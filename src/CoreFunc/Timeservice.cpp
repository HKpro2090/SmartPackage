#include "./CoreFunc/Timeservice.h"

Timeservice::Timeservice(long gmt,int daylight)
{
    gmtOffset_sec = gmt;
    daylightsavingoffset = daylight;
    //configtimezone();
}
void Timeservice::changetimezone(long gmt,int daylight)
{
    gmtOffset_sec = gmt;
    daylightsavingoffset = daylight;
}
void Timeservice::configtimezone()
{
    while(WiFi.status() != WL_CONNECTED)
    {}
    configTime(gmtOffset_sec, daylightsavingoffset, ntpServer);
}
void Timeservice::timeupdate()
{
  if(!getLocalTime(&timeinfo)){
    Serial.println(F("Failed to obtain time"));
  }
  //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  strftime(timeHour,3, "%H", &timeinfo);
  strftime(timeminute,3, "%M", &timeinfo);
  strftime(timesec,3, "%S", &timeinfo);
  strftime(timeday,4, "%A", &timeinfo);
  strftime(timemonth,4, "%B", &timeinfo);
  strftime(timedate,3, "%d", &timeinfo);
  
}
void Timeservice::showtime()
{
    //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}