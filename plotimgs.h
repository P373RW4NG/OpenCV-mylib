#ifndef PLOTIMGS_H
#define PLOTIMGS_H

#include <stdarg.h>
#include <array>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#ifdef _WIN32
#include <wtypes.h>
#elif defined __APPLE__ || __MACH__
#include <ApplicationServices/ApplicationServices.h>
#elif defined __linux__
#include <X11/Xlib.h>
#endif


/* Objective: Plot several images in one figure
 *
 * cv::Mat subplot(const int n, double scl = 1.0, ...)
 *
 * Parameters:
 * n: number of input images
 * scl: scaling factor of output image
 *
 * Example:
 * 1. result = subplot(1, 0.8, &img) // copy a image which has scale ratio of 0.8 of original image
 * 2. img = subplot(3, 0.5, &img1, &img2, &img3) // merge three images with half of height and width
 * 3. cv::imshow("figure.1", subplot(2, 0.5, &img, &img2)) // display two images in one window with half of its original size
 *
 * void showImages(char* win_name, const int n, double scl, int msec, ...)
 *
 * Parameters:
 * win_name: name of the window
 * n: number of input images
 * scl: scaling factor of output image
 * msec: waits for a pressed key (in milliseconds). msec = 0 means forever, msec < 0 means disable.
 *
 * Example:
 * 1. showImages("pic.1", 2, 1, &sobel, &laplacian)
 *
 */

class winRes{
public:
    int height;
    int width;
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
        std::cout<<"Screen resolusion: "<<width<<'*'<<height<<std::endl;
    }
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
    void printSize(){ std::cout<<"Screen resolusion: "<<width<<'*'<<height<<'*'<<channel<<std::endl; }
};

cv::Mat subplot(const int n, double scl = 1.0, ...){
    int w=3, h=(n%w>0)? (n/w)+1 : n/w;
    if(n<w){
        w=n;
    }
    if(fmod(n,sqrt(n))==0 && n>1){
        w=sqrt(n), h=sqrt(n);
    }
    va_list va;
    va_start(va, scl);
    //std::cout<<h<<std::endl;
    cv::Mat *img, ROI, res;
    img = va_arg(va, cv::Mat*);

    if(img->channels()==1){
        res = cv::Mat(h*img->rows, w*img->cols, CV_8UC1, cv::Scalar::all(0));
    }else if(img->channels()==3){
        res = cv::Mat(h*img->rows, w*img->cols, CV_8UC3, cv::Scalar::all(0));
    }
    for(int j=0; j<h; j++){
        if(j==h-1) w = (n%w>0)? n%w : w;
        for(int i=0; i<w; i++){
            ROI = res(cv::Rect((img->cols)*i, (img->rows)*j, img->cols,img->rows));
            img->copyTo(ROI);
            img = va_arg(va, cv::Mat*);
        }
    }
    va_end(va);
    cv::resize(res, res, cv::Size(), scl, scl, CV_INTER_AREA);
    return res;
}

void showImages(char* win_name, const int n, double scl, int msec, ...){
    int w=3, h=(n%w>0)? (n/w)+1 : n/w;
    if(n<w){
        w=n;
    }
    if(fmod(n,sqrt(n))==0 && n>1){
        w=sqrt(n), h=sqrt(n);
    }
    va_list va;
    va_start(va, msec);
    //std::cout<<h<<std::endl;
    cv::Mat *img, ROI, res;
    img = va_arg(va, cv::Mat*);

    if(img->channels()==1){
        res = cv::Mat(h*img->rows, w*img->cols, CV_8UC1, cv::Scalar::all(0));
    }else if(img->channels()==3){
        res = cv::Mat(h*img->rows, w*img->cols, CV_8UC3, cv::Scalar::all(0));
    }
    for(int j=0; j<h; j++){
        if(j==h-1) w = (n%w>0)? n%w : w;
        for(int i=0; i<w; i++){
            ROI = res(cv::Rect((img->cols)*i, (img->rows)*j, img->cols,img->rows));
            img->copyTo(ROI);
            img = va_arg(va, cv::Mat*);
        }
    }
    va_end(va);
    cv::resize(res, res, cv::Size(), scl, scl, CV_INTER_AREA);
    cv::namedWindow(win_name);
    cv::imshow(win_name, res);
    if(msec >= 0){
        cv::waitKey(msec);
    }
}

#endif // PLOTIMGS_H
