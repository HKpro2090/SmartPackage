#include <Arduino.h>
#include <SPIFFS.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <CoreFunc/WifiService.h>
#include <CoreFunc/Timeservice.h>
#include <CoreFunc/Keypadservice.h>
#include <CoreFunc/Apphandler.h>
#include <CoreFunc/IDstruct.h>
#include <CoreFunc/RFIDservice.h>
Timeservice tms(19800, 0);
Timeservice *tmsp = &tms;
#define i2c_Address 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SH1106G oled = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SH1106G *display = &oled;
WifiService wifiserv = WifiService(display);
Keypadservice keys = Keypadservice();
Keypadservice *keypad = &keys;
IDstruct id = {"Harikrishnan Vamsi", "Analyst", "harikrishnanv", "1234567890","BC12"};
IDstruct *idcard = &id;
RFIDservice r;
RFIDservice *rfid = &r;
Apphandler aph(tmsp,display,keypad,&aph,rfid,idcard);

void apphandlerimptask(void *para)
{
  for (;;)
  {
    aph.appflagchecker();
    vTaskDelay(1);
  }
}

void setup() {
  //Wire.begin(14,15);
  Wire.begin(21,22);
  delay(250);
  display->begin(i2c_Address, true);
  display->clearDisplay();
  display->display();
  display->setCursor(0,0);
  display->setTextSize(1);
  display->setTextColor(SH110X_WHITE,SH110X_BLACK);
  display->println(F("Loading..."));
  display->display();
  Serial.begin(9600);
  display->println(F("Serial Debugger Established"));
  display->display();
  display->println(F("Mounting FileSystem ...."));
  display->display();
  if (!SPIFFS.begin(true))
  {
    display->println(F("An Error has occurred while mounting SPIFFS"));
  }

  else
  {
    display->println(F("Filesystem Mounted"));
  }
  display->display();
  delay(1000);
  // Wifi Service Established
  wifiserv.bootwifi();
  Serial.println(WiFi.macAddress());
  ArduinoOTA
      .onStart([]()
               {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";
      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      display->setTextSize(1);
      Serial.println("Start updating " + type); })
      .onEnd([]()
             { Serial.println("\nEnd"); })
      .onProgress([](unsigned int progress, unsigned int total)
                  { 
    display->setCursor(0,0);
    display->println(F("New Firmware Update"));
    display->drawLine(0,11,128,11,SH110X_WHITE);
    display->setCursor(0, 30);
    display->printf("Updating ... : %u%%\r", (progress / (total / 100)));
    display->display();
    display->clearDisplay();
    Serial.printf("Progress: %u%%\r", (progress / (total / 100))); })
      .onError([](ota_error_t error)
               {
    display->setCursor(0,0);
    display->println(F("OTA Update Failed"));
    display->setCursor(0, 30);
    display->clearDisplay();
    display->printf("Error[%u]: ", error);
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
    {
      display->setCursor(0, 40);
      display->println(F("Reason: Auth Failed"));
      Serial.println(F("Auth Failed"));
    }
    else if (error == OTA_BEGIN_ERROR)
    {
      display->setCursor(0, 40);
      display->println(F("Reason: Begin Failed"));
      Serial.println(F("Begin Failed"));
    }
    else if (error == OTA_CONNECT_ERROR)
    {
      display->setCursor(0, 40);
      display->println(F("Reason:Connect Failed"));
      Serial.println(F("Connect Failed"));
    }
    else if (error == OTA_RECEIVE_ERROR)
    {
      display->setCursor(0, 40);
      display->println(F("Reason: Receive Failed"));
      Serial.println(F("Receive Failed"));
    }
    else if (error == OTA_END_ERROR)
    {
      display->setCursor(0, 40);
      display->println(F("Reason: End Failed"));
      Serial.println(F("End Failed"));
    }
    });
  ArduinoOTA.begin();
  display->clearDisplay();
  display->display();
  xTaskCreate(apphandlerimptask, "Apphandler", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  aph.startapp("Homeapp");
}

void loop() {
  keypad->buttonservice();
  ArduinoOTA.handle();
}