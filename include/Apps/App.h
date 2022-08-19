#ifndef APP_H
#define APP_H
#include <Arduino.h>
#include <CoreFunc/servicepointers.h>
#include <CoreFunc/StartAppStruct.h>
#include <CoreFunc/IDstruct.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Arduino_JSON.h>
class App
{
public:
    bool pause = false;
    bool stopped = false;
    int appscreencounter = -1;
    int screenpagecounter = 0;
    String Appname = "";
    bool *stopapp;
    servicepointers appservices;
    IDstruct *idcard;
    StartAppStruct *newappstruct;
    App(struct servicepointers s, String apname, StartAppStruct *n, bool *stopappflag, IDstruct *id);
    String getappname();
    void printat(int size, int x, int y, String s);
    JSONVar myobject;
};
#endif