/* 
 * File:   ParallelBinarizationPthread.h
 * Author: vanderson
 *
 * Created on 9 de Junho de 2013, 22:00
 */


#include <iostream>// cout
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <fstream>

#include "Binarization.h"
#include <time.h>


using namespace std;
typedef struct _ARGS{
        Image *img;
        int i;
        int j;
        int iMax;
        int jMax;
        short thresh;
}ARGS;

class ParallelBinarizationPthread : public Binarization {
public:
    ParallelBinarizationPthread(Image *im) : Binarization(im){
    int larguraImg = img->bih->biWidth;
    int alturaImg = img->bih->biHeight;
    
    //primeiro quadrante
    argumentos[0].j = 0;
    argumentos[0].i = 0;
    argumentos[0].jMax = larguraImg - (larguraImg / 2);
    argumentos[0].iMax = alturaImg - (alturaImg / 2);
    //segundo quadrante
    argumentos[1].j = larguraImg - (larguraImg / 2);
    argumentos[1].i = 0;
    argumentos[1].jMax = larguraImg;
    argumentos[1].iMax = alturaImg - (alturaImg / 2);
    //terceiro quadrante
    argumentos[2].j = 0;
    argumentos[2].i = alturaImg - (alturaImg / 2);
    argumentos[2].jMax = larguraImg - (larguraImg / 2);
    argumentos[2].iMax = alturaImg;
    //quarto quadrante
    argumentos[3].j = larguraImg - (larguraImg / 2);
    argumentos[3].i = alturaImg - (alturaImg / 2);
    argumentos[3].jMax = larguraImg;
    argumentos[3].iMax = alturaImg;
    
    };
    void run();
    
    short simpleThresholding(Image *img);
    short otsuThresholding(Image *img);
private:
    ARGS argumentos[4];


};


