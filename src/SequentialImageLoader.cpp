/* 
 * File:   SequentialImageLoader.cpp
 * Author: Stephano
 * 
 * Created on 1 de Junho de 2013, 22:11
 */

#include "../inc/SequentialImageLoader.h"

unsigned short **SequentialImageLoader::alocarMatriz(unsigned short **matriz) {
    unsigned short **mat = new unsigned short*[bih->biHeight];

    for (int i = 0; i < bih->biHeight; ++i)
        mat[i] = new unsigned short[bih->biWidth];

    //iniciando ela com zero
    for (int i = 0; i < bih->biHeight; ++i)
        for (int j = 0; j < bih->biWidth; ++j)
            mat[i][j] = 0;
        return mat;
}

