#pragma once
#include "Binarization.h"

using namespace std;
class SequentialBinarization : public Binarization{
public:
    SequentialBinarization(Image *im) : Binarization(im){};
    void run();
    short simpleThresholding(Image *img);
    short otsuThresholding(Image *img);
private:

};

