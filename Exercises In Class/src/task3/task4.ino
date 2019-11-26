
#define LED_NUMBER 9

int analogPin = A0;

int val = 0;
void setup() {
  // initialize digital pin ledPin as an output.
  int ledPin = LED_NUMBER;
  pinMode(ledPin, OUTPUT);

  //initialize serial freq
    Serial.begin(9600);
    
}


// the loop function runs over and over again forever
void loop() {
    val = analogRead(analogPin);
  Serial.println(val);

  analogWrite(ledPin, val / 4);
  


}
