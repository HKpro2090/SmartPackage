#ifndef MQTTSERVICE_H
#define MQTTSERVICE_H
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#define MSG_BUFFER_SIZE (50)
class MQTTservice
{
    public:

    private:
    char *broker = "broker.mqttdashboard.com";
    int port = 1883;
    void callback();
};

#endif 