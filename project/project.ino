/*
  PRACTICA 1 "SENSOR DE ULTRASONIDOS"
  Muestra la distance a la que se encuentran los objetos
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define trigPin D0   //define la salida por donde se manda el trigPin
#define echoPin D1 //define la salida por donde se recibe el echoPin

#define LED_UPPER_THRESHOLD D2 //this led is on when the upper threshold is trespassed
#define LED_LOWER_THRESHOLD D3 // this led is on when the lower threshold is trespassed

int distance;  //crea la variable "distance"
float tiempo;  //crea la variable tiempo (como float)

const char* ssid = "MASTER";
const char* password = "malagaiot";

const char* mqtt_server = "iot.ac.uma.es";
const char* mqtt_user = "master";
const char* mqtt_pass = "malagaiot";

//TOPICS
const char* mqtt_distance = "master/GRUPO_K/distance";
const char* mqtt_threshold = "master/GRUPO_K/threshold";

//LED VARIABLES
boolean led_lower_on = false;
boolean led_upper_on = false;

//BASKET HEIGHT
double basket_height = 50.;

char mqtt_cliente[50];

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(9600);  //Serial port

  //Initialize Sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //initialize the LEDs outputs
  pinMode(LED_LOWER_THRESHOLD, OUTPUT);
  pinMode(LED_UPPER_THRESHOLD, OUTPUT);

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  snprintf(mqtt_cliente, 50, "ESP_%d", ESP.getChipId());
  Serial.print("Mi ID es ");
  Serial.println(mqtt_cliente);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

//called when receiving data from the subsribed topic
void callback(const char* topic, byte* payload, unsigned int length) {


  //FIX OVERFLOW malloc(length+1)
  strncpy(topic_json, (char*) payload, length);

  Serial.printf("%s\n", topic_json);

  //parse the JSON and turn on the corresponding LED

  DynamicJsonDocument topic_json_document(length*4);

  DeserializationError error = deserializeJson(topic_json_document, topic_json);

  //Handle error and show debug messages
  if(error) {
    Serial.printf("ERROR: Invalid JSON input from topic: <%s>\n", topic);
    Serial.println(error.c_str());
    return;
  }

  //turn on or off LEDs accordingly, show debug info
  led_upper_on = topic_json_document["highLed"];
  led_lower_on = topic_json_document["lowLed"];

  digitalWrite(LED_LOWER_THRESHOLD,
               led_lower_on ? HIGH : LOW);

  Serial.printf("Lower threshold overtaken: %d\n", led_lower_on);

  digitalWrite(LED_UPPER_THRESHOLD,
               led_upper_on ? HIGH : LOW);

  Serial.printf("Upper threshold overtaken: %d\n", led_upper_on);

  //get the basket height
  if(!topic_json_document["basketHeight"].isNull()){
    basket_height = topic_json_document["basketHeight"];
    Serial.printf("Basket height: %s cm\n", basket_height);
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(mqtt_cliente, mqtt_user, mqtt_pass, mqtt_distance, 0, 1, "Desconectado")) {
      Serial.println("connected");
      // Once connected, publish an announcement...

      client.publish(mqtt_distance, "Connected!", true);

      //subscribe to topics:

      if(client.subscribe(mqtt_threshold)) {
        Serial.println("Subscribed succesfully!");
      } else {
        Serial.println("Error subscribing!");
      }

      client.setCallback(callback);

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  digitalWrite(trigPin,LOW); //Por cuestión de estabilización del sensor
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); //envío del trigPin ultrasónico
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  tiempo = pulseIn(echoPin, HIGH);

  distance = (tiempo / 2) / 29.1;

  /*Monitorización en centímetros por el monitor serial*/
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  char distance_str[16];

  itoa(distance, distance_str, 10);
  client.publish(mqtt_distance, distance_str, true);

  delay(3000);
}