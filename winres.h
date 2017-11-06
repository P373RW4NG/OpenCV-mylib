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
    int height;
    int width;
public:
    winRes(){
#if defined _WIN32
        GetDesktopResolution(this);
#elif defined __APPLE__ || __MACH__
        CGDirectDisplayID id = CGMainDisplayID();
        width = CGDisplayPixelsHigh(id);
        height = CGDisplayPixelsWide(id);
#elif defined __linux__
        Display* disp = XOpenDisplay(NULL);
        //Screen* scrn = DefaultScreenOfDisplay(disp);
        //width = scrn->width;
        //height = scrn->height;
        //Display *display = XGetMainDisplay(NULL);
        const int scrn = DefaultScreen(disp);
        width = DisplayWidth(disp, scrn);
        height = DisplayHeight(disp, scrn);
#endif
    }
    winRes(int w, int h): width(w), height(h){}
    ~winRes(){}
    void printSize(){
        std::cout<<"Screen resolution: "<<width<<'*'<<height<<std::endl;
    }
    int const Height(){ return height; }
    int const Width(){ return width; }
private:
    #if defined _WIN32
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
#endif
};

class imgSize{
public:
    imgSize():height(0), width(0), channel(0){}
    ~imgSize(){}
    int height, width, channel;
    int area(){ return height*width; }
    void printSize(){ std::cout<<"Screen resolution: "<<width<<'*'<<height<<'*'<<channel<<std::endl; }
};

#endif // WINRES_H
