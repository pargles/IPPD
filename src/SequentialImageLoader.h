#pragma once
#include "ImageLoader.h"
using namespace std;
class SequentialImageLoader : public ImageLoader {
public:
    SequentialImageLoader(string path) : ImageLoader(path){load();};
    unsigned short **alocarMatriz(unsigned short **matriz);
private:

};

