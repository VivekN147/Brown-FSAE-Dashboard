// input pin can be any digital input
// RPM Pin
const byte inputPin = 2;
boolean inputState = false;
boolean lastInputState = false;
long count = 0L;
// Wheel Speed Pin
const byte inputPin2 = 4;
boolean inputState2 = false;
boolean lastInputState2 = false;
long count2 = 0L;

unsigned long previousCountMillis = millis();
const long countMillis = 500L; // Might need to change to 1000L for the second pin
void setInputState() {
  inputState = digitalRead(inputPin);
  inputState2 = digitalRead(inputPin2);
}

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // runs every time thru the loop
  setInputState();
  // count every transision HIGH<->LOW for RPM Pin
  if (inputState != lastInputState) {
    count++;
    lastInputState = inputState;
  }
  // count every transision HIGH<->LOW for Wheel Speed Pin
  if (inputState2 != lastInputState2) {
    count2++;
    lastInputState2 = inputState2;
  }

  // ------- every half second, count is equal to Hz.---------------
  if (millis() - previousCountMillis >= countMillis) {
    previousCountMillis += countMillis;
    // show Hz on Serial too if available
    //Serial.print(count);
    //Serial.println(" Hz");
    //Serial.print(count2);
    //Serial.println(" Hz");

    // -------------------------------- OTHER OBJECTS -----------------------------------------------------------
    // Coolant Temp
    int CoolVal = 39;
    Serial.print("coolant.val=" + String(CoolVal)); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    // Fan
    String FanVal = "\"ON\""; // Options: "\"ON\"", "\"OFF\"" - maybe "\"AUTO\""
    Serial.print("fan.txt=" + FanVal); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    // Battery
    int BatteryVal = 2;
    Serial.print("battery.val=" + String(BatteryVal)); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    // Gear
    String GearVal = "\"1\""; // Options: "\"N\"" or "\"i\"" where i = 0,1,2,3,4,5,6 - maybe not 0
    Serial.print("gear.txt=" + GearVal); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    // Traction Control
    int TCVal = 1; // Options: 0 = OFF, 1 = ON
    Serial.print("tc.val=" + String(TCVal)); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    // Launch Control
    int LCVal = 1; // Options: 0 = OFF, 1 = ON
    Serial.print("lc.val=" + String(LCVal)); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    // -------------------------------- OTHER OBJECTS END -------------------------------------------------------
    
    // Print engine speed to Nextion
    int rpm = count * 60 / 100;
    if (rpm <= 100) {
      Serial.print("p1.val=" + String(rpm)); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
      Serial.print("p2.val=0"); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    } else if (rpm > 100) {
      int RPMP2 = (rpm % 100);
      int RPMP1 = (rpm - RPMP2);
      RPMP2 = (RPMP2 * 100) / 35;
      Serial.print("p1.val=" + String(RPMP1)); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
      Serial.print("p2.val=" + String(RPMP2)); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    // ONCE EVERYTHING COMPLETELY WORKS - CHANGE TOP CODE TO BELOW CODE (FASTER):
      // NOTE: This will not work if the Arduino ends up recieving out-of-bound rpm values from MOTEC/CAN
    //int RPMP2 = (engineSpeedScaled % 100) * 100 / 35;
    //Serial.print("p1.val=100"); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    //Serial.print("p2.val=" + String(RPMP2)); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    }

    // reset to zero for the next half second's sample
    count = 0L;
    count2 = 0L;
  }
}