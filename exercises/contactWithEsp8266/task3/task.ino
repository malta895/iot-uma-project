/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 - Se conecta a la WiFi y al servidor de mensajes (broker) MQTT
 - Cada X segundos envía al topic master/holamundo un mensaje con el identificador ESP_#######

 - El LED se apaga con cada envío
 - Comprobar en el monitor serie los mensajes  de depuración
 - Comprobar en el IU de node-red que llegan los mensajes 

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"

// Update these with values suitable for your network.

const char* ssid = "MASTER";
const char* password = "malagaiot";

const char* mqtt_server = "iot.ac.uma.es";
const char* mqtt_user = "master";
const char* mqtt_pass = "malagaiot";

//TOPICS
const char* mqtt_dispositivo = "master/GRUPO_K/dispositivo";
const char* mqtt_order = "master/GRUPO_K/orden";
const char* mqtt_estado = "master/GRUPO_K/estado";

char mqtt_cliente[50];

DHTesp dht;

#define LED 2

WiFiClient espClient;
PubSubClient client(espClient);

int ledStatus = 0; //0 apaga, 1 enciende, 2 alterna

void callback(const char* topic, byte* payload, unsigned int length) {

  if(strncmp("enciende", (char*)payload, 8) == 0){
    ledStatus = 1;
    Serial.println((char*)payload);
    client.publish(mqtt_estado, "ON", true);
  } else if(strncmp("apaga", (char*)payload, 5) == 0) {
    ledStatus = 0;
    Serial.println((char*)payload);
    client.publish(mqtt_estado, "OFF", true);
  } else if(strncmp("alterna", (char*)payload, 7) == 0) {
    ledStatus = 2;
    Serial.println((char*)payload);

  } else {
    //error
    Serial.print("Message: ");
      Serial.print((char*)payload);
      Serial.print(" not recognized!");
  }
}

void setup() {
  pinMode(LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();

  client.setServer(mqtt_server, 1883);
  snprintf(mqtt_cliente, 50, "ESP_%d", ESP.getChipId());
  Serial.print("Mi ID es "); Serial.println(mqtt_cliente);

   dht.setup(5, DHTesp::DHT11); // Connect DHT sensor to GPIO 5



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

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(mqtt_cliente, mqtt_user, mqtt_pass, mqtt_dispositivo, 0, 1, "Desconectado")) {
      Serial.println("connected");
      // Once connected, publish an announcement...

      if(client.subscribe(mqtt_order)){
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

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();

  switch(ledStatus){
  case 0:
    digitalWrite(LED, HIGH);
    break;
  case 1:
    digitalWrite(LED, LOW);
    break;
  case 2:
    digitalWrite(LED,HIGH);
    client.publish(mqtt_estado, "OFF", true);
    delay(200);
    digitalWrite(LED,LOW);
    client.publish(mqtt_estado, "ON", true);
    break;
  default:
    Serial.println("LED status not recognized");
    break;
  }

  //Send retained "available" message
  client.publish(mqtt_dispositivo, "Disposable", true);


  delay(200);

}
