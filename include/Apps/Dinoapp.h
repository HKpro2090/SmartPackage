#ifndef DINOAPP_H
#define DINOAPP_H
#include <Apps/App.h>
#include <CoreFunc/servicepointers.h>
#include <CoreFunc/StartAppStruct.h>
#include <CoreFunc/IDstruct.h>
class Dinoapp : public App
{
    private:
    int x = 0;


    public:
    Dinoapp(struct servicepointers s, String apname, StartAppStruct *n, bool *stopappflag, IDstruct *idcard) : App(s, apname, n, stopappflag, idcard){};
    void dinoapphandler();

};
#endif