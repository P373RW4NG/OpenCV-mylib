#ifndef PLOTIMGS_H
#define PLOTIMGS_H
/*
Objective: Plot several images in one picture
*/
#include <stdarg.h>
#include <cmath>
#include "opencv2/core/core.hpp"

// This function can be called like this:
// img = subplot(1, 0.8, &img)
// or
// img = subplot(3, 0.5, &img1, &img2, &img3)
// or
// cv::imshow("figure.1", subplot(2, 0.5, &img, &img2))
// 
// No input image number limit
// No auto output image rescaling (add in the future)

cv::Mat subplot(int n, double scl, ...){
    int w=3, h=(n%w>0)? (n/w)+1 : n/w;
    if(n<w){
        w=n;
    }
    if(fmod(n,sqrt(n))==0 && (int)sqrt(n)>1){
        w=sqrt(n), h=sqrt(n);
    }
    va_list va;
    va_start(va, scl);

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
    cv::resize(res, res, cv::Size(), scl, scl);
    va_end(va);
    return res;
}
cv::Mat subplot(int n, ...){
    int w=3, h=(n%w>0)? (n/w)+1 : n/w;
    if(n<w){
        w=n;
    }
    if(fmod(n,sqrt(n))==0 && n>1){
        w=sqrt(n), h=sqrt(n);
    }
    va_list va;
    va_start(va, n);
    std::cout<<h<<std::endl;
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
    return res;
}

#endif // PLOTIMGS_H
