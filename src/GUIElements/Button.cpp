#include "GUIElements/Button.h"

Button::Button(Adafruit_SH1106G *oled,String btname,int xcord, int ycord,int btsize)
{
    display = oled;
    buttontext = btname;
    buttonid = esp_random();
    x = xcord;
    y = ycord;
    size = btsize;
}

Button::Button()
{
}

void Button::unhighlighted()
{
    display->setTextColor(SH110X_BLACK,SH110X_BLACK);
    display->setCursor(x, y);
    display->print(F(">"));
    display->setTextColor(SH110X_WHITE,SH110X_BLACK);
    display->setCursor(x+10, y);
    display->print(F(buttontext.c_str()));
    //display->display();

}

void Button::highlighted()
{
    // display->setTextSize(size);
    // display->setFont();
    display->setTextColor(SH110X_WHITE,SH110X_BLACK);
    display->setCursor(x, y);
    display->print(F(">"));
    display->setTextColor(SH110X_WHITE,SH110X_BLACK);
    display->setCursor(x + 10, y);
    display->print(buttontext);
    //display->display();
}
int Button::clicked()
{
    display->setTextSize(size);
    display->setFont();
    display->setTextColor(SH110X_BLACK,SH110X_WHITE);
    display->setCursor(x, y);
    display->print(F(">"));
    display->setTextColor(SH110X_BLACK, SH110X_WHITE);
    display->setCursor(x + 10, y);
    display->print(buttontext);
    display->display();
    return buttonid;
}