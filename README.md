# OpenCV-mylib

## macOS
>Qt .pro
>>LIBS += -framework ApplicationServices
>
>gcc
>> -framework ApplicationServices


Example:
showImages("HOG", 4, 1, 4, 0.5, 0, &img, &gammaNormalize, &sobelEdge, &HOG);
![hog](https://user-images.githubusercontent.com/29127069/37355665-3d9fc4c4-271f-11e8-98df-37f86db83039.png?raw=true)
