#ifndef PLOTIMGS_H
#define PLOTIMGS_H

#include <stdarg.h>
#include <array>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "winres.h"

#ifdef _WIN32
#include <wtypes.h>
#elif defined __APPLE__ || __MACH__
#include <ApplicationServices/ApplicationServices.h>
#elif defined __linux__
#include <X11/Xlib.h>
#endif


/* Objective: Plot several images in one figure
 *
 * cv::Mat subplot(const int n, const int resRow, const int resCol, double scl = 1.0, ...)
 *
 * Parameters:
 * n: number of input images
 * resRow: number of images in the vertical direction of output grid
 * resCol: number of images in the horizontal direction of output grid
 * scl: scaling factor of output image
 *
 * Example:
 * 1. Copy an image and scale it to twice of the size
 *    result = subplot(1, 1, 1, 2, &img) 
 * 2. Merge three images and scale it to half of the height and width
 *    img = subplot(3, 1, 3, 0.5, &img1, &img2, &img3)
 * 3. Display two images in one window and scale it to half of its original size
 *    cv::imshow("figure.1", subplot(2, 1, 2, 0.5, &img, &img2))
 *
 * void showImages(char* win_name, const int n, const int resRow, const int resCol, double scl, int msec, ...)
 *
 * Parameters:
 * win_name: name of the window
 * n: number of input images
 * resRow: number of images in the vertical direction of output grid
 * resCol: number of images in the horizontal direction of output grid
 * scl: scaling factor of output image
 * msec: waits for a pressed key (in milliseconds). msec = 0 means forever, msec < 0 means disable.
 *
 * Example:
 * 1. Display two images side-by-side and close window after 3 seconds
 *    showImages("pic.1", 2, 1, 2, 1, 3000, &sobel, &laplacian)
 *
 */

cv::Mat subplot(const int n, const int resRow, const int resCol, double scl = 1.0, ...){

    va_list va;
    va_start(va, scl);
    //std::cout<<h<<std::endl;
    cv::Mat *img, ROI, res;
    img = va_arg(va, cv::Mat*);
    int ctr=0;


    if(resRow<=0 && resCol<=0){
        int w=3, h=(n%w>0)? (n/w)+1 : n/w;
        if(n<w){
            w=n;
        }
        if(fmod(n,sqrt(n))==0 && n>1){
            w=sqrt(n), h=sqrt(n);
        }

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
    }else if(resRow >0 && resCol >0){
        if(img->channels()==1){
            res = cv::Mat(resRow*img->rows, resCol*img->cols, CV_8UC1, cv::Scalar::all(0));
        }else if(img->channels()==3){
            res = cv::Mat(resRow*img->rows, resCol*img->cols, CV_8UC3, cv::Scalar::all(0));
        }
        for(int r=0; r<resRow && ctr<n; r++){
            for(int c=0; c<resCol && ctr<n; c++){
                ROI = res(cv::Rect((img->cols)*c, (img->rows)*r, img->cols,img->rows));
                img->copyTo(ROI);
                img = va_arg(va, cv::Mat*);
                ctr++;
            }
        }
    }
    va_end(va);
    cv::resize(res, res, cv::Size(), scl, scl, CV_INTER_AREA);
    return res;
}

void showImages(char* win_name, const int n, const int resRow, const int resCol, double scl, int msec, ...){

    va_list va;
    va_start(va, msec);
    //std::cout<<h<<std::endl;
    cv::Mat *img, ROI, res;
    img = va_arg(va, cv::Mat*);
    int ctr=0;

    if(resRow<=0 && resCol<=0){
        int w=3, h=(n%w>0)? (n/w)+1 : n/w;
        if(n<w){
            w=n;
        }
        if(fmod(n,sqrt(n))==0 && n>1){
            w=sqrt(n), h=sqrt(n);
        }

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
    }else if(resRow >0 && resCol >0){
        if(img->channels()==1){
            res = cv::Mat(resRow*img->rows, resCol*img->cols, CV_8UC1, cv::Scalar::all(0));
        }else if(img->channels()==3){
            res = cv::Mat(resRow*img->rows, resCol*img->cols, CV_8UC3, cv::Scalar::all(0));
        }
        for(int r=0; r<resRow && ctr<n; r++){
            for(int c=0; c<resCol && ctr<n; c++){
                ROI = res(cv::Rect((img->cols)*c, (img->rows)*r, img->cols,img->rows));
                img->copyTo(ROI);
                img = va_arg(va, cv::Mat*);
                ctr++;
            }
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
