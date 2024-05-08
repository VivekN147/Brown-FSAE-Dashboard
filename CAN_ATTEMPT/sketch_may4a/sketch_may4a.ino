#include <CAN.h>
#include <SPI.h>
#define MISO_Pin 12
#define MOSI_Pin 11
#define CS_Pin 10
#define SCK_Pin 13
#define INTRPT_Pin 9
float voltage;
float coolTemp;
float engnSpeed;
float wheelSpeed;
bool can_start = 1;
void setup() {
  //establish SPI pins
    // SPI.setMISO(MISO_Pin);
    // SPI.setMOSI(MOSI_Pin);
    // SPI.setSCK(SCK_Pin);
  //Input output pins
  pinMode(CS_Pin, OUTPUT);
  //Interrupt needs to read
  pinMode(INTRPT_Pin, INPUT);
  //note: can library attaches its own interrupt to pin
  //Configure CAN library:
  CAN.setPins(CS_Pin, INTRPT_Pin); //
  Serial.begin(9600);
  Serial1.begin(9600);
  while (!Serial);
  // // Serial.println("CAN Receiver Callback");
  CAN.setSPIFrequency(100000); //max MCP is 10Mhz
  CAN.setClockFrequency(8E6);
  // start the CAN bus at 500 kbps
  if (!CAN.begin(250E3)) {
    // // Serial.println("Starting CAN failed!");
    while (1);
  } else {
    // // Serial.println("CAN Started");
    can_start = 0;
  }
  // register the receive callback
  CAN.onReceive(onReceive);
}
void loop() {
  if (can_start){
    while(!CAN.begin(250E3)){
      // // Serial.println("can fail");
      delay(100);
    }
  } else {
    can_start = 0;
  }
  //print to dash
  // RPM
  int RPMVal = engnSpeed/100;
  if (RPMVal <= 100) {
    Serial1.print("p1.val=" + String(RPMVal)); Serial1.write(0xff); Serial1.write(0xff); Serial1.write(0xff);
    Serial1.print("p2.val=0"); Serial1.write(0xff); Serial1.write(0xff); Serial1.write(0xff);
  } else if (RPMVal > 100) {
    int RPMP2 = (RPMVal % 100);
    int RPMP1 = (RPMVal - RPMP2);
    RPMP2 = (RPMP2 * 100) / 35;
    Serial1.print("p1.val=" + String(RPMP1)); Serial1.write(0xff); Serial1.write(0xff); Serial1.write(0xff);
    Serial1.print("p2.val=" + String(RPMP2)); Serial1.write(0xff); Serial1.write(0xff); Serial1.write(0xff);
    // ONCE EVERYTHING COMPLETELY WORKS - CHANGE TOP CODE TO BELOW CODE (FASTER):
      // NOTE: This will not work if the Arduino ends up recieving out-of-bound rpm values from MOTEC/CAN
    //int RPMP2 = (RPMVal % 100) * 100 / 35;
    //Serial.print("p1.val=100"); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    //Serial.print("p2.val=" + String(RPMP2)); Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
  }
  // Coolant Temp
  int CoolVal = coolTemp;
  Serial1.print("coolant.val=" + String(CoolVal)); Serial1.write(0xff); Serial1.write(0xff); Serial1.write(0xff);
  // Fan
  String FanVal = "\"ON\""; // Options: "\"ON\"", "\"OFF\"" - maybe "\"AUTO\""
  Serial1.print("fan.txt=" + FanVal); Serial1.write(0xff); Serial1.write(0xff); Serial1.write(0xff);
  // Battery
  Serial1.print("battery.val=" + String(voltage)); Serial1.write(0xff); Serial1.write(0xff); Serial1.write(0xff);
  // Gear
  String GearVal = "\"1\""; // Options: "\"N\"" or "\"i\"" where i = 0,1,2,3,4,5,6 - maybe not 0
  Serial1.print("gear.txt=" + GearVal); Serial1.write(0xff); Serial1.write(0xff); Serial1.write(0xff);
  // Traction Control
  int TCVal = 0; // Options: 0 = OFF, 1 = ON
  Serial1.print("tc.val=" + String(TCVal)); Serial1.write(0xff); Serial1.write(0xff); Serial1.write(0xff);
  // Launch Control
  int LCVal = 0; // Options: 0 = OFF, 1 = ON
  Serial1.print("lc.val=" + String(LCVal)); Serial1.write(0xff); Serial1.write(0xff); Serial1.write(0xff);
  Serial.print("Battery: " + String(voltage) + "V, \tCoolant Temp: " + String(coolTemp) + "C, \tEngine Speed: " + String(engnSpeed) + " RPM, \tWheel Speed: " + String(wheelSpeed) + "kph\n");
  delay(100);
}
void onReceive(int packetSize) {
  // received a packet
  //// // Serial.println("hello");
  // Serial.println(CAN.packetId());
  if(CAN.packetId() == 0x701) {
    // Serial.print("Received ");
    if (CAN.packetExtended()) {
      // Serial.print("extended ");
    }
    if (CAN.packetRtr()) {
      // Remote transmission request, packet contains no data
      // Serial.print("RTR ");
    }
    // Serial.print("packet with id ");
    // Serial.print(CAN.packetId());
    //// Serial.print(CAN.packetId(), HEX);
    if (CAN.packetRtr()) {
      // Serial.print(" and requested length ");
      // Serial.println(CAN.packetDlc());
    } else {
      // Serial.print(" and length ");
      // Serial.println(packetSize);
      // only print packet data for non-RTR packets
      union data {
        uint32_t bits;
        float number;
      };
      union data t;
      t.bits = 0;
      int i = 0;
      while (CAN.available()) {
        uint32_t j = CAN.read();
        if(i < 4) {
          t.bits = (t.bits << 8) + j;
          // Serial.print(j,HEX);
          // Serial.print(" ");
          i++;
        }
      }
      // Serial.println();
      // Serial.print(t.number);
      voltage = t.number;
      // Serial.println();
    }
    // Serial.println();
  }
  if(CAN.packetId() == 0x700) {
    // Serial.print("Received ");
    if (CAN.packetExtended()) {
      // Serial.print("extended ");
    }
    if (CAN.packetRtr()) {
      // Remote transmission request, packet contains no data
      // Serial.print("RTR ");
    }
    // Serial.print("packet with id ");
    // Serial.print(CAN.packetId());
    //// Serial.print(CAN.packetId(), HEX);
    if (CAN.packetRtr()) {
      // Serial.print(" and requested length ");
      // Serial.println(CAN.packetDlc());
    } else {
      // Serial.print(" and length ");
      // Serial.println(packetSize);
      // only print packet data for non-RTR packets
      union data {
        uint32_t bits;
        float number;
      };
      union data t;
      t.bits = 0;
      int i = 0;
      while (CAN.available()) {
        uint32_t j = CAN.read();
        if(i < 4) {
          t.bits = (t.bits << 8) + j;
          // Serial.print(j,HEX);
          // Serial.print(" ");
          i++;
        }
      }
      // Serial.println();
      // Serial.print(t.number);
      coolTemp = t.number;
      // Serial.println();
    }
    // Serial.println();
  }
  if(CAN.packetId() == 0x702) {
    // Serial.print("Received ");
    if (CAN.packetExtended()) {
      // Serial.print("extended ");
    }
    if (CAN.packetRtr()) {
      // Remote transmission request, packet contains no data
      // Serial.print("RTR ");
    }
    // Serial.print("packet with id ");
    // Serial.print(CAN.packetId());
    //// Serial.print(CAN.packetId(), HEX);
    if (CAN.packetRtr()) {
      // Serial.print(" and requested length ");
      // Serial.println(CAN.packetDlc());
    } else {
      // Serial.print(" and length ");
      // Serial.println(packetSize);
      // only print packet data for non-RTR packets
      union data {
        uint32_t bits;
        float number;
      };
      union data t;
      t.bits = 0;
      int i = 0;
      while (CAN.available()) {
        uint32_t j = CAN.read();
        if(i < 4) {
          t.bits = (t.bits << 8) + j;
          // Serial.print(j,HEX);
          // Serial.print(" ");
          i++;
        }
      }
      // Serial.println();
      // Serial.print(t.number);
      engnSpeed = t.number / 6;
      // Serial.println();
    }
    // Serial.println();
  }
  if(CAN.packetId() == 0x703) {
    // Serial.print("Received ");
    if (CAN.packetExtended()) {
      // Serial.print("extended ");
    }
    if (CAN.packetRtr()) {
      // Remote transmission request, packet contains no data
      // Serial.print("RTR ");
    }
    // Serial.print("packet with id ");
    // Serial.print(CAN.packetId());
    //// Serial.print(CAN.packetId(), HEX);
    if (CAN.packetRtr()) {
      // // Serial.print(" and requested length ");
      // // Serial.println(CAN.packetDlc());
    } else {
      // // Serial.print(" and length ");
      // // Serial.println(packetSize);
      // only print packet data for non-RTR packets
      union data {
        uint32_t bits;
        float number;
      };
      union data t;
      t.bits = 0;
      int i = 0;
      while (CAN.available()) {
        uint32_t j = CAN.read();
        if(i < 4) {
          t.bits = (t.bits << 8) + j;
          // // Serial.print(j,HEX);
          // // Serial.print(" ");
          i++;
        }
      }
      // // Serial.println();
      // // Serial.print(t.number);
      wheelSpeed = t.number;
      // // Serial.println();
    }
    // // Serial.println();
  }
}