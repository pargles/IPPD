#pragma once
#include "ImageLoader.h"
using namespace std;
class ParallelImageLoader : public ImageLoader{
public:
    ParallelImageLoader(string path):ImageLoader(path){load();};
    virtual unsigned short **alocarMatriz(unsigned short **matriz);
private:

};

