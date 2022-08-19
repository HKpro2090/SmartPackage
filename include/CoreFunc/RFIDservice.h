#ifndef RFIDSERVICE_H
#define RFIDSERVICE_H
#include <Arduino.h>
#include <MFRC522.h>
#include <Wire.h>

class RFIDservice
{
    private:
    uint8_t RST_PIN = 4;
    TwoWire *i2cBus;
    MFRC522_I2C *dev;
    MFRC522 *mfrc522;
    public:
    RFIDservice();
};
#endif