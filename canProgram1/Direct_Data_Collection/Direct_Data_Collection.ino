#define DATAPIN A5

void setup() {
  // put your setup code here, to run once:
  pinMode(DATAPIN, INPUT); // if an error comes up maybe delete this line, i don't think it's necessary

  Serial.begin(9600);
  Serial.println("Beginning data collection...");
}

void loop() {
  // put your main code here, to run repeatedly:
  float data = analogRead(DATAPIN);
  Serial.println(data);
}
