#define LED_NUMBER 8

void setup() {
  // initialize digital pin ledPin as an output.
  int ledPin = LED_NUMBER;
  pinMode(ledPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  int ledPin = LED_NUMBER;
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}