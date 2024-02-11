#define DATAPIN 5

void setup() {
  // put your setup code here, to run once:
  pinMode(DATAPIN, INPUT);

  Serial.begin(9600);
  Serial.println("Beginning data collection...");
}

void loop() {
  // put your main code here, to run repeatedly:
  float data = analogRead(DATAPIN);
  Serial.println(data);
}
