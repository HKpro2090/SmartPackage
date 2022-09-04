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
        mainscreen();
    }
    if (appservices.keypadinput->longpressB)
    {
        appservices.display->fillScreen(SH110X_BLACK);
        appscreencounter = 0;
        screenpagecounter=1;
        *stopapp = true;
    }
    appservices.keypadinput->resetpressflags();
}

void Scheduleapp::mainscreen()
{
    
    if(x == 1)
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
        
        x++;
    }
    if (x == 0)
    {
        HTTPClient http;
        bool httpInitResult = http.begin("http://0.tcp.in.ngrok.io:19192/schedule.php");
        if (httpInitResult == false)
        {
            appservices.display->setCursor(20, 30);
            appservices.display->println(F("Unknown Error. Try Again!"));
            // Serial.println(F("http.begin() failed!")); // debug
            x = 100;
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
                appservices.display->setCursor(20,40);
                appservices.display->println(F("Unknown Error. Try Again!"));
                // Serial.println(F("Error on HTTP request"));
                x = 100;
            }
        }
        pages =(myobject.length() / 3)+1;
        // Serial.println(pages);
        currentpage = 0;
        // Serial.println(ESP.getFreeHeap());
        http.end();
        http.~HTTPClient();
        // Serial.println(ESP.getFreeHeap());
        x++;
    }
    if(x == 2)
    {
        for(int i = 0;i < myobject.length();i++)
        {
            timeslots->add(JSON.stringify(myobject[i]["time"]));
            eventnames->add(JSON.stringify(myobject[i]["event_name"]));
        }
        for(int i = 0; i < (timeslots->size()%3);i++)
        {
            timeslots->add("");
            eventnames->add("");
        }
        myobject.~JSONVar();
        x++;
    }
    if (x == 3)
    {
        appservices.display->fillRect(0,22,128,64,SH110X_BLACK);
        appservices.display->setCursor(0, 22);
        for (int i = (currentpage*3); i < (currentpage+1)*3; i++)
        {
            appservices.display->printf("%s %s\n\n",timeslots->get(i).substring(1, 6),eventnames->get(i).substring(1,eventnames->get(i).length()-1));
            // Serial.println(timeslots->get(i));
        }
        appservices.display->display();
        x++;
    }
    if(x == 4)
    {
        if(appservices.keypadinput->shortpressDOWN)
        {
            currentpage++;
            if(currentpage >= pages)
            {
                currentpage = 0;
            }
            x = 3;
        }
        if (appservices.keypadinput->shortpressUP)
        {
            currentpage--;
            if (currentpage <= -1)
            {
                currentpage = pages-1;
            }
            x = 3;
        }
    }
}