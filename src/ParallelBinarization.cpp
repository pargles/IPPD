#include "../inc/ParallelBinarization.h"


void ParallelBinarization::run(){
    img->toGrayScaleParallel();   //necessario ter a matriz em grayScale
    int max=-1,min=256,average=0;
    #pragma omp parallel for
    {
        for (int i = 0; i < img->bih->biHeight; i++) {
            for (int j = 0; j < img->bih->biWidth; j++) {
                if((img->RED[i][j]) > max)
                    max = (img->RED[i][j]);
                if(img->RED[i][j] < min)
                    min = (img->RED[i][j]);
            }
        }
    }
    average = (max + min)/2;
    #pragma omp parallel for
    {
        for (int i = 0; i < img->bih->biHeight; i++) {
            for (int j = 0; j < img->bih->biWidth; j++) {
                if((img->RED[i][j]) > average)
                    img->RED[i][j] = img->GREEN[i][j] = img->BLUE[i][j] = 255;
                else img->RED[i][j] = img->GREEN[i][j] = img->BLUE[i][j] = 0;
            }
        }
    }
    cout << "binarizacao paralela";
}
    



