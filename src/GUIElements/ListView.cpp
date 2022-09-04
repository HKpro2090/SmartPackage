#include "GUIElements/ListView.h"

ListView::ListView(Keypadservice *t, Adafruit_SH1106G *d, LinkedList<String> *hlist, int x, int y, int w, int h, bool butorlist)
{
    input = t;
    display = d;
    headlist = hlist;
    posX = x;
    posY = y;
    width = w;
    height = h;
    buttont = butorlist;
}

ListView::ListView(Keypadservice *t, Adafruit_SH1106G *d, LinkedList<String> *hlist, LinkedList<String> *slist, int x, int y, int w, int h, bool butorlist)
{
    input = t;
    display = d;
    headlist = hlist;
    subheadlist = slist;
    posX = x;
    posY = y;
    width = w;
    height = h;
    buttont = butorlist;
}

void ListView::setPadding(int vertical, int horizontal)
{
    paddingTop = vertical;
    paddingDown = vertical;
    paddingLeft = horizontal;
    paddingRight = horizontal;
}

void ListView::setPadding(int padd)
{
    paddingTop = padd;
    paddingDown = padd;
    paddingLeft = padd;
    paddingRight = padd;
}

void ListView::setPadding(int t, int l, int r, int d)
{
    paddingTop = t;
    paddingDown = d;
    paddingLeft = l;
    paddingRight = r;
}

void ListView::setdividerwidth(int d)
{
    dividerWidth = d;
}

void ListView::loadView()
{
    if(buttont)
    {
        for(int i = 0;i<headlist->size();i++)
        {
            btarr[i].display = display;
            btarr[i].x = posX + paddingLeft;
            btarr[i].y = posY + paddingTop + (cellheight * i);
            btarr[i].buttontext = headlist->get(i);
            if(i == selectedbt)
                btarr[i].highlighted();
            else
                btarr[i].unhighlighted();
            //display->drawLine(0, (posX+cellheight * (i + 1)), width, (cellheight * (i + 1)), SH110X_WHITE);
        }
    }
}

int ListView::lvbtupdatetask()
{
    if(input->shortpressUP)
    {
        selectedbt--;
        if(selectedbt <= -1)
        {
            selectedbt = 3;
        }
        Serial.println(selectedbt);
        //loadView();
        return 1;
    }
    if (input->shortpressDOWN)
    {
        selectedbt++;
        if (selectedbt >= 4)
        {
            selectedbt = 0;
        }
        Serial.println(selectedbt);
        //loadView();
        return 1;
    }
    if(input->shortpressA)
    {
        selectedbtname = btarr[selectedbt].buttontext;
        Serial.println("App open");
        return 2;
    }
    return 0;
}