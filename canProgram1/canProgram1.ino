#include <FlexCAN_T4.h>
//#include <APA102.h>
//#include <FastLED.h>


/*#define TESTING 1

#define LEDPIN 13
#define LEDCLKPIN 14
#define NUMLEDS 13
#define OILPIN 20
#define COOLPIN 19
#define LEDTYPE WS2813
#define COLORORDER GRB
#define BRIGHTNESS  64

rgb_color colors[NUMLEDS];

// RPM tuning
#define REV_LIMIT 13500
#define REV_MAX 13000
#define REV_MIN 10000

// Warning Limits
#define OIL_THRESH 100
#define COOL_THRESH 100

APA102<LEDPIN, LEDCLKPIN> ledStrip;
CRGB leds[NUMLEDS];*/
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
CAN_message_t msg;
int msg_id;

// The struct that represents the status of the car
// 4 bytes * 8 floats = 32 bytes
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
/*float acceleration_y;
float acceleration_z;

char output;
int n;

bool leds[16] = {0};*/
telemetry car = {0,0,0,9000,0,0,0,0};

void setup(void) {
  /*FastLED.addLeds<LEDTYPE, LEDPIN, COLORORDER>(leds, NUMLEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );*/
  
  can1.begin();
  can1.setBaudRate(1000000);

  /*pinMode(OILPIN, OUTPUT);
  pinMode(COOLPIN, OUTPUT);
  
  showStartupFlash(millis() >> 2);*/

  Serial.begin(9600);
  Serial.print("Starting Teensy...");

}

// Copies two sets of an 8 bit number from the buffer into the values 
void copyValues(float *value1, float *value2, CAN_message_t msg) {
  uint8_t a[4] = {msg.buf[3], msg.buf[2], msg.buf[1], msg.buf[0]};
  memcpy(value1, &a, 2); //2

  uint8_t b[4] = {msg.buf[7], msg.buf[6], msg.buf[5], msg.buf[4]};
  memcpy(value2, &b, 3); //3
}

void loop() {
  if (!can1.read(msg) ) {
    msg_id = msg.id;
    Serial.println(msg_id);
    /*if(msg_id == 0x700) { // Coolant and Oil Temp
      copyValues(&car.coolant_temp, &car.oil_pressure, msg);
    } else*/ if(msg_id == 0x701) { //  Battery Voltage and Exhaust
      copyValues(&car.battery_voltage, &car.lambda, msg);
    } /*else if(msg_id == 0x702) { // Engine Speed and Throttle Pos
      copyValues(&car.engine_speed, &car.throttle_pos, msg);
    } else if(msg_id == 0x703) { // Wheel Speeds
      copyValues(&car.wheel_speed_l, &car.wheel_speed_r, msg);
    } else if(msg_id == 0x704) { // Acceleration Y, Z
      copyValues(&acceleration_y, &acceleration_z, msg);
    }*/

    Serial.printf("%f,\n", car.battery_voltage);
    // Serial.write((byte*)&car, sizeof(car));
  } 

  //showRPM(car.engine_speed/5);  


  /*if (TESTING) {
    if(car.engine_speed > 14000) {
      car.engine_speed = 9000;
    }
    car.engine_speed += 100;

    Serial.printf("%f,%f,%f,%f,%f,%f,%f,%f\n", car.coolant_temp, car.oil_pressure, car.battery_voltage, car.lambda, car.engine_speed, car.throttle_pos, car.wheel_speed_l, car.wheel_speed_r);
    //Serial.write((byte*)&car, sizeof(car));
    delay(100);
  }*/
  
}

/*void showRPM(float rpm) {
  int num_pixels; // Number of LEDs ilumninated
  rgb_color c; // Pixel color
  bool limit = false;
  
  if(rpm < REV_MIN) { // Below visual range
    memset(leds, 0, sizeof(leds));
  } else if(rpm <= REV_MAX) { // Inside power band
    memset(leds, 0, sizeof(leds));
    num_pixels = int((rpm - REV_MIN) / (REV_MAX - REV_MIN) * (NUMLEDS*3/4));

    memset(leds, 1, num_pixels * sizeof(bool));
  } else if (rpm <= REV_LIMIT){ // Above rev max
    memset(leds, 1, sizeof(leds));
  } else { // Above rev limiter
    memset(leds, 1, sizeof(leds));
    limit = true;
  }
  for(uint16_t i=0; i<16; i++) {
    if (limit) {
      c = rgb_color(255, 0, 0); // RED
    } else if (leds[i]) {
      if(i < NUMLEDS/4) {
        c = rgb_color(0, 0, 255); // BLUE
      } else if (i < NUMLEDS/2) {
        c = rgb_color(0, 255, 0); // GREEN
      } else if (i < (NUMLEDS*3/4)) {
        c = rgb_color(255, 255, 0); // YELLOW
      } else {
        c = rgb_color(255, 0, 0); // RED 
      }
    } else {
      c = rgb_color(0, 0, 0);
    }
    colors[i] = c;
  }
  ledStrip.write(colors, NUMLEDS, 1);
}

void showWarnings(float oil_pressure, float coolant_temp) {

  if (coolant_temp > COOL_THRESH) {
    digitalWrite(COOLPIN, HIGH);
  } else {
    digitalWrite(COOLPIN, LOW);
  }
  
}

void showStartupFlash(uint8_t time) {
  for(uint16_t i = 0; i < NUMLEDS; i++)
  {
    uint8_t x = time - i * 8;
    colors[i] = rgb_color(x, 255 - x, x);
  }

  ledStrip.write(colors, NUMLEDS, 1);
  delay(2000);
}*/