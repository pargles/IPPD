#pragma once
#include "Image.h"

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

