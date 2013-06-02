#pragma once
#include "Image.h"
#include <cstdio>
#include <iostream>//cout

class Binarization {
    
public:
    Binarization(Image *im);
    virtual void run()=0;
    virtual short simpleThresholding(Image *img)=0;
    virtual short otsuThresholding(Image *img)=0;
    Image *img;
private:
    int executionTime;  

};

