#ifndef WINRES_H
#define WINRES_H
/*
Objective: Get screen resolusion
Platform: Windows
*/
#include <wtypes.h>
#include <iostream>
using namespace std;

class winRes{
public:
    int height;
    int width;
    winRes(){
        GetDesktopResolution(this);
    }
    winRes(int w, int h): width(w), height(h){}
    ~winRes(){}
    void printSize(){
        cout<<"Screen resolusion: "<<width<<'*'<<height<<endl;
    }

private:
    void GetDesktopResolution(winRes* screen)
    {
       RECT desktop;
       // Get a handle to the desktop window
       const HWND hDesktop = GetDesktopWindow();
       // Get the size of screen to the variable desktop
       GetWindowRect(hDesktop, &desktop);
       // The top left corner will have coordinates (0,0)
       // and the bottom right corner will have coordinates
       screen->width = desktop.right;
       screen->height = desktop.bottom;
    }
};

#endif // WINRES_H
