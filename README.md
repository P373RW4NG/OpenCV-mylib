# OpenCV-mylib

## macOS
>Qt .pro
>>LIBS += -framework ApplicationServices
>
>gcc
>> -framework ApplicationServices


Example:
showImages("HOG", 4, 1, 4, 0.5, 0, &img, &gammaNormalize, &sobelEdge, &HOG);
![hog](https://user-images.githubusercontent.com/29127069/37452922-07f5b7c2-2871-11e8-94e3-1402e39946f4.png?raw=true)
