#ifndef SCHEDULEAPP_H
#define SCHEDULEAPP_H
#include <Apps/App.h>
#include <CoreFunc/servicepointers.h>
#include <CoreFunc/StartAppStruct.h>
#include <CoreFunc/IDstruct.h>
#include <HTTPClient.h>

#include <LinkedList.h>
class Scheduleapp : public App
{
private:
    int x = 0;
    int pages = 0;
    int currentpage = 0;
    LinkedList<String> *timeslots;
    LinkedList<String> *eventnames;
    

public:
    Scheduleapp(struct servicepointers s, String apname, StartAppStruct *n, bool *stopappflag, IDstruct *idcard) : App(s, apname, n, stopappflag, idcard){};
    void scheduleapphandler();
    void mainscreen();
};
#endif