#include "../inc/OMPCoinCounter.h"

void OMPCoinCounter::filtrar() {
    
#pragma omp parallel for
    for (int i = 2; i < img->bih->biHeight - 2; i++) {
        int media;
        for (int j = 2; j < img->bih->biWidth - 2; j++) {
            media = (img->RED[i - 1][j - 1] +
                    img->RED[i][j - 1] +
                    img->RED[i + 1][j - 1] +
                    img->RED[i - 1][j] +
                    img->RED[i][j] +
                    img->RED[i + 1][j] +
                    img->RED[i - 1][j + 1] +
                    img->RED[i][j + 1] +
                    img->RED[i + 1][j + 1]+
                    img->RED[i - 2][j - 2] +
                    img->RED[i-2][j - 1] +
                    img->RED[i-2][j] +
                    img->RED[i-2][j+1] +
                    img->RED[i-2][j+2] +
                    img->RED[i-1][j-2] +
                    img->RED[i - 1][j + 2] +
                    img->RED[i][j + 2] +
                    img->RED[i][j -2]+
                    img->RED[i+1][j-2] +
                    img->RED[i+1][j + 2] +
                    img->RED[i+2][j + 2] +
                    img->RED[i+2][j + 1] +
                    img->RED[i+2][j] +
                    img->RED[i+2][j -1] +
                    img->RED[i+2][j - 2] ) / 25;
            if (media >= 128)
                img->RED[i][j] = img->GREEN[i][j] = img->BLUE[i][j] = 255;
            else img->RED[i][j] = img->GREEN[i][j] = img->BLUE[i][j] = 0;
        }
    }

}
    
int OMPCoinCounter::run(){
    filtrar();
    int moedas1 = 0, moedas2 = 0, moedas3 = 0, moedas4 = 0;
    map<string,bool> treeMap;
    int passo = img->bih->biHeight / 4;
    int p1 = passo;
    int p2 = p1 + passo;
    int p3 = p2 + passo;
    #pragma omp parallel
    {
        printf("%d threads \n", omp_get_num_threads());
        #pragma omp sections nowait
        {
            #pragma omp section
            {
                cout << "thread " << omp_get_thread_num() << " executando processo 1 " << endl;
                img->contarMoedas(0, p1, &treeMap);
            }
            #pragma omp section
            {
                cout << "thread " << omp_get_thread_num() << " executando processo 2 " << endl;
                img->contarMoedas(p1+1, p2, &treeMap);
            }
            #pragma omp section
            {
                cout << "thread " << omp_get_thread_num() << " executando processo 3 " << endl;
                img->contarMoedas(p2+1, p3, &treeMap);
            }
            #pragma omp section
            {
                cout << "thread " << omp_get_thread_num() << " executando processo 4 " << endl;
                img->contarMoedas(p3+1, img->bih->biHeight, &treeMap);
            }
        }
    }
    return treeMap.size();
}
    




