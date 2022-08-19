#include "./CoreFunc/Apphandler.h"

void homeapptask(void *para)
{
    Homeapp happ = *(Homeapp *)para;
    for (;;)
    {
        happ.homeapphandler();
        vTaskDelay(10);
    }
}

void dinoapptask(void *para)
{
    Dinoapp dapp = *(Dinoapp *)para;
    for (;;)
    {
        dapp.dinoapphandler();
        vTaskDelay(10);
    }
}

void scheduleapptask(void *para)
{
    Scheduleapp sapp = *(Scheduleapp *)para;
    for (;;)
    {
        sapp.scheduleapphandler();
        vTaskDelay(10);
    }
}

Apphandler::Apphandler(Timeservice *tmsp, Adafruit_SH1106G *oled, Keypadservice *ks, Apphandler *selfaph,IDstruct *id)
{
    Laucherapptask = NULL;
    otherapprunning = false;
    services.display = oled;
    services.tmsp = tmsp;
    // services.rotationinput = rip;
    services.keypadinput = ks;
    idcard = id;
    aph = selfaph;
    startappstruct.startapp = false;
    startappstruct.startingappname = "";
    hap = new Homeapp(services, "Homeapp", &startappstruct, &stopapp,id);
    dap = new Dinoapp(services,"Dinoapp",&startappstruct,&stopapp,id);
    sap = new Scheduleapp(services, "Scheduleapp",&startappstruct,&stopapp,id);
}

void Apphandler::startapp(char *s)
{
    Serial.println(s);
    if (top != NULL)
    {
        if (eTaskGetState(top->apptaskhandler) != eSuspended)
        {
            vTaskSuspend(top->apptaskhandler);
        }
    }
    if (strcmp(s, "Homeapp") == 0)
    {
        xTaskCreate(homeapptask, s, 6000, hap, 1, &Laucherapptask);
        push(Laucherapptask);
    }
    if (strcmp(s, "Scheduleapp") == 0)
    {
        xTaskCreate(scheduleapptask, s, 6000, hap, 1, &Laucherapptask);
        push(Laucherapptask);
    }
}

void Apphandler::quitapp()
{
    vTaskDelete(top->apptaskhandler);
    pop();
    vTaskResume(top->apptaskhandler);
}

void Apphandler::push(TaskHandle_t s)
{
    struct AppStackNode *temp;
    temp = new AppStackNode();
    temp->apptaskhandler = s;
    temp->link = top;
    top = temp;
}

void Apphandler::pop()
{
    struct AppStackNode *temp;
    if (top == NULL)
    {
        Serial.println(F("Nothing to Close"));
    }
    else
    {
        temp = top;
        top = top->link;
        temp->link = NULL;
        free(temp);
    }
}

void Apphandler::appflagchecker()
{
    if (startappstruct.startapp == true)
    {
        int n = startappstruct.startingappname.length() + 1;
        char newappname[n + 1];
        startappstruct.startingappname.toCharArray(newappname, n);
        startapp(newappname);
        startappstruct.startapp = false;
        startappstruct.startingappname = "";
    }
    if (stopapp == true)
    {
        quitapp();
        stopapp = false;
    }
}