#pragma once
#include "Image.h"

class CoinCounter {
    
public:
    CoinCounter(Image *im);
    virtual int run()=0;
    virtual void filtrar()=0;
    Image *img;
private:
    int executionTime;  

};

