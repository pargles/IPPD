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

class ParallelBinarization : public Binarization {
public:
    ParallelBinarization(Image *im) : Binarization(im){};
    void run();
private:

};

