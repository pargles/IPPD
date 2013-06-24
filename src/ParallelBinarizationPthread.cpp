/* 
 * File:   ParallelBinarizationPthread.cpp
 * Author: vanderson
 * 
 * Created on 9 de Junho de 2013, 22:00
 */


#include "../inc/ParallelBinarizationPthread.h"
#include <pthread.h>

void *largura(void *p) {
    int iMax = ((ARGS *) p)->iMax;
    int jMax = ((ARGS *) p)->jMax;
    Image *img = ((ARGS *) p)->img;
    short thresh = ((ARGS *) p)->thresh;
    for (int i = ((ARGS *) p)->i; i < iMax; i++) {
        for (int j = ((ARGS *) p)->j; j < jMax; j++) {
            if ((img->RED[i][j]) > thresh)
                img->RED[i][j] = img->GREEN[i][j] = img->BLUE[i][j] = 255;
            else img->RED[i][j] = img->GREEN[i][j] = img->BLUE[i][j] = 0;
        }
    }
}

void *sthresholding(void *p){
    int min=-1,max=256;
    int iMax = ((ARGS *) p)->iMax;
    int jMax = ((ARGS *) p)->jMax;
    Image *img = ((ARGS *) p)->img;
    for (int i = 0; i < iMax; i++) {
            for (int j = 0; j < jMax; j++) {
                if ((img->RED[i][j]) > max)
                    max = (img->RED[i][j]);
                if (img->RED[i][j] < min)
                    min = (img->RED[i][j]);
            }
        }
     ((ARGS *) p)->minMax=(min+max)/2;
}

short ParallelBinarizationPthread::simpleThresholding(Image *img) {
    int retorno;
    int status[4], rc[4];
    pthread_t operarios[4];
    for (int i = 0; i < 4; i++) {
        argumentos[i].img = img;
        argumentos[i].minMax=0;
        status[i] = pthread_create(&(operarios[i]), NULL, sthresholding, (void *) &argumentos[i]);
        if (status[i])
            exit(-1);
    }
    for (int i = 0; i < 4; i++) {
        status[i] = pthread_join(operarios[i], (void **) &rc[i]);
        if (status[i])
            exit(-1);
    }
    for(int j=0;j<4;j++)
        retorno+=argumentos[j].minMax;
    return retorno;
}

short ParallelBinarizationPthread::otsuThresholding(Image *img) {
    int ptr = 0;
    short *histData = new short[256];
    for (int i = 0; i < 256; i++) histData[i] = 0;
    for (int i = 0; i < img->bih->biHeight; i++) {
        for (int j = 0; j < img->bih->biWidth; j++) {
            int h = 0xFF & img->BLUE[i][j];
            histData[h]++;
            ptr++;
        }
    }
    int total = img->bih->biHeight * img->bih->biWidth;
    float sum = 0;
    for (int t = 0; t < 256; t++) 
        sum += t * histData[t];
    float sumB = 0;
    int wB = 0;
    int wF = 0;
    float varMax = 0;
    short threshold = 0;
    for (int t = 0; t < 256; t++) {
        wB += histData[t]; // Weight Background
        if (wB == 0)
            continue;
        wF = total - wB; // Weight Foreground
        if (wF == 0) 
            break;
        sumB += (float) (t * histData[t]);
        float mB = sumB / wB; // Mean Background
        float mF = (sum - sumB) / wF; // Mean Foreground
        // Calculate Between Class Variance
        float varBetween = (float) wB * (float) wF * (mB - mF) * (mB - mF);
        // Check if new maximum found
        if (varBetween > varMax) {
            varMax = varBetween;
            threshold = t;
        }
    }
    return threshold;
}
void ParallelBinarizationPthread::run() {
    img->toGrayScaleParallel();
    int status[4], rc[4];
    pthread_t operarios[4];
    for (int i = 0; i < 4; i++) {
        argumentos[i].img = img;
        argumentos[i].thresh = 245;
        status[i] = pthread_create(&(operarios[i]), NULL, largura, (void *) &argumentos[i]);
        if (status[i])
            exit(-1);
    }
    for (int i = 0; i < 4; i++) {
        status[i] = pthread_join(operarios[i], (void **) &rc[i]);
        if (status[i])
            exit(-1);
    }
    cout << "binarizacao paralela pthread" << "\n";
}



