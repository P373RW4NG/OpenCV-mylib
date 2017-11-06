#ifndef WINRES_H
#define WINRES_H
/*
Objective: Get screen resolusion
Platform: Windows
*/

#include <iostream>
#include <opencv2/core/core.hpp>

#ifdef _WIN32
#include <wtypes.h>
#elif defined __APPLE__ || __MACH__
#include <ApplicationServices/ApplicationServices.h>
#elif defined __linux__
#include <X11/Xlib.h>
#endif

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
        std::cout<<"Screen resolution(WxH): "<<width<<'*'<<height<<std::endl;
    }
    int const Height(){ return height; }
    int const Width(){ return width; }
    int const area(){ return height*width; }
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
    imgSize(int h, int w, int c):height(h), width(w), channel(c){}
    imgSize(winRes win): height(win.Height()), width(win.Width()), channel(3){}
    imgSize(cv::Mat img): height(img.rows), width(img.cols), channel(img.channels()) {}
    ~imgSize(){}
    int height, width, channel;
    int const area(){ return height*width; }
    void printSize(){
        if(channel<=0){
            throw "empty image data";
        }else{ std::cout<<"Screen resolution(WxHxD): "<<width<<'*'<<height<<'*'<<channel<<std::endl; }
    }
};

#endif // WINRES_H
