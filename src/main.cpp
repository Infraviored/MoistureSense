#include <Arduino.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "config.h"
#include "connection.h"

void handleMqttMessage(char *topic, byte *payload, unsigned int length);
void controlValve(unsigned long duration);
void monitorValve();

bool valveOpen = false;
unsigned long valveOpenTimestamp = 0;
const unsigned long MAX_VALVE_OPEN_DURATION = 300000; // 100 seconds in milliseconds
unsigned long currentValveOpenDuration = 0;           // Stores the desired open duration for the valve
unsigned long lastStatusTimestamp = 0;
const unsigned long STATUS_INTERVAL = 1000; // 1 second in milliseconds

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting up...");

  pinMode(VALVE_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(handleMqttMessage);

  setup_wifi();
  reconnect();

  Serial.println("Ready to water!");
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  monitorValve();
  delay(20);
}

void handleMqttMessage(char *topic, byte *payload, unsigned int length)
{
  String message = "";
  for (unsigned int i = 0; i < length; i++)
  {
    message += (char)payload[i];
  }
  String information_message = "Command \"" + message + "\" received on topic \"" + String(topic) + "\"";
  Serial.println(information_message);

  if (strcmp(topic, commandTopic) == 0)
  {
    if (message == "open_valve")
    {
      controlValve(100000); // Open for 100 seconds
    }
    else if (message == "close_valve")
    {
      controlValve(0); // Close immediately
    }
    else if (message == "10s")
    {
      controlValve(10000); // Open for 10 seconds
    }
    else if (message.startsWith("openfor_"))
    {
      // Extract the number after "openfor"
      int duration = message.substring(8).toInt(); // Convert the substring to an integer
      controlValve(duration * 1000);               // Assuming the duration is in seconds, so multiply by 1000 to get milliseconds
    }
    else
    {
      Serial.println("Command unknown");
    }
  }
}

void controlValve(unsigned long duration)
{
  if (duration > 0)
  {
    if (!valveOpen) // Only open the valve if it's not already open
    {
      if (duration > MAX_VALVE_OPEN_DURATION)
      {
        duration = MAX_VALVE_OPEN_DURATION;
      }

      valveOpen = true;
      valveOpenTimestamp = millis();
      currentValveOpenDuration = duration;

      digitalWrite(VALVE_PIN, HIGH);
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(LED_PIN, HIGH);
      client.publish(stateTopic, "valve_open");
      Serial.println("Valve opened");
    }
  }
  else
  {
    valveOpen = false;
    digitalWrite(VALVE_PIN, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LED_PIN, LOW);
    client.publish(stateTopic, "valve_closed");
    Serial.println("Valve closed");
  }
}

void monitorValve()
{
  if (valveOpen)
  {
    unsigned long elapsedTime = millis() - valveOpenTimestamp;

    if (elapsedTime > currentValveOpenDuration)
    {
      valveOpen = false;
      digitalWrite(VALVE_PIN, LOW);
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(LED_PIN, LOW);
      client.publish(stateTopic, "valve_closed");
      Serial.println("Valve closed");
    }
    else if (millis() - lastStatusTimestamp > STATUS_INTERVAL)
    {
      // Calculate remaining time and publish
      unsigned long remainingTime = (currentValveOpenDuration - elapsedTime) / 1000; // Convert to seconds
      String statusMessage = String(remainingTime);
      client.publish(stateTopic, statusMessage.c_str());
      lastStatusTimestamp = millis(); // Update the timestamp
    }
  }
}
