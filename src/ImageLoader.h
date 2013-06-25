#pragma once
#include "Image.h"
using namespace std;

class ImageLoader {
    
public:
    ImageLoader(string path);
    void load();
    virtual unsigned short **alocarMatriz(unsigned short **matriz)=0;
    Image::BITMAPFILEHEADER* bfh;
    Image::BITMAPINFOHEADER* bih;
    unsigned short **BLUE;
    unsigned short **GREEN;
    unsigned short **RED;
    unsigned short **COINS;
    string path;
    Image *image;
    int time;
private:
    
};


