#pragma once
#include "Binarization.h"

using namespace std;

class ParallelBinarization : public Binarization {
public:
    ParallelBinarization(Image *im) : Binarization(im){};
    void run();
    short simpleThresholding(Image *img);
    short otsuThresholding(Image *img);
private:

};

