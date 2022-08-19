#include "./Apps/App.h"

App::App(servicepointers s, String apname, StartAppStruct *n, bool *stopappflag, IDstruct *id)
{
    appservices.display = s.display;
    appservices.tmsp = s.tmsp;
    appservices.keypadinput = s.keypadinput;
    idcard = id;
    // appservices.rotationinput = s.rotationinput;
    newappstruct = n;
    stopapp = stopappflag;
    Appname = apname;
}

String App::getappname()
{
    if (Appname != "")
        ;
    return Appname;
}

void App::printat(int size, int x, int y, String s)
{
    appservices.display->setTextSize(size);
    appservices.display->setFont();
    appservices.display->setTextColor(SH110X_WHITE);
    appservices.display->setCursor(x, y);
    appservices.display->println(s);
    appservices.display->display();
}