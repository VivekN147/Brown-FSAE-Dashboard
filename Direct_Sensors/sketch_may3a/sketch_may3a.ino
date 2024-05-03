const int inputPin = 2; // measure frequency at this pin

volatile unsigned long count = 0; // pulse count
unsigned long startTime = // start time of measurement

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(inputPin, INPUT); // set the input pin as INPUT
  attachInterrupt(digitalPinToInterrupt(inputPin), countPulse, RISING)
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(300); // MAYBE remove the delay, or make it smaller
  
  // disable interrupts to safely read count and startTime
  noInterrupts(); 

  // Read the current count and time
  unsigned long currentCount = count;
  unsigned long currentTime = millis();

  // Re-enable interrupts
  interrupts();

  // Calculate elapsed time since last measurement
  unsigned long elapsedTime = currentTime - startTime;

  // Calculate frequency in Hz
  float frequency = currentCount / (elapsedTime / 1000.0);

  // Convert frequency to engine speed in RPM
  float engineSpeed = frequency * 60.0;

  // Print engine speed
  Serial.print("Engine Speed: ");
  Serial.print(engineSpeed);
  Serial.println(" RPM");
}

// Interrupt service routine to count pulses
void countPulse() {
  count++;
}


