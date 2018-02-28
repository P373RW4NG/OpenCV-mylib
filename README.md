# OpenCV-mylib

## macOS
>Qt .pro
>>LIBS += -framework ApplicationServices
>
>gcc
>> -framework ApplicationServices

Example:
showImages("HOG", 4, 1, 4, 0.5, 0, &img, &gammaNormalize, &sobelEdge, &HOG);

