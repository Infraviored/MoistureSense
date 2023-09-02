#ifndef CONFIG_H
#define CONFIG_H

// fundamental config
extern const char *MQTT_DEVICE_NAME;
extern const char *commandTopic;
extern const char *stateTopic;

extern const char* ssid;
extern const char* password;
extern const char* mqtt_server;
extern const int mqtt_port;
extern const char* mqtt_user;
extern const char* mqtt_pass;

// other config
extern const int VALVE_PIN;
extern const int LED_PIN;

#endif