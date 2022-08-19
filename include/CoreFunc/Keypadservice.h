#ifndef KEYPADSERVICE_H
#define KEYPADSERVICE_H
#include <Arduino.h>
#define UP_BUTTON_PIN 27
#define DOWN_BUTTON_PIN 26
#define LEFT_BUTTON_PIN 25
#define RIGHT_BUTTON_PIN 33
#define A_BUTTON_PIN 4
#define B_BUTTON_PIN 32

class Keypadservice
{
    private:
    int currentStateUP;
    int currentStateDOWN;
    int currentStateLEFT;
    int currentStateRIGHT;
    int currentStateA;
    int currentStateB;
    int lastStateUP = LOW;
    int lastStateDOWN = LOW;
    int lastStateLEFT = LOW;
    int lastStateRIGHT = LOW;
    int lastStateA = LOW;
    int lastStateB = HIGH;
    unsigned long pressedTimeUP = 0;
    unsigned long releasedTimeUP = 0;
    unsigned long pressedTimeDOWN = 0;
    unsigned long releasedTimeDOWN = 0;
    unsigned long pressedTimeLEFT = 0;
    unsigned long releasedTimeLEFT = 0;
    unsigned long pressedTimeRIGHT = 0;
    unsigned long releasedTimeRIGHT = 0;
    unsigned long pressedTimeA = 0;
    unsigned long releasedTimeA = 0;
    unsigned long pressedTimeB = 0;
    unsigned long releasedTimeB = 0;
    const int SHORT_PRESS_TIME = 500;
    const int LONG_PRESS_TIME = 500;
    public:
    bool shortpressUP = false;
    bool longpressUP = false;
    bool shortpressDOWN = false;
    bool longpressDOWN = false;
    bool shortpressLEFT = false;
    bool longpressLEFT = false;
    bool shortpressRIGHT = false;
    bool longpressRIGHT = false;
    bool shortpressA = false;
    bool longpressA = false;
    bool shortpressB = false;
    bool longpressB = false;
    Keypadservice();
    void buttonservice();
    void resetpressflags();
};
#endif