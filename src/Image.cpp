/* 
 * File:   Image.cpp
 * Author: gaci
 * 
 * Created on 23 de Maio de 2013, 14:44
 */

#include "../inc/Image.h"

Image::Image(string imageAdress) {
    adress = imageAdress;
    //bfh = (BITMAPFILEHEADER*)new char[sizeof(BITMAPFILEHEADER)];
    //bih = (BITMAPINFOHEADER*)new char[sizeof(BITMAPINFOHEADER)];
    load();
}

void Image::printarInformacoesDaImagem() {
    
    cout << "\n FILHEADER\n";
    cout << "\n File type: " << bfh->bfType[0] << bfh->bfType[1] << endl;
    cout << " File size: " << bfh->bfSize << endl;
    cout << " ==>>Offset(adress of beggining of the image information): " << bfh->bfOffBits << endl;
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

void Image::printarMatrizDeCor(unsigned int **matriz, int linhas, int colunas)
{
    for (int i = 0; i < bih->biHeight; i++) {
        for (int j = 0; j < bih->biWidth; j++) {
            cout<< matriz[i][j]<<" ";
        }
        cout<<endl;
    } 
}

void Image::load() {
    ifstream ifs(adress.c_str(), ios::binary);

    if(!ifs){
        cout << " Nao foi possivel encontrar a imagem"<<endl;
        exit(1);   
    } 
    // Reading information about BITMAPFILEHEADER
    char* temp = new char[sizeof(BITMAPFILEHEADER)];
    ifs.read(temp, sizeof(BITMAPFILEHEADER));
    bfh = (BITMAPFILEHEADER*)(temp);
      // Reading information about BITMAPINFOHEADER
    temp = new char[sizeof(BITMAPINFOHEADER)];
    ifs.read(temp, sizeof(BITMAPINFOHEADER));
    bih = (BITMAPINFOHEADER*)(temp); 
    
    printarInformacoesDaImagem();
    
    BLUE = alocarMatriz(BLUE,bih->biHeight,bih->biWidth);
    GREEN = alocarMatriz(GREEN,bih->biHeight,bih->biWidth);
    RED = alocarMatriz(RED,bih->biHeight,bih->biWidth);
    
    ifs.seekg(bfh->bfOffBits, ios::beg); // posiciona o ponteiro do arquivo aonde começam as informações de cor
    char r,g,b;//essa é a ordem no arquivo
    for (int i = 0; i < bih->biHeight; i++) {
        for (int j = 0; j < bih->biWidth; j++) {
            ifs.read(&b, 1);
            BLUE[i][j] = static_cast<unsigned char>(b);//recasting para ficar unsigned
            ifs.read(&g, 1);
            GREEN[i][j] = static_cast<unsigned char>(g);//recasting para ficar unsigned
            ifs.read(&r, 1);
            RED[i][j] = static_cast<unsigned char>(r);//recasting para ficar unsigned
        }
    }
    
    printarMatrizDeCor(BLUE,bih->biHeight,bih->biWidth);
}

unsigned int **Image::alocarMatriz(unsigned int **matriz, int linhas, int colunas) {
    unsigned int **mat = new unsigned int*[linhas];

    for (int i = 0; i < linhas; ++i)
        mat[i] = new unsigned int[colunas];

    //iniciando ela com zero
    for (int i = 0; i < linhas; ++i)
        for (int j = 0; j < colunas; ++j)
            mat[i][j] = 0;
        return mat;
}

