#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
CAN_message_t msg;
int msg_id;

struct telemetry {
  float coolant_temp;
  float oil_pressure;
  float battery_voltage;
  float lambda;
  float engine_speed;
  float throttle_pos;
  float wheel_speed_l;
  float wheel_speed_r;
};

telemetry car = {0,0,0,0,0,0,0,0};

void setup() {
  // put your setup code here, to run once:

  can1.begin();
  can1.setBaudRate(1000000);

  Serial.begin(9600);
  Serial.print("Starting Teensy");

}

void loop() {
  // put your main code here, to run repeatedly:

  if (can1.read(msg) ) {
    msg_id = msg.id;
    if(msg_id == 0x701) { // Battery Voltage and Exhaust
      copyValues(&car.battery_voltage, msg);
    }

    Serial.printf("%f\n", car.battery_voltage);
    // Serial.write((byte*)&car, sizeof(car));
  } 

}
