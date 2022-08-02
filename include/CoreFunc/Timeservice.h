#ifndef TIMESERVICE_H
#define TIMESERVICE_H
#include <Arduino.h>
#include <time.h>
#include <WiFi.h>
class Timeservice
{
    private:
    const char* ntpServer = "pool.ntp.org";
    long gmtOffset_sec;
    int daylightsavingoffset;
    //struct tm timeinfo;
    bool wificonnected;
    public:
    char timeHour[3];
    char timeminute[3];
    char timesec[3];
    char timeday[4];
    char timemonth[4];
    char timedate[3];
    struct tm timeinfo;
    bool timerec;
    Timeservice(long gmt,int daylight);
    void configtimezone();
    void changetimezone(long gmt,int daylight);
    void timeupdate();
    void showtime();
};
#endif