#include "../inc/OMPCoinCounter.h"

void OMPCoinCounter::filtrar() {
    int media;
#pragma omp parallel for
    for (int i = 1; i < img->bih->biHeight - 1; i++) {
        for (int j = 1; j < img->bih->biWidth - 1; j++) {
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
            else img->RED[i][j] = img->GREEN[i][j] = img->BLUE[i][j] = 0;
        }
    }

}
    
int OMPCoinCounter::run(){
	filtrar();
	int moedas1 = 0, moedas2 = 0, moedas3 = 0, moedas4 = 0;
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
                moedas1 = img->contarMoedas(0, p1);
            }
#pragma omp section
            {
                cout << "thread " << omp_get_thread_num() << " executando processo 2 " << endl;
                moedas2 = img->contarMoedas(p1, p2);
            }
#pragma omp section
            {
                cout << "thread " << omp_get_thread_num() << " executando processo 3 " << endl;
                moedas3 = img->contarMoedas(p2, p3);
            }
#pragma omp section
            {
                cout << "thread " << omp_get_thread_num() << " executando processo 4 " << endl;
                moedas4 = img->contarMoedas(p3, img->bih->biHeight);
            }
        }
    }
    return moedas1 + moedas2 + moedas3 + moedas4;
}
    




