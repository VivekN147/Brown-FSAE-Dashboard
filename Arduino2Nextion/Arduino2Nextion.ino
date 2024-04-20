/*#include <NexButton.h>
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
#include <doxygen.h>*/

//----------------------------------------------------------------------
// When Done, remove lines (and any relating code) that have a comment:
//                          "for testing"
//----------------------------------------------------------------------

//int looper = 0;
//bool fan = false;
int i; // for testing

void setup() {
  // put your setup code here, to run once:
  i = 50; // for testing
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
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

  // RPM 
  // Have rmp brought down from 13,500 --> 135 (so divided by 100)
  if (i > 135) { // for testing
    i = 50; // for testing
  } // for testing
  int RPMVal = i++; 
  
  if (RPMVal <= 100) {
    Serial.print("p1.val=" + String(RPMVal)); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    Serial.print("p2.val=0"); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
  } else if (RPMVal > 100) {
    int RPMP2 = (RPMVal % 100);
    int RPMP1 = (RPMVal - RPMP2);
    RPMP2 = (RPMP2 * 100) / 35;
    Serial.print("p1.val=" + String(RPMP1)); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    Serial.print("p2.val=" + String(RPMP2)); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    // ONCE EVERYTHING COMPLETELY WORKS - CHANGE TOP CODE TO BELOW CODE (FASTER):
      // NOTE: This will not work if the Arduino ends up recieving out-of-bound rpm values from MOTEC/CAN
    //int RPMP2 = (RPMVal % 100) * 100 / 35;
    //Serial.print("p1.val=100"); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    //Serial.print("p2.val=" + String(RPMP2)); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
  }
  
  //delay(10);
}

/*void changeVal() {
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
}*/
