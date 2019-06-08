// Maker Fest Box --- Novi Sad, 2010

#include <Servo.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char*     WIFI_SSID          = "";    // WiFi Network Name
const char*     WIFI_PASSWORD      = "";    // WiFi Network Password
const char*     MQTT_USER          = "";    // Go to AllThingsTalk Maker > Devices > Your Device > Settings > Authentication > Device Tokens to get yours
const char*     DEVICE_ID          = "";    // Go to AllThingsTalk Maker > Devices > Your Device > Settings > Authentication > Device ID to get your Device ID

Servo servo;
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println();
  Serial.println("WiFi Connected!");
  client.setServer("api.allthingstalk.io", 1883);
  client.setCallback(callback);
}

void servoControl(bool state) {
  if (state == true) {
    servo.attach(D2);
    servo.write(10);
    delay(700);
    servo.detach();
    Serial.println("Box Unlocked");
  } else if (state == false) {
    servo.attach(D2);
    servo.write(150);
    delay(700);
    servo.detach();
    Serial.println("Box Locked");
  }
}

void callback(char* topic, byte* payload, unsigned int length) { 
  Serial.print("Message arrived on topic [");
  Serial.print(topic);
  Serial.println("] ");
  String convertedPayload;
  for (int i = 0; i < length; i++) {
    convertedPayload.concat((char)payload[i]);
  }
  //Serial.println("Value: ");
  //Serial.println(convertedPayload);
  StaticJsonDocument<500> doc;
  DeserializationError error = deserializeJson(doc, convertedPayload);
  if(!error) {
    bool value = doc["value"];
    Serial.println(value);
    servoControl(value);
  } else {
    Serial.println("Parsing JSON failed");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting to connect to AllThingsTalk...");
    if (client.connect("NodeMCU-2981", MQTT_USER, "arbitrary")) {
      Serial.println("Success! Connected to AllThingsTalk!");
      char topic[128];
      snprintf(topic, sizeof topic, "%s%s%s", "device/", DEVICE_ID, "/asset/+/command");
      Serial.println(topic);
      client.subscribe(topic);
    } else {
      Serial.print("Connection to AllThingsTalk Failed. Trying in 5 seconds. rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
