#pragma once
#include <iostream>// cout
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <fstream>
 #include <omp.h>
#include "ImageLoader.h"
using namespace std;
class SequentialImageLoader : public ImageLoader {
public:
    SequentialImageLoader(string path) : ImageLoader(path){load();};
    unsigned short **alocarMatriz(unsigned short **matriz);
private:

};

