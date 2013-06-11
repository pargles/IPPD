/* 
 * File:   ParallelImageLoaderPthread.cpp
 * Author: vanderson
 * 
 * Created on 9 de Junho de 2013, 22:02
 */

#include "../inc/ParallelImageLoaderPthread.h"


unsigned short **ParallelImageLoaderPthread::alocarMatriz(unsigned short **matriz) {
    unsigned short **mat = new unsigned short*[bih->biHeight];
//#pragma omp parallel for
    for (int i = 0; i < bih->biHeight; ++i)
        mat[i] = new unsigned short[bih->biWidth];
//#pragma omp parallel for
    //iniciando ela com zero
    for (int i = 0; i < bih->biHeight; ++i)
        for (int j = 0; j < bih->biWidth; ++j)
            mat[i][j] = 0;
        return mat;
}
