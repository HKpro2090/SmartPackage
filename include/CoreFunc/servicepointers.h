#ifndef SERVICEPOINTERS_H
#define SERVICEPOINTERS_H
#include <Arduino.h>
#include <CoreFunc/Timeservice.h>
#include <CoreFunc/Keypadservice.h>
#include <CoreFunc/Timeservice.h>
#include <CoreFunc/WifiService.h>
#include <Adafruit_SH110X.h>
#include <SD.h>

struct servicepointers
{
    Timeservice *tmsp;
    Adafruit_SH1106G *display;
    // RotaryInput *rotationinput;
    Keypadservice *keypadinput;
};

#endif