#ifndef APPSTACKNODE_H
#define APPSTACKNODE_H
#include <Arduino.h>
struct AppStackNode
{
    TaskHandle_t apptaskhandler;
    struct AppStackNode *link;
};
#endif