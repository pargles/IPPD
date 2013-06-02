/* 
 * File:   SequentialBinarization.cpp
 * Author: Stephano
 * 
 * Created on 1 de Junho de 2013, 22:35
 */

#include "../inc/SequentialBinarization.h"


void SequentialBinarization::run() {
    img->toGrayScale();         //necessario ter a matriz em grayScale
    int max=-1,min=256,average=0;
    for (int i = 0; i < img->bih->biHeight; i++) {
        for (int j = 0; j < img->bih->biWidth; j++) {
            if((img->RED[i][j]) > max)
                max = (img->RED[i][j]);
            if(img->RED[i][j] < min)
                min = (img->RED[i][j]);
        }
    }
    average = (max + min)/2;
    for (int i = 0; i < img->bih->biHeight; i++) {
        for (int j = 0; j < img->bih->biWidth; j++) {
            if((img->RED[i][j]) > average)
                img->RED[i][j] = img->GREEN[i][j] = img->BLUE[i][j] = 255;
            else img->RED[i][j] = img->GREEN[i][j] = img->BLUE[i][j] = 0;
        }
    }
    cout << "binarizacao sequencial realizada";
        //printarMatrizDeCor(BandW);    
}

