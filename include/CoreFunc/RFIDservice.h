#ifndef RFIDSERVICE_H
#define RFIDSERVICE_H
#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>

class RFIDservice
{
    private:
    uint8_t RST_PIN = 2;
    uint8_t SS_PIN = 15;
    MFRC522 *rfid;
    public:
    RFIDservice();
    String readrfiduid();
};
#endif