/* 
 * File:   ParallelBinarizationPthread.h
 * Author: vanderson
 *
 * Created on 9 de Junho de 2013, 22:00
 */

#include "Binarization.h"

using namespace std;
typedef struct _ARGS{
        Image *img;
        int i;
        int j;
        int iMax;
        int jMax;
        short thresh;
        int minMax;
}ARGS;

class ParallelBinarizationPthread : public Binarization {
public:
    ParallelBinarizationPthread(Image *im) : Binarization(im){
    int larguraImg = img->bih->biWidth;
    int faixa=img->bih->biHeight/4;
    for(int i=0;i<4;i++){
      argumentos[0].j = 0;
      argumentos[i].jMax = larguraImg;
      argumentos[i].i=i*faixa;
      argumentos[i].iMax=(i+1)*faixa;
    }
    };
    void run();
    
    short simpleThresholding(Image *img);
    short otsuThresholding(Image *img);
private:
    ARGS argumentos[4];


};


