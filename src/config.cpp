#include "config.h"
#include <ESP8266WiFi.h>

// fundamental config
//! IMPORTANT! RENAME!
const char *MQTT_DEVICE_NAME = "MoistureSensor1";

String sStateTopic = String(MQTT_DEVICE_NAME) + "/state";
const char *stateTopic = sStateTopic.c_str();

// other config
const int SENSOR_VIN_PIN = D2;
const int SENSOR_OUT_PIN = A0;
const int LED_PIN = D1;