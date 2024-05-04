const int inputPin = 2; // measure frequency at this pin

volatile unsigned long count = 0; // pulse count
unsigned long startTime = 0; // start time of measurement

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(inputPin, INPUT); // set the input pin as INPUT
  attachInterrupt(digitalPinToInterrupt(inputPin), countPulse, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(20); // MAYBE remove the delay, or make it smaller
  
  // disable interrupts to safely read count and startTime
  noInterrupts(); 

  // Read the current count and time
  unsigned long currentCount = count;
  unsigned long currentTime = millis();

  // Re-enable interrupts
  interrupts();

  // Calculate elapsed time since last measurement
  unsigned long elapsedTime = currentTime - startTime;

  // Calculate frequency in Hz
  float frequency = currentCount / (elapsedTime / 1000.0);

  // Convert frequency to engine speed in RPM
  float engineSpeed = frequency * 60.0;

  // Print engine speed
  Serial.print("Engine Speed: ");
  Serial.print(engineSpeed);
  Serial.println(" RPM");

  // Ensure engine speed is within the desired range
  if (engineSpeed < 0) {
    engineSpeed = 0; // Limit to minimum RPM
  } else if (engineSpeed > 13500) {
    engineSpeed = 13500; // Limit to maximum RPM
  }

  // Convert RPM from 0-13,500 to 0-135 as an integer
  int engineSpeedScaled = static_cast<int>(engineSpeed / 100.0);

  // Print engine speed to Nextion
  if (engineSpeedScaled <= 100) {
    Serial.print("p1.val=" + String(engineSpeedScaled)); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    Serial.print("p2.val=0"); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
  } else if (engineSpeedScaled > 100) {
    int RPMP2 = (engineSpeedScaled % 100);
    int RPMP1 = (engineSpeedScaled - RPMP2);
    RPMP2 = (RPMP2 * 100) / 35;
    Serial.print("p1.val=" + String(RPMP1)); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    Serial.print("p2.val=" + String(RPMP2)); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    // ONCE EVERYTHING COMPLETELY WORKS - CHANGE TOP CODE TO BELOW CODE (FASTER):
      // NOTE: This will not work if the Arduino ends up recieving out-of-bound rpm values from MOTEC/CAN
    //int RPMP2 = (engineSpeedScaled % 100) * 100 / 35;
    //Serial.print("p1.val=100"); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    //Serial.print("p2.val=" + String(RPMP2)); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
  }

}

// Interrupt service routine to count pulses
void countPulse() {
  count++;
}


