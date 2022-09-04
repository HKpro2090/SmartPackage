#ifndef LISTVIEW_H
#define LISTVIEW_H
#include <Arduino.h>
#include <LinkedList.h>
#include <Adafruit_SH110X.h>
#include <GUIElements/Button.h>
#include <CoreFunc/Keypadservice.h>
class ListView
{
private:
    int listitemno = 0;
    int posX = 0;
    int posY = 0;
    int width = 0;
    int height = 0;
    int dividerWidth = 1;
    int paddingTop = 5;
    int paddingRight = 5;
    int paddingDown = 5;
    int paddingLeft = 5;
    int cellheight = 10;
    bool buttont = false;
    int selectedbt = 0;
    Adafruit_SH1106G *display;
    Keypadservice *input = NULL;
    LinkedList<String> *headlist = NULL;
    LinkedList<String> *subheadlist = NULL;
    Button btarr[4];

public:
    String selectedbtname = "";
    ListView(Keypadservice *t, Adafruit_SH1106G *d, LinkedList<String> *hlist, int x, int y, int w, int h,bool butorlist);
    ListView(Keypadservice *t, Adafruit_SH1106G *d, LinkedList<String> *hlist, LinkedList<String> *slist, int x, int y, int w, int h, bool butorlist);
    ListView(Keypadservice *t, Adafruit_SH1106G *d, LinkedList<Button> *hbtlist, int x, int y, int w, int h);
    ListView(Keypadservice *t, Adafruit_SH1106G *d, LinkedList<Button> *hbtlist, LinkedList<Button> *sbtlist, int x, int y, int w, int h);
    void setPadding(int vertical, int horizontal);
    void setPadding(int padd);
    void setPadding(int t, int l, int r, int d);
    void setdividerwidth(int d);
    void loadView();
    void loadbtView();
    void show();
    int lvbtupdatetask();
};

#endif