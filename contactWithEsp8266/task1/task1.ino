const int ledPin =  LED_BUILTIN;

// Variables will change:
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long intervalOn = 1000;           // interval at which to blink (milliseconds)

const long intervalOff = 2000; 

long interval = 0;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

// the loop function runs over and over again forever
/*
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);  // wait for a second
  }
}
*/

void loop() {
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();  

  
  if(ledState == HIGH) {
    interval = intervalOff; 
   } else {
    interval = intervalOn; 
   }

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
      Serial . println ( "LED is turned off" ) ; 
    } else {
      ledState = LOW;
      Serial . println ( "LED is turned on" ) ; 
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
}
