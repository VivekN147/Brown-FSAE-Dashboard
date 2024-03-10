#define COOLANT_TEMP A5
#define FAN 6
#define GEAR A7
#define RPM 7

// dont know if they should be int or float
sumNum = 20;
val1 = sumNum;

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
  delay(30);
  Serial.print("object.val=" + String(val1)); //send as strinf
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  sumNUm++;

  // possible write structure (arduino -> nextion editor)
  // This specific example is for a Text/Number (Gear)
  int GearVal = 2 // this would be the gear as the number/neutral/reverse
  Serial.print("objname.val="); // print the variable we want to change on the screen
  Serial.print(GearVal); // print the value we want to be displayed
  Serial.write(0xff); // always add 3 full bytes after
  Serial.write(0xff);
  Serial.write(0xff);

}
