#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>
#include <Adafruit_SH110X.h>
class Button
{
private:
public:
    int x;
    int y;
    int size;
    int buttonid;
    String buttontext;
    Adafruit_SH1106G *display;
    Button(Adafruit_SH1106G *oled,String btname,int xcord,int ycord,int btsize);
    Button(  );

    void highlighted();
    int clicked();
    void unhighlighted();
    void putbtname();
};
#endif