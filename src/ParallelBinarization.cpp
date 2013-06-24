#include "../inc/ParallelBinarization.h"

short ParallelBinarization::simpleThresholding(Image *img){
    int max=-1,min=256;
    #pragma omp parallel for
        for (int i = 0; i < img->bih->biHeight; i++) {
            for (int j = 0; j < img->bih->biWidth; j++) {
                if((img->RED[i][j]) > max)
                    max = (img->RED[i][j]);
                if(img->RED[i][j] < min)
                    min = (img->RED[i][j]);
            }
        }
    return (max + min)/2;
}

short ParallelBinarization::otsuThresholding(Image *img){
    int ptr = 0;
    short *histData = new short[256];
    #pragma omg parallel for
    for (int i = 0; i < 256; i++) histData[i] = 0;
    #pragma omg parallel for
    for (int i = 0; i < img->bih->biHeight; i++) {
        for (int j = 0; j < img->bih->biWidth; j++) {
            int h = 0xFF & img->BLUE[i][j];
            histData[h] ++;
            ptr ++;
        }
    }
    int total = img->bih->biHeight * img->bih->biWidth;
    float sum = 0;
    for (int t=0 ; t<256 ; t++) sum += t * histData[t];
    float sumB = 0;
    int wB = 0;
    int wF = 0;
    float varMax = 0;
    short threshold = 0;
    #pragma omg parallel for
    for (int t=0 ; t<256 ; t++) {
        wB += histData[t];               // Weight Background
        if (wB == 0) continue;
        wF = total - wB;                 // Weight Foreground
        if (wF == 0) break;
        sumB += (float) (t * histData[t]);
        float mB = sumB / wB;            // Mean Background
        float mF = (sum - sumB) / wF;    // Mean Foreground
        float varBetween = (float)wB * (float)wF * (mB - mF) * (mB - mF);
        if (varBetween > varMax) {
            varMax = varBetween;
            threshold = t;
        }
    }
    return threshold;
}
void ParallelBinarization::run(){
    img->toGrayScaleParallel();   //necessario ter a matriz em grayScale
    short thresh = 245;
    cout << "thresh " << thresh << endl;
    #pragma omp parallel for
        for (int i = 0; i < img->bih->biHeight; i++) {
            for (int j = 0; j < img->bih->biWidth; j++) {
                if((img->RED[i][j]) > thresh)
                    img->RED[i][j] = img->GREEN[i][j] = img->BLUE[i][j] = 255;
                else img->RED[i][j] = img->GREEN[i][j] = img->BLUE[i][j] = 0;
            }
        }
    cout << "binarizacao paralela" << "\n";
}
    



