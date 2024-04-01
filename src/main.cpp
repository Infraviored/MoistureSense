#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "config.h"
#include "connection.h"

void performSensorReading();
int performOutlierDetectionAndAveraging(int arr[], int n);

// Time to sleep (in milliseconds)
// Default: 1 hour
unsigned long sleepTimeMs = 3600000;
// Test: 10 seconds
// unsigned long sleepTimeMs = 10000;

void setup()
{
  // Only run setup code once after waking from sleep
  Serial.begin(74880);
  Serial.println("Waking up...");

  // Initialize pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(SENSOR_VIN_PIN, OUTPUT);
  pinMode(SENSOR_OUT_PIN, INPUT);

  // Connect to WiFi and MQTT
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  reconnect();

  // Perform sensor reading and processing
  performSensorReading();

  // Go back to sleep
  Serial.println("Going to sleep...");
  Serial.flush();
  ESP.deepSleep(sleepTimeMs * 1000); // deepSleep takes microseconds
}

void loop()
{
  // This loop will never be executed because the ESP goes to sleep in the setup() function
}

void performSensorReading()
{
  digitalWrite(SENSOR_VIN_PIN, HIGH); // Power the sensor
  digitalWrite(LED_PIN, HIGH);        // Turn on the LED
  
  
  const int warmupReadings = 5;
  const int numReadings = 20;
  int readings[numReadings]; // Array to hold raw sensor readings

  // Warm up the sensor
  for (int i = 0; i < warmupReadings; i++)
  {
    analogRead(SENSOR_OUT_PIN);
    delay(100);
  }
  digitalWrite(LED_PIN, LOW); // Turn off the LED

  // Take multiple readings
  for (int i = 0; i < numReadings; i++)
  {
    readings[i] = analogRead(SENSOR_OUT_PIN);
    Serial.println(readings[i]);
    delay(100);
  }

  // Perform outlier detection and averaging here
  // ...
  int processedValue = performOutlierDetectionAndAveraging(readings, numReadings);

  // Publish to MQTT
  String payload = String(processedValue);
  client.publish(stateTopic, payload.c_str());

  // Turn off sensor
  digitalWrite(SENSOR_VIN_PIN, LOW);
}

int performOutlierDetectionAndAveraging(int arr[], int n)
{
  // For simplicity, let's just average all values for now.
  // You can add outlier detection logic here.

  int sum = 0;
  for (int i = 0; i < n; i++)
  {
    sum += arr[i];
  }

  return sum / n;
}
