#include "CoreFunc/RFIDservice.h"

RFIDservice::RFIDservice()
{
    rfid = new MFRC522(SS_PIN,RST_PIN);
    SPI.begin();
    rfid->PCD_Init();
}

String RFIDservice::readrfiduid()
{
    if(rfid->PICC_IsNewCardPresent())
    {
        if(rfid->PICC_ReadCardSerial())
        {
            MFRC522::PICC_Type piccType = rfid->PICC_GetType(rfid->uid.sak);
            Serial.print("RFID/NFC Tag Type: ");
            Serial.println(rfid->PICC_GetTypeName(piccType));
            Serial.print("UID:");
            String hexstring = "";
            for (int i = 0; i < rfid->uid.size; i++)
            {
                hexstring+=String(rfid->uid.uidByte[i],HEX);
            }
            Serial.println(hexstring);
            return hexstring;
        }
    }
    return "";
}