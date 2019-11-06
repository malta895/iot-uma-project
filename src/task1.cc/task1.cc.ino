int analogPin = A0;

int val = 0;

int ledPin = 8;

void setup(){
  Serial.begin(9600);
}

void loop(){
  val = analogRead(analogPin);
  Serial.println(val);

if(val != 0){
    digitalWrite(ledPin, HIGH);
  delay(1023 - val);

    digitalWrite(ledPin, LOW);

  delay(1023 - val);
} else {
      digitalWrite(ledPin, HIGH);
}


}

//#define LED_NUMBER 8
//
//void setup() {
//  // initialize digital pin ledPin as an output.
//  int ledPin = LED_NUMBER;
//  pinMode(ledPin, OUTPUT);
//}
//
//// the loop function runs over and over again forever
//void loop() {
//  int ledPin = LED_NUMBER;
//  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);                       // wait for a second
//  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000);                       // wait for a second
//
//  
//}



///*
// ESP8266 Arduino Blink by Simon Peter
// Blink the blue LED on the ESP-01 module
// This example code is in the public domain
// 
// The blue LED on the ESP-01 module is connected to GPIO1 
// (which is also the TXD pin; so we cannot use Serial.print() at the same time)
// 
// Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
//*/
//
//void setup() {
//  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
//}
//
//// the loop function runs over and over again forever
//void loop() {
//  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
//                                    // but actually the LED is on; this is because 
//                                    // it is acive low on the ESP-01)
//  delay(500);                      // Wait for a second
//  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
//  delay(500);                      // Wait for two seconds (to demonstrate the active low LED)
//}
