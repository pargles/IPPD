/* 
 * File:   ParallelBinarizationPthread.cpp
 * Author: vanderson
 * 
 * Created on 9 de Junho de 2013, 22:00
 */


#include "../inc/ParallelBinarizationPthread.h"
#include <pthread.h>



void *largura(void *p){
    int i=((ARGS *)p)->i;
    Image *img=((ARGS *)p)->img;
    short t=((ARGS *)p)->thresh;
    
    for (int j = 0; j < img->bih->biWidth; j++) {
                if((img->RED[i][j]) > t)
                    img->RED[i][j] = img->GREEN[i][j] = img->BLUE[i][j] = 255;
                else img->RED[i][j] = img->GREEN[i][j] = img->BLUE[i][j] = 0;
    }
    //pthread_exit(NULL);
}
short ParallelBinarizationPthread::simpleThresholding(Image *img){
    int max=-1,min=256;
    //#pragma omp parallel for
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
    //cout << max;
    return (max + min)/2;
}

short ParallelBinarizationPthread::otsuThresholding(Image *img){
    // Calculate histogram
    int ptr = 0;
    short *histData = new short[256];
    //#pragma omg parallel for
    for (int i = 0; i < 256; i++) histData[i] = 0;
    //#pragma omg parallel for
    for (int i = 0; i < img->bih->biHeight; i++) {
        for (int j = 0; j < img->bih->biWidth; j++) {
            int h = 0xFF & img->BLUE[i][j];
            histData[h] ++;
            ptr ++;
        }
    }

    // Total number of pixels
    int total = img->bih->biHeight * img->bih->biWidth;

    float sum = 0;
    for (int t=0 ; t<256 ; t++) sum += t * histData[t];

    float sumB = 0;
    int wB = 0;
    int wF = 0;

    float varMax = 0;
    short threshold = 0;
   // #pragma omg parallel for
    for (int t=0 ; t<256 ; t++) {
        wB += histData[t];               // Weight Background
        if (wB == 0) continue;

        wF = total - wB;                 // Weight Foreground
        if (wF == 0) break;

        sumB += (float) (t * histData[t]);

        float mB = sumB / wB;            // Mean Background
        float mF = (sum - sumB) / wF;    // Mean Foreground

        // Calculate Between Class Variance
        float varBetween = (float)wB * (float)wF * (mB - mF) * (mB - mF);

        // Check if new maximum found
        if (varBetween > varMax) {
            varMax = varBetween;
            threshold = t;
        }
    }
    return threshold;
}

void ParallelBinarizationPthread::run(){
    int initTime = clock();
    img->toGrayScaleParallel();   //necessario ter a matriz em grayScale
    int larguraImg=img->bih->biWidth;
    short thresh = otsuThresholding(img);
    cout << "thresh " << thresh << endl;
    //pthread
    int status,rc;
    pthread_t width[larguraImg];
    ARGS argumentos;
    argumentos.img=img;
    argumentos.thresh=thresh;
    //#pragma omp parallel for
    //{
        for (int i = 0; i < img->bih->biHeight; i++) {
            argumentos.i=i;
            status=pthread_create(&(width[i]),NULL,largura,(void *)&argumentos);  
            if (status)
                exit(-1);
        }
        for (int i = 0; i < img->bih->biHeight; i++) {
            argumentos.i=i;
            status=pthread_join(width[i],(void **)&rc);  
            if (status)
                exit(-1);
        }
    //}
    //pthread_exit(NULL);
    cout << "binarizacao paralela pthread" << "\n";
    cout << "tempo pthread: " << clock() - initTime;
}

    

