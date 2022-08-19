#include "Apps/Scheduleapp.h"

void Scheduleapp::scheduleapphandler()
{
    if(appscreencounter == -1)
    {
        mainscreen();
        appscreencounter++;
    }
    if(appscreencounter == 0)
    {
        
    }
}

void Scheduleapp::mainscreen()
{
    
    if(x == 0)
    {
        timeslots = new LinkedList<String>();
        eventnames = new LinkedList<String>();
        appservices.display->clearDisplay();
        // appservices.display->fillScreen(SH110X_BLACK);
        appservices.display->setFont(&FreeMono9pt7b);
        appservices.display->setTextSize(1);
        appservices.display->setTextColor(SH110X_WHITE, SH110X_BLACK);
        appservices.display->setCursor(0, 15);
        appservices.display->println(F("Schedule"));
        appservices.display->drawLine(0, 20, 128, 20, SH110X_WHITE);
        appservices.display->display();
        appservices.display->setFont();
        appservices.display->setCursor(0,22);
        x++;
    }
    if (x == 1)
    {
        HTTPClient http;
        bool httpInitResult = http.begin("http://0.tcp.in.ngrok.io:15224/schedule.php");
        if (httpInitResult == false)
        {
            appservices.display->setCursor(20, 30);
            appservices.display->println(F("Unknown Error. Try Again!"));
            Serial.println(F("http.begin() failed!")); // debug
        }
        else
        {
            int httpCode = http.GET();
            if (httpCode > 0)
            {
                myobject = JSON.parse(http.getString());
            }
            else
            {
                appservices.display->setCursor(20, 30);
                appservices.display->println(F("Unknown Error. Try Again!"));
                Serial.println(F("Error on HTTP request"));
            }
        }
        pages = myobject.length() / 4;
        Serial.println(ESP.getFreeHeap());
        http.end();
        http.~HTTPClient();
        Serial.println(ESP.getFreeHeap());
        x++;
    }
    if(x == 2)
    {
        for(int i = 0;i < myobject.length();i++)
        {
            timeslots->add(JSON.stringify(myobject[i]["time"]).substring(1,8));
            eventnames->add(JSON.stringify(myobject[i]["event_name"]));
            Serial.println(timeslots->get(i));
        }
        myobject.~JSONVar();
        x++;
    }
    if (x == 3)
    {
        for (int i = 0; i < 4; i++)
        {
            appservices.display->println(timeslots->get(i));
            Serial.println(timeslots->get(i));
        }
        appservices.display->display();
        x++;
    }
    if(x == 4)
    {
        if (appservices.keypadinput->longpressB)
        {
            *stopapp = true;
        }
        appservices.keypadinput->resetpressflags();
    }
}