/* 
 * File:   Image.cpp
 * Author: pargles
 * 
 * Created on 23 de Maio de 2013, 14:44
 */

#include "../inc/Image.h"

Image::Image(unsigned short **r, unsigned short **g, unsigned short **b, unsigned short **c, BITMAPFILEHEADER *bfh, BITMAPINFOHEADER *bih) {
    RED = r;
    GREEN = g;
    BLUE = b;
    COINS = c;
    this->bfh = bfh;
    this->bih = bih;
}

void Image::printarMatrizDeCor(unsigned short **matriz)
{
    for (int i = 0; i < bih->biHeight; i++) {
        for (int j = 0; j < bih->biWidth; j++) {
            cout<< matriz[i][j]<<" ";
        }
        cout<<endl;
    } 
}

void Image::salvarImagemRGB(string nomeArquivo) {
    fstream pictureOut;
    pictureOut.open(nomeArquivo.c_str(),ios::out |ios::in | ios::app | ios::binary);
    char *temp = (char*)bfh;
    pictureOut.write(temp,sizeof(BITMAPFILEHEADER));
    temp=(char*)bih;
    pictureOut.write(temp,sizeof(BITMAPINFOHEADER));
    char r,g,b;
    for (int i = 0; i < bih->biHeight; i++) {
        for (int j = 0; j < bih->biWidth; j++) {
            r = static_cast<char>(RED[i][j]);//recasting para ficar unsigned
            pictureOut.write(&r,sizeof(char));
            g = static_cast<char>(GREEN[i][j]);//recasting para ficar unsigned
            pictureOut.write(&g,sizeof(char));
            b = static_cast<char>(BLUE[i][j]);//recasting para ficar unsigned
            pictureOut.write(&b,sizeof(char));
        }
    }
    pictureOut.close();
}

void Image::toGrayScale(){
    unsigned short r,g,b, gray;
    for (int i = 0; i < bih->biHeight; i++) {
        for (int j = 0; j < bih->biWidth; j++) {
            r = (RED[i][j] * 0.2989);//recasting para ficar unsigned
            g = (GREEN[i][j] * 0.5870);//recasting para ficar unsigned
            b = (BLUE[i][j] * 0.1140 );//recasting para ficar unsigned
            gray = r + g + b;
            RED[i][j] = gray;
            GREEN[i][j] = gray;
            BLUE[i][j] = gray;
        }
    }
}

void Image::toGrayScaleParallel() {
     unsigned short r,g,b, gray;
#pragma omp parallel for
        for (int i = 0; i < bih->biHeight; i++) {
            for (int j = 0; j < bih->biWidth; j++) {
                r = (RED[i][j] * 0.2989);//recasting para ficar unsigned
                g = (GREEN[i][j] * 0.5870);//recasting para ficar unsigned
                b = (BLUE[i][j] * 0.1140 );//recasting para ficar unsigned
                gray = r + g + b;
                RED[i][j] = gray;
                GREEN[i][j] = gray;
                BLUE[i][j] = gray;
            }
        }
}

int Image::posicaoCentral(int i,int j)
{
	int contDir=j,contEsq=j;
	register int k=j;
	COINS[i][k]=PRETO;
	while(RED[i][k+1]==PRETO)
	{
		k++;contDir++;COINS[i][k]=PRETO;
	}
	k=j;
	while(RED[i][k-1]==PRETO)
	{
		k--;contEsq--;COINS[i][k]=PRETO;
	}
	
	return contEsq+((contDir-contEsq)/2);
}

int Image::contarMoedas(int HeightStart, int HeightEnd) {
    register int m, n;
    int moedas = 0;
    for (int i = HeightStart + 1; i < HeightEnd - 1; i++) {
        for (int j = 1; j < bih->biWidth - 1; j++) {
            if (RED[i - 1][j - 1] == PRETO && RED[i - 1][j] == PRETO && RED[i - 1][j + 1] == PRETO &&
                    RED[i][j - 1] == PRETO && RED[i][j] == PRETO && RED[i][j + 1] == PRETO &&
                    RED[i + 1][j - 1] == PRETO && RED[i + 1][j] == PRETO && RED[i + 1][j + 1] == PRETO) {
                if (COINS[i - 1][j - 1] == BRANCO && COINS[i - 1][j] == BRANCO && COINS[i - 1][j + 1] == BRANCO &&
                        COINS[i][j - 1] == BRANCO && COINS[i][j] == BRANCO && COINS[i][j + 1] == BRANCO &&
                        COINS[i + 1][j - 1] == BRANCO && COINS[i + 1][j] == BRANCO && COINS[i + 1][j + 1] == BRANCO) {
                    moedas++;
                    m = i;
                    n = j;
                    while (RED[m][n] == PRETO) {
                        n = posicaoCentral(m, n);
                        m--;
                    }
                    m = i;
                    n = j;
                    while (RED[m][n] == PRETO) {
                        n = posicaoCentral(m, n);
                        m++;
                    }

                }
            }
        }
    }

    return moedas;
}

///////////////////////////////////////////////////////////////////


void Image::printarInformacoesDaImagem() {
    
    cout << "\n FILHEADER\n";
    cout << "\n File type: " << bfh->bfType[0] << bfh->bfType[1] << endl;
    cout << " File size: " << bfh->bfSize << endl;
    cout << " Offset(adress of beggining of the image information): " << bfh->bfOffBits << endl;
    cout << "\n INFOHEADER\n";
    cout << "\n Header size: " << bih->biSize << endl;
    cout << " Image width: " << bih->biWidth << endl;
    cout << " Image height: " << bih->biHeight << endl;
    cout << " Number of bits for each pixel: " << bih->biBitCount << endl;
    cout << " Used compression: " << bih->biCompression << endl;
    cout << " Image size: " << bih->biSizeImage << endl;
    cout << " Horizontal resolution: " << bih->biXPelsPerMeter << endl;
    cout << " Vertical resolution: " << bih->biYPelsPerMeter << endl;
    cout << " Number of colors in the color palette: " << bih->biClrUsed << endl;
    cout << " Number of important colors used: " << bih->biClrImportant << endl;
}
