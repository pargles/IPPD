#include "../inc/PthreadCoinCounter.h"

void * filtro(void *p) {
    int media;
    Image * img = ((ARGSF *) p)->img;
    int i = ((ARGSF *) p)->i;
    if (i == 0)
        i++;
    int imax = ((ARGSF *) p)->iMax ;
    if (imax == img->bih->biHeight)
        imax--;
    for (; i < imax; i++) {
        int jmax = img->bih->biWidth;
        for (int j = 1; j < jmax; j++) {
            media = (img->RED[i - 1][j - 1] +
                    img->RED[i][j - 1] +
                    img->RED[i + 1][j - 1] +
                    img->RED[i - 1][j] +
                    img->RED[i][j] +
                    img->RED[i + 1][j] +
                    img->RED[i - 1][j + 1] +
                    img->RED[i][j + 1] +
                    img->RED[i + 1][j + 1]) / 9;
            if (media > 128)
                img->RED[i][j] = img->GREEN[i][j] = img->BLUE[i][j] = 255;
            else
                img->RED[i][j] = img->GREEN[i][j] = img->BLUE[i][j] = 0;
        }
    }
}

    map<string, bool> treeMap;
    
void * contador(void *p) {
    int inicio = ((ARGSC *) p)->i ;
    int fim = ((ARGSC *) p)->imax ;
    int moedaAux = ((ARGSC *) p)->img->contarMoedas(inicio, fim, &treeMap);
    ((ARGSC *) p)->moedas = moedaAux;
}

void PthreadCoinCounter::filtrar() {
    int status[4], rc[4];
    pthread_t operarios[4];
    ARGSF parametros[4];
    for (int i = 0, j = img->bih->biHeight / 4; i < 4; i++) {
        parametros[i].i = j*i;
        parametros[i].iMax = j * (i + 1);
        parametros[i].img = img;
        status[i] = pthread_create(&(operarios[i]), NULL, filtro, (void *) &parametros[i]);
        if (status[i])
            exit(-1);
    }
    for (int i = 0; i < 4; i++) {
        status[i] = pthread_join(operarios[i], (void **) &rc[i]);
        if (status[i])
            exit(-1);
    }
}

int PthreadCoinCounter::run() {
    filtrar();
    int status[4], rc[4];
    pthread_t operarios[4];
    ARGSC parametros[4];
    for (int i = 0, j = (img->bih->biHeight / 4); i < 4; i++) {
        parametros[i].i = j*i;
        parametros[i].imax = j * (i + 1);
        parametros[i].moedas = 0;
        parametros[i].img = img;
        status[i] = pthread_create(&(operarios[i]), NULL, contador, (void *) &parametros[i]);
        if (status[i])
            exit(-1);
    }
    for (int i = 0; i < 4; i++) {
        status[i] = pthread_join(operarios[i], (void **) &rc[i]);
        if (status[i])
            exit(-1);
    }
    for (int j = 0; j < 4; j++) {
        moedas += parametros[j].moedas;
    }
    //return moedas;
    return treeMap.size();
}