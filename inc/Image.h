#pragma once
#include <iostream>// cout
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <time.h>
 #include <omp.h>
#define PRETO 0
#define BRANCO 255
using namespace std;
 
class Image {
 
private:
   
    
public:
    #pragma pack(2)//The header needs to be 2 byte aligned.
    struct BITMAPFILEHEADER // File header
    {
        char bfType[2]; // File type: should be BM ( 0x42 0x4D ) 
        int bfSize; // File size in bytes
        short bfReserved1; // Reserved - for what i have no idea :P 
        short bfReserved2; // -||-
        int bfOffBits; // Offset, adress of the beginning of the information about image (pixels )
    };

    struct BITMAPINFOHEADER // Bitmap header
    {
        unsigned int biSize; // Size of this header
        unsigned int biWidth; // Width of image ( in pixels)
        unsigned int biHeight; // Height of this image ( in pixels )
        unsigned short biPlanes; // Numer of color planes, always 1
        unsigned short biBitCount; // Number of bytes for pixel. Possibility values :1,4,8,16, 24 and 32
        unsigned int biCompression; // Used compression (0 -none)
        unsigned int biSizeImage; // Size of image 
        signed int biXPelsPerMeter; // Horizontal resolution of the image (pixel per meter)
        signed int biYPelsPerMeter; // Vertical resolution of the image (pixel per meter)
        unsigned int biClrUsed; // Number of colors in the color palette, or 0 to default to 2^n ( 0- no palette)
        unsigned int biClrImportant; // Number of important colors used
    };  
    #pragma pack() // and this
    struct BITMAPFILEHEADER* bfh;
    struct BITMAPINFOHEADER* bih;
    Image(unsigned short **r, unsigned short **g, unsigned short **b, unsigned short **c, BITMAPFILEHEADER *bfh, BITMAPINFOHEADER *bih);
    void printarInformacoesDaImagem();
    void printarMatrizDeCor(unsigned short **matriz);
    void toGrayScale();
    void toGrayScaleParallel();
    void salvarImagemRGB(string nomeArquivo);
    void salvarImagemGrayScale(string nomeArquivo);
    void salvarImagemBlackAndWhite(string nomeArquivo);
    int posicaoCentral(int i,int j);
    int contarMoedas(int HeightStart, int HeightEnd);
    
    
    unsigned short **BLUE;
    unsigned short **GREEN;
    unsigned short **RED;
    unsigned short **COINS;
};
