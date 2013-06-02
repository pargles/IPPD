#pragma once
#include "Image.h"
#include <cstdio>
#include <iostream>//cout

class Binarization {
    
public:
    Binarization(Image *im);
    virtual void run()=0;
    Image *img;
private:
    int executionTime;  

};

