#include "../inc/SequentialCoinCounter.h"

void SequentialCoinCounter::filtrar() {
    int media;
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
    
int SequentialCoinCounter::run(){
	filtrar();
    return img->contarMoedas(0, img->bih->biHeight);;
}
    





