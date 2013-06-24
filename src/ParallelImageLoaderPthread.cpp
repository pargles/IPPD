/* 
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
    int status[4],rc[4],i;
    pthread_t operarios[4];
    ARGSI argumentos[4];
    for( i=0;i<4;i++){
       argumentos[i].mat=mat;
       argumentos[i].j=0;
       argumentos[i].jMax=larguraImg;
       argumentos[i].i=i*(alturaImg/4);
       argumentos[i].iMax=(argumentos[i].i)+(alturaImg/4);
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
