/* 
 * File:   ParallelImageLoaderPthread.cpp
 * Author: vanderson
 * 
 * Created on 9 de Junho de 2013, 22:02
 */

#include "../inc/ParallelImageLoaderPthread.h"

void *zerar(void *p){
    int iMax=((ARGSI *)p)->iMax;
    int jMax=((ARGSI *)p)->jMax;
    unsigned short **mat=((ARGSI *)p)->mat;
    for (int i=((ARGSI *)p)->i; i <iMax;  i++)
        for (int j=((ARGSI *)p)->j; j <jMax; j++)
            mat[i][j] = 0;    
}
unsigned short **ParallelImageLoaderPthread::alocarMatriz(unsigned short **matriz) {
    unsigned short **mat = new unsigned short*[bih->biHeight];
    int alturaImg=bih->biHeight;
    int larguraImg=bih->biWidth;

    for (int i = 0; i < bih->biHeight; ++i)
        mat[i] = new unsigned short[bih->biWidth];

    //iniciando ela com zero
    //pthread
     int status[4],rc[4],i;
    pthread_t operarios[4];
    ARGSI argumentos[4];
   
    //primeiro quadrante
    argumentos[0].j=0;
    argumentos[0].i=0;
    argumentos[0].jMax=larguraImg-(larguraImg/2);
    argumentos[0].iMax=alturaImg-(alturaImg/2);
    //segundo quadrante
    argumentos[1].j=larguraImg-(larguraImg/2);
    argumentos[1].i=0;
    argumentos[1].jMax=larguraImg;
    argumentos[1].iMax=alturaImg-(alturaImg/2);
    //terceiro quadrante
     argumentos[2].j=0;
     argumentos[2].i=alturaImg-(alturaImg/2);
     argumentos[2].jMax=larguraImg-(larguraImg/2);
     argumentos[2].iMax=alturaImg;
     //quarto quadrante
      argumentos[3].j=alturaImg-(alturaImg/2);
     argumentos[3].i=alturaImg-(alturaImg/2);
     argumentos[3].jMax=larguraImg;
     argumentos[3].iMax=alturaImg;
     
     
      for( i=0;i<4;i++){
       argumentos[i].mat=mat;
       status[i]=pthread_create(&(operarios[i]),NULL,zerar,(void *)&argumentos[i]);  
       if (status[i])
                exit(-1);
    }
    for (i = 0; i < 4; i++) {
         status[i]=pthread_join(operarios[i],(void **)&rc[i]);  
         if (status[i])
            exit(-1);
    }
     return mat;
   
}
