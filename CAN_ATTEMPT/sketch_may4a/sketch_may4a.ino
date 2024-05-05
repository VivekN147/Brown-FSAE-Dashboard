#include <CAN.h>
#include <SPI.h>
#define MISO_Pin 12
#define MOSI_Pin 11
#define CS_Pin 10
#define SCK_Pin 13
#define INTRPT_Pin 9
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
  while (!Serial);
  Serial.println("CAN Receiver Callback");
  CAN.setSPIFrequency(100000); //max MCP is 10Mhz
  CAN.setClockFrequency(8E6);
  // start the CAN bus at 500 kbps
  if (!CAN.begin(250E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  } else {
    Serial.println("CAN Started");
    can_start = 0;
  }
  // register the receive callback
  CAN.onReceive(onReceive);
}
void loop() {
if (can_start){
  while(!CAN.begin(250E3)){
  Serial.println("can fail");
  delay(100);
  }
} else {
  can_start = 0;
}
}
void onReceive(int packetSize) {
  // received a packet
  //Serial.println("hello");
  Serial.println(CAN.packetId());
  if(CAN.packetId() == 0x701) {
    Serial.print("Received ");
    if (CAN.packetExtended()) {
      Serial.print("extended ");
    }
    if (CAN.packetRtr()) {
      // Remote transmission request, packet contains no data
      Serial.print("RTR ");
    }
    Serial.print("packet with id ");
    Serial.print(CAN.packetId());
    //Serial.print(CAN.packetId(), HEX);
    if (CAN.packetRtr()) {
      Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    } else {
      Serial.print(" and length ");
      Serial.println(packetSize);
      // only print packet data for non-RTR packets
      union data {
        uint32_t bits;
        float voltage;
      };
      union data t;
      t.bits = 0;
      int i = 0;
      while (CAN.available()) {
        uint32_t j = CAN.read();
        if(i < 4) {
          t.bits = (t.bits << 8) + j;
          Serial.print(j,HEX);
          Serial.print(" ");
          i++;
        }
      }
      Serial.println();
      Serial.print(t.voltage);
      Serial.println();
    }
    Serial.println();
  }
}