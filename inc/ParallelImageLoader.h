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
class ParallelImageLoader : public ImageLoader{
public:
    ParallelImageLoader(string path):ImageLoader(path){load();};
    virtual unsigned short **alocarMatriz(unsigned short **matriz);
private:

};

