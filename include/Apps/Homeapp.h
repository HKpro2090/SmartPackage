#ifndef HOMEAPP_H
#define HOMEAPP_H
#include <Apps/App.h>
#include <CoreFunc/servicepointers.h>
#include <CoreFunc/StartAppStruct.h>
#include <CoreFunc/IDstruct.h>
#include <GUIElements/Button.h>
#include <GUIElements/ListView.h>
class Homeapp : public App
{
private:
    int x = 0;
    LinkedList<String> *menubts;
    ListView *lv;
    
public:
    Homeapp(struct servicepointers s, String apname, StartAppStruct *n, bool *stopappflag,IDstruct *idcard) : App(s, apname, n, stopappflag,idcard){};
    void homeapphandler();
    void homescreen();
    void menuscreen();
};
#endif