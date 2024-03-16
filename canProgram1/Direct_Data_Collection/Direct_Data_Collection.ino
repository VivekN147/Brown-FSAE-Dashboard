#define COOLANT_TEMP A5
#define FAN 6
#define GEAR A7
#define RPM 7

// dont know if they should be int or float
//sumNum = 20;
//val1 = sumNum;

float BoundN = 0;
float Bound1 = 0.83;
float Bound2 = 1.67;
float Bound3 = 2.50;
float Bound4 = 3.33;
float Bound5 = 4.16;
float Bound6 = 5;

float highTime;
float lowTime;
float frequencyConstant;
float fromFBound;
float toFBound;

void setup() {
  // put your setup code here, to run once:
  pinMode(COOLANT_TEMP, INPUT);
  pinMode(FAN, INPUT);
  pinMode(GEAR, INPUT);
  pinMode(RPM, INPUT);

  Serial.begin(9600);
  Serial.println("Beginning data collection...");
}

void loop() {
  // READING COOLANT TEMP
  float coolantTemp = analogRead(COOLANT_TEMP);
  Serial.println(coolantTemp);

  // READING FAN STATUS
  bool fanSpeed = digitalRead(FAN);
  if(fanSpeed) {
    Serial.println("FAN ON");
  } else {
    Serial.println("FAN OFF");
  }

  // READING GEAR
  float gear = analogRead(GEAR);
  if(gear == BoundN) {
    Serial.println("GEAR N");
  } else if(gear <= Bound1 && gear > BoundN) {
    Serial.println("GEAR 1");
  } else if(gear <= Bound2 && gear > Bound1) {
    Serial.println("GEAR 2");
  } else if(gear <= Bound3 && gear > Bound2) {
    Serial.println("GEAR 3");
  } else if(gear <= Bound4 && gear > Bound3) {
    Serial.println("GEAR 4");
  } else if(gear <= Bound5 && gear > Bound4) {
    Serial.println("GEAR 5");
  } else if(gear <= Bound6 && gear > Bound5) {
    Serial.println("GEAR 6");
  }else {
    Serial.println("Something's wrong!");
  }

  // READING RPM
  highTime = pulseIn(RPM, HIGH);
  lowTime = pulseIn(RPM, LOW);
  float period = highTime + lowTime;
  float frequency = 1 / (period * frequencyConstant);
  float volt = map(frequency, 0, fromFBound, 0, toFBound);
  Serial.println(volt);

  delay(100);

  // possible write structure (arduino -> nextion editor)
  // This specific example is for a bar graph
  //delay(30);
  //Serial.print("object.val=" + String(val1)); //send as strinf
  //Serial.write(0xff);
  //Serial.write(0xff);
  //Serial.write(0xff);
  //sumNUm++;

  // possible write structure (arduino -> nextion editor)
  // This specific example is for a Text/Number (Gear)
  //int GearVal = 2 // this would be the gear as the number/neutral/reverse
  //Serial.print("gear.val="); // print the variable we want to change on the screen
  //Serial.print(GearVal); // print the value we want to be displayed
  //Serial.write(0xff); // always add 3 full bytes after
  //Serial.write(0xff);
  //Serial.write(0xff);

  // Coolant Temp
  int CoolVal = 22;
  Serial.print("coolant.val=" + String(CoolVal));
  Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);

  // Fan
  string FanVal = "OFF";
  Serial.print("fan.txt=" + String(FanVal));
  Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);

  // Battery
  int BatteryVal = 2;
  Serial.print("battery.val=" + String(BatteryVal));
  Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);

  // Gear - Needs fixing for both int (1-6) and string ("N")
  string GearVal = "1";
  Serial.print("gear.txt=" + String(GearVal));
  Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);

  // Traction Control
  int TCVal = 1; // 0 = OFF, 1 = ON
  Serial.print("tc.val=" + String(TCVal));
  Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);

  // Launch Control
  int LCVal = 1; // 0 = OFF, 1 = ON
  Serial.print("lc.val=" + String(LCVal));
  Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);

  // RPM1 = 2x Progress Bars
  int RPMVal = 101; // Have rmp brought down from 13,500 --> 135 (so divided by 100)
  if (RPMVal =< 100) {
    Serial.print("p1.val=" + String(RPMVal));
    Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
  } else if (RPMVal > 100) {
    int RPMP2 = (RPMVal % 100);
    int RPMP1 = (RPMVal - RPMP2);
    Serial.print("p1.val=" + String(RPMP2)); 
    Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    Serial.print("p2.val=" + String(RPMP2));
    Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
  }

  // RPM2 = 27x Progress Bars
  int RPMVal = 101; // // Have rmp brought down from 13,500 --> 135 (so divided by 100)
  std::vector<std::string> rpmBars = {"j0", "j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "j10", "j11", "j12", "j13", "j14", "j15", "j16", "j17", "j18", "j19", "j20", "j21", "j22", "j23", "j24", "j25", "j26"};
  int RPMBarVal;
  for (size_t i = 0; i < rpmBars.size(); ++i) {
    int low = (i*5);
    int high = (low + 5);
    if (RPMVal > low) & (RPMVal <= high) {
      RPMBarVal = 100;
    } else {
      RPMBarVal = 0;
    }
    Serial.print(rpmBars[i] + ".val=" + String(RPMBarVal));
    Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
  }
  // Ranges:
  // {0, 1, 2, 3, 4, 5...}
  // {0-5, 6-10, 11-15...}

}
