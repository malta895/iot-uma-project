//TASK 3

int analogPin = A0;

int val = 0;

int ledPin = 8;

void setup() {
  // initialize digital pin ledPin as an output.
  int ledPin = LED_NUMBER;
  pinMode(ledPin, OUTPUT);

  //initialize serial freq
    Serial.begin(9600);
    
}

void loop() {
  val = analogRead(analogPin);
  Serial.println(val);

  if (val != 0) {
    digitalWrite(ledPin, HIGH);
    delay(1023 - val);

    digitalWrite(ledPin, LOW);

    delay(1023 - val);
  } else {
    digitalWrite(ledPin, HIGH);
  }


}
