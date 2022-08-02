#include <Arduino.h>
#include <Wire.h>
#include <TFT_eSPI.h>
#include <SPIFFS.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <CoreFunc/WifiService.h>
#include <CoreFunc/Timeservice.h>
Timeservice tms(19800, 0);
Timeservice *tmsp = &tms;
TFT_eSPI tft = TFT_eSPI();
TFT_eSPI *display = &tft;
WifiService wifiserv = WifiService(display);

void setup() {
  
  // Start Display
  display->init();
  display->setRotation(1);
  display->fillScreen(TFT_BLACK);
  // display->setCursor(55,113);
  display->setCursor(0, 0);
  display->setTextColor(TFT_WHITE, TFT_BLACK);
  display->setTextSize(1);
  display->println(F("Loading..."));
  Serial.begin(9600);
  display->println(F("Serial Debugger Established"));
  // display->drawNumber(ESP.getPsramSize(),0,50);
  // display->drawNumber(ESP.getFreePsram(), 0, 100);
  display->println(F("Mounting FileSystem ...."));
  if (!SPIFFS.begin(true))
  {
    display->println(F("An Error has occurred while mounting SPIFFS"));
  }
  else
  {
    display->println(F("Filesystem Mounted"));
  }
  delay(1000);
  //Wifi Service Established
  wifiserv.bootwifi();
  // tms.configtimezone();
  // tms.timeupdate();
  ArduinoOTA
      .onStart([]()
               {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type); })
      .onEnd([]()
             { Serial.println("\nEnd"); })
      .onProgress([](unsigned int progress, unsigned int total)
                  { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); })
      .onError([](ota_error_t error)
               {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed"); });

  ArduinoOTA.begin();
}

void loop() {
  ArduinoOTA.handle();
}