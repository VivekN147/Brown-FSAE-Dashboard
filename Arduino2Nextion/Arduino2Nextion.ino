#include <NexButton.h>
#include <NexCheckbox.h>
#include <NexConfig.h>
#include <NexCrop.h>
#include <NexDualStateButton.h>
#include <NexGauge.h>
#include <NexGpio.h>
#include <NexHardware.h>
#include <NexHotspot.h>
#include <NexNumber.h>
#include <NexObject.h>
#include <NexPage.h>
#include <NexPicture.h>
#include <NexProgressBar.h>
#include <NexRadio.h>
#include <NexRtc.h>
#include <NexScrolltext.h>
#include <NexSlider.h>
#include <NexText.h>
#include <NexTimer.h>
#include <NexTouch.h>
#include <NexUpload.h>
#include <NexVariable.h>
#include <NexWaveform.h>
#include <Nextion.h>
#include <doxygen.h>
 
int looper = 0;
bool fan = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Coolant Temp
  /*int CoolVal = 22;
  Serial.print("coolant.val=" + String(CoolVal));
  Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);

  // Fan
  string FanVal = "OFF";
  Serial.print("fan.txt=" + String(FanVal));
  Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);*/

  // Battery
  for(int i = 0; i < 13500; i++) {
    Serial.print("battery.val=" + String(i));
    Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
  }
  /*int BatteryVal = 2;
  Serial.print("battery.val=" + String(BatteryVal));
  Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);*/

  /*// Gear - Needs fixing for both int (1-6) and string ("N")
  string GearVal = "1";
  Serial.print("gear.txt=" + GearVal);
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
  if (RPMVal <= 100) {
    Serial.print("p1.val=" + String(RPMVal));
    Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    Serial.print("p2.val=0");
    Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
  } else if (RPMVal > 100) {
    int RPMP2 = (RPMVal % 100);
    int RPMP1 = (RPMVal - RPMP2);
    RPMP2 = (RPMP2 * 100) / 35;
    Serial.print("p1.val=" + String(RPMP1)); 
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
    if (RPMVal > low) {
      RPMBarVal = 100;
    } else {
      RPMBarVal = 0;
    }
    Serial.print(rpmBars[i] + ".val=" + String(RPMBarVal));
    Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
  }
  // Ranges:
  // {0, 1, 2, 3, 4, 5...}
  // {0-5, 6-10, 11-15...}*/

  delay(100);
}

void changeVal() {
  for(int i = 0; i < 13500; i++) {
    looper = i;
    Serial.println(looper);
  }
  for(int i = 13500; i >= 0; i--) {
    looper = i;
    Serial.println(looper);
  }
  if(fan) {
    Serial.println("fan on");
  } else {
    Serial.println("fan off");
  }
  fan = !fan;
}
