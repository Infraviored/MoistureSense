#include "config.h"
#include <ESP8266WiFi.h>

// fundamental config
//! IMPORTANT! RENAME!
const char *MQTT_DEVICE_NAME = "WaterValve";

String sCommandTopic = String(MQTT_DEVICE_NAME) + "/commands";
String sStateTopic = String(MQTT_DEVICE_NAME) + "/state";
const char *commandTopic = sCommandTopic.c_str();
const char *stateTopic = sStateTopic.c_str();

// other config
const int VALVE_PIN = D2;
const int LED_PIN = D1;