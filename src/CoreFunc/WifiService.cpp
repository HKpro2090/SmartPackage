#include "./CoreFunc/WifiService.h"

WifiService::WifiService(TFT_eSPI *disp)
{
    display = disp;
    WiFi.mode(WIFI_STA);
}

int WifiService::returnSavedNetworks()
{
    char k = 0;
    char j = 0;
    File file = SPIFFS.open("/wifi.txt");
    if (!file)
        Serial.println(F("No saved networks available."));
    else
    {
        String a = file.readString();

        for (int i = 0; i < a.length(); i++)
        {
            char c = a.charAt(i);
            if (c != '\n')
            {
                if (j == 0)
                    savedssid[k].concat(c);
                else if (j == 1)
                    savedpasswd[k].concat(c);
            }
            else if (c == '\n')
            {
                if (j == 0)
                    j++;
                else if (j == 1)
                    j++;
                else
                {
                    j = 0;
                    k++;
                }
            }
        }
    }
    file.close();
    return k;
}

void WifiService::updateSavedNetworks(char *ssid, char *pass)
{
    File file = SPIFFS.open("/wifi.txt", FILE_APPEND);
    if (!file)
    {
        file = SPIFFS.open("/wifi.txt", FILE_WRITE);
    }
    file.println(ssid);
    file.println(pass);
    file.println();
    file.close();
    file = SPIFFS.open("/wifi.txt", FILE_READ);
    Serial.println(file.readString());
}

void WifiService::bootwifi()
{
    display->println(F("[WIFI] Reteriving Saved Networks"));
    int k = returnSavedNetworks();
    display->println(F("[WIFI] Scanning for Saved Networks"));
    int n = WiFi.scanNetworks();
    for (int i = 0; i <= k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (strcmp(savedssid[i].substring(0, savedssid[i].length() - 1).c_str(), WiFi.SSID(j).c_str()) == 0)
            {
                connectwifi(savedssid[i].substring(0, savedssid[i].length() - 1).c_str(), savedpasswd[i].substring(0, savedpasswd[i].length() - 1).c_str());
            }
        }
    }
}

boolean WifiService::connectwifi(const char *ssid, const char *pass)
{
    for (char i = 0; i < 2; i++)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            display->println(F("Already Connected"));
            return true;
        }
        // Serial.println(F("[WIFI] Connecting"));
        display->println(F("[WIFI] Connecting"));
        // Serial.println(ssid);
        // Serial.println(pass);
        WiFi.begin(ssid, pass);
        unsigned long startAttemptTime = millis();
        while (WiFi.status() != WL_CONNECTED &&
               millis() - startAttemptTime < WIFI_TIMEOUT_MS)
        {
        }
        if (WiFi.status() != WL_CONNECTED)
        {
            // Serial.println(F("[WIFI] FAILED"));
            display->println(F("WIFI Failed"));
            vTaskDelay(WIFI_RECOVER_TIME_MS / portTICK_PERIOD_MS);
            break;
        }
        else
        {
            // Serial.println(F("[WIFI] Connected"));
            display->println(F("[WIFI] Connected"));
            // Serial.println(WiFi.localIP());
            display->println(WiFi.localIP());
            wifidetails.wifiSSID.clear();
            wifidetails.wifiSSID.concat(ssid);
            wifidetails.ipaddr.clear();
            wifidetails.ipaddr.concat(WiFi.localIP());
            wifidetails.encrypttype = WiFi.encryptionType(0);
            wifidetails.rssi = WiFi.RSSI();
            return true;
        }
        return false;
    }
}
