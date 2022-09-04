#ifndef APPHANDLER_H
#define APPHANDLER_H
#include <Arduino.h>
#include <CoreFunc/Timeservice.h>
#include <Adafruit_SH110X.h>
#include <CoreFunc/servicepointers.h>
#include <CoreFunc/AppStackNode.h>
#include <CoreFunc/StartAppStruct.h>
#include <CoreFunc/IDstruct.h>
#include <Apps/Homeapp.h>
#include <Apps/Dinoapp.h>
#include <Apps/Scheduleapp.h>


class Apphandler
{
private:
    TaskHandle_t Laucherapptask;
    TaskHandle_t Pollsapp;
    struct servicepointers services;
    struct AppStackNode *top = NULL;
    StartAppStruct startappstruct;
    IDstruct *idcard;
    bool stopapp = false;
    Homeapp *hap;
    Dinoapp *dap;
    Scheduleapp *sap;


public:
    Apphandler *aph;
    bool otherapprunning;
    Apphandler(Timeservice *tmsp, Adafruit_SH1106G *oled, Keypadservice *ks, Apphandler *selfaph,RFIDservice *rfid,IDstruct *id);
    void appstackhandler();
    void updateservicepointer();
    void push(TaskHandle_t s);
    void startapp(char *s);
    void pop();
    void quitapp();
    void appflagchecker();
};
#endif