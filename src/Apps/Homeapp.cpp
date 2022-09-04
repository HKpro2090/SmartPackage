#include "Apps/Homeapp.h"

void Homeapp::homeapphandler()
{
    if(appscreencounter == -1)
    {
        menubts = new LinkedList<String>();
        menubts->add("Schedule Watcher");
        menubts->add("Feedback Filler");
        menubts->add("Share");
        menubts->add("Extra");
        lv = new ListView(appservices.keypadinput, appservices.display, menubts, 0, 22, 128, 42, true);
        homescreen();
        appscreencounter++;
    }
    if(appscreencounter == 0)
    {
        if (appservices.keypadinput->shortpressUP && screenpagecounter == 0)
        {
            screenpagecounter = 0;
            homescreen();
        }

        if(appservices.keypadinput->shortpressDOWN && screenpagecounter == 0)
        {
            screenpagecounter = 1;
            homescreen();
        }
        if (appservices.keypadinput->shortpressUP && screenpagecounter == 1)
        {
            screenpagecounter = 0;
            homescreen();
        }
        if(appservices.keypadinput->shortpressA)
        {
            screenpagecounter = 0;
            appscreencounter  = 1;
            Serial.print("Menu open");
            appservices.keypadinput->resetpressflags();
        }
        
    }
    if (appscreencounter == 1)
    {
        appscreencounter++;
    }
    if(appscreencounter == 2)
    {
        menuscreen();
        if (appservices.keypadinput->shortpressB)
        {
            screenpagecounter = 0;
            appscreencounter = -1;
            x = 0;
            menubts->clear();
            Serial.print("Menu close");
        }
    }
    appservices.keypadinput->resetpressflags();
    // Serial.println(appscreencounter);
}

void Homeapp::homescreen()
{
    if(screenpagecounter == 0)
    {
        appservices.display->fillScreen(SH110X_BLACK);
        appservices.display->setFont(&FreeMono9pt7b);
        appservices.display->setTextSize(0);
        appservices.display->setTextColor(SH110X_WHITE);
        appservices.display->setCursor(0,15);
        appservices.display->println(F(idcard->name));
        appservices.display->drawLine(0,40,128,40,SH110X_WHITE);
        printat(1,0,45,F(idcard->designation));
        printat(1, 0, 55, F(idcard->phoneno));
        
    }
    if(screenpagecounter == 1)
    {
        appservices.display->fillScreen(SH110X_BLACK);
        appservices.display->setFont();
        appservices.display->setTextSize(1);
        appservices.display->setTextColor(SH110X_WHITE);
        appservices.display->setCursor(0,10);
        appservices.display->print(F(idcard->emailid));
        appservices.display->println(F("@kpmg.com"));
        appservices.display->println(WiFi.macAddress());
        // printat(1, 0, 30, F(idcard->emailid));
        appservices.display->display();
    }
}

void Homeapp::menuscreen()
{
    if(screenpagecounter == 0)
    {
        if(x == 0)
        {
            appservices.display->clearDisplay();
            // appservices.display->fillScreen(SH110X_BLACK);
            appservices.display->setFont(&FreeMono9pt7b);
            appservices.display->setTextSize(0);
            appservices.display->setTextColor(SH110X_WHITE,SH110X_BLACK);
            appservices.display->setCursor(0, 15);
            appservices.display->println(F("Menu"));
            appservices.display->drawLine(0, 20, 128, 20, SH110X_WHITE);
            //appservices.display->display();
            x++;
        }
        if(x == 1)
        {
            appservices.display->setFont();
            appservices.display->setTextSize(1);
            appservices.display->setTextColor(SH110X_WHITE, SH110X_BLACK);
            // appservices.display->setCursor(10, 22);
            // appservices.display->println(F("Schedule Watcher"));
            // appservices.display->println(F("Feedback Filler"));
            // appservices.display->println(F("Share"));
            // appservices.display->println(F("Extra"));
            lv->loadView();
            appservices.display->display();
            x++;
        }
        if(x == 2)
        {
            int change = lv->lvbtupdatetask();
            if(change == 1)
            {
                x = 0;
            }
            if(change == 2)
            {
                appscreencounter=-1;
                screenpagecounter = 0;
                x = 0;
                newappstruct->startingappname = lv->selectedbtname.c_str();
                menubts->~LinkedList();
                newappstruct->startapp = true;
            }
        }
    }
}