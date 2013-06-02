#pragma once
#include <iostream>// cout
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <fstream>
 #include <omp.h>
#include "Binarization.h"
using namespace std;
class SequentialBinarization : public Binarization{
public:
    SequentialBinarization(Image *im) : Binarization(im){};
    void run();
private:

};

