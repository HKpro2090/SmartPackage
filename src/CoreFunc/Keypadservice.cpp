#include "./CoreFunc/Keypadservice.h"

Keypadservice::Keypadservice()
{
    pinMode(UP_BUTTON_PIN,INPUT_PULLUP);
    pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);
    pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);
    pinMode(A_BUTTON_PIN, INPUT_PULLUP);
    pinMode(B_BUTTON_PIN, INPUT_PULLUP);
}

void Keypadservice::buttonservice()
{
    currentStateUP = digitalRead(UP_BUTTON_PIN);
    currentStateDOWN = digitalRead(DOWN_BUTTON_PIN);
    currentStateLEFT = digitalRead(LEFT_BUTTON_PIN);
    currentStateRIGHT = digitalRead(RIGHT_BUTTON_PIN);
    currentStateA = digitalRead(A_BUTTON_PIN);
    currentStateB = digitalRead(B_BUTTON_PIN);

    if(lastStateUP == HIGH && currentStateUP == LOW)
        pressedTimeUP = millis();
    else if(lastStateUP == LOW && currentStateUP == HIGH)
    {
        releasedTimeUP = millis();
        long pressDuration = releasedTimeUP - pressedTimeUP;
        if(pressDuration < SHORT_PRESS_TIME)
        {
            shortpressUP = true;
            longpressUP = false;
            Serial.println("UP button Short Press");
            
        }
        if(pressDuration > LONG_PRESS_TIME)
        {
            shortpressUP = false;
            longpressUP = true;
            Serial.println("UP button Long Press");
        }
    }
    else if (lastStateDOWN == HIGH && currentStateDOWN == LOW)
        pressedTimeDOWN = millis();
    else if (lastStateDOWN == LOW && currentStateDOWN == HIGH)
    {
        releasedTimeDOWN = millis();
        long pressDuration = releasedTimeDOWN - pressedTimeDOWN;
        if (pressDuration < SHORT_PRESS_TIME)
        {
            shortpressDOWN = true;
            longpressDOWN = false;
            Serial.println("DOWN button Short Press");
        }
        if (pressDuration > LONG_PRESS_TIME)
        {
            shortpressDOWN = false;
            longpressDOWN = true;
            Serial.println("DOWN button Long Press");
        }
    }
    else if (lastStateLEFT == HIGH && currentStateLEFT == LOW)
        pressedTimeLEFT = millis();
    else if (lastStateLEFT == LOW && currentStateLEFT == HIGH)
    {
        releasedTimeLEFT = millis();
        long pressDuration = releasedTimeLEFT - pressedTimeLEFT;
        if (pressDuration < SHORT_PRESS_TIME)
        {
            shortpressLEFT = true;
            longpressLEFT = false;
            Serial.println("LEFT button Short Press");
        }
        if (pressDuration > LONG_PRESS_TIME)
        {
            shortpressLEFT = false;
            longpressLEFT = true;
            Serial.println("LEFT button Long Press");
        }
    }
    else if (lastStateRIGHT == HIGH && currentStateRIGHT == LOW)
        pressedTimeRIGHT = millis();
    else if (lastStateRIGHT == LOW && currentStateRIGHT == HIGH)
    {
        releasedTimeRIGHT = millis();
        long pressDuration = releasedTimeRIGHT - pressedTimeRIGHT;
        if (pressDuration < SHORT_PRESS_TIME)
        {
            shortpressRIGHT = true;
            longpressRIGHT = false;
            Serial.println("Right button Short Press");
        }
        if (pressDuration > LONG_PRESS_TIME)
        {
            shortpressRIGHT = false;
            longpressRIGHT = true;
            Serial.println("RIGHT button Long Press");
        }
    }
    else if (lastStateA == HIGH && currentStateA == LOW)
        pressedTimeA = millis();
    else if (lastStateA == LOW && currentStateA == HIGH)
    {
        releasedTimeA = millis();
        long pressDuration = releasedTimeA - pressedTimeA;
        if (pressDuration < SHORT_PRESS_TIME)
        {
            shortpressA = true;
            longpressA = false;
            Serial.println("A button Short Press");
        }
        if (pressDuration > LONG_PRESS_TIME)
        {
            shortpressA = false;
            longpressA = true;
            Serial.println("A button Long Press");
        }
    }
    else if (lastStateB == HIGH && currentStateB == LOW)
        pressedTimeB = millis();
    else if (lastStateB == LOW && currentStateB == HIGH)
    {
        releasedTimeB = millis();
        long pressDuration = releasedTimeB - pressedTimeB;
        if (pressDuration < SHORT_PRESS_TIME)
        {
            shortpressB = true;
            longpressB = false;
            Serial.println("B button Short Press");
        }
        if (pressDuration > LONG_PRESS_TIME)
        {
            shortpressB = false;
            longpressB = true;
            Serial.println("B button Long Press");
        }
    }
    lastStateUP = currentStateUP;
    lastStateDOWN = currentStateDOWN;
    lastStateLEFT = currentStateLEFT;
    lastStateRIGHT = currentStateRIGHT;
    lastStateA = currentStateA;
    lastStateB = currentStateB;
}

void Keypadservice::resetpressflags()
{
    shortpressUP = false;
    longpressUP = false;
    shortpressDOWN = false;
    longpressDOWN = false;
    shortpressLEFT = false;
    longpressLEFT = false;
    shortpressRIGHT = false;
    longpressRIGHT = false;
    shortpressA = false;
    longpressA = false;
    shortpressB = false;
    longpressB = false;
}