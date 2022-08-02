#ifndef WIFISERVICE_H
#define WIFISERVICE_H
#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <TFT_eSPI.h>
#define WIFI_TIMEOUT_MS 20000
#define WIFI_RECOVER_TIME_MS 30000

struct wifidet
{
    String wifiSSID;
    String ipaddr;
    int rssi;
    int encrypttype;
};

class WifiService
{
private:
    String savedssid[5] = {"", "", "", "", ""};
    String savedpasswd[5] = {"", "", "", "", ""};
    bool flag = false;
    struct wifidet wifidetails;
    TFT_eSPI *display;
    int returnSavedNetworks();
    void updateSavedNetworks(char *ssid, char *pass);

public:
    WifiService(TFT_eSPI *disp);
    // void static keepwifialive(WiFiEvent_t event, WiFiEventInfo_t info);
    void wifiscan();
    boolean connectwifi(const char *ssid, const char *pass);
    void bootwifi();
};
#endif