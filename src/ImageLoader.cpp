/* 
 * File:   ImageLoader.cpp
 * Author: Stephano
 * 
 * Created on 1 de Junho de 2013, 21:31
 */


#include "../inc/ImageLoader.h"

ImageLoader::ImageLoader(string path) {
    this->path = path;
    //load();
}


void ImageLoader::load() {
    ifstream ifs(path.c_str(), ios::binary);

    if(!ifs){
        cout << " Nao foi possivel encontrar a imagem"<<endl;
        exit(1);   
    } 
    // Reading information about BITMAPFILEHEADER
    char* temp = new char[sizeof(Image::BITMAPFILEHEADER)];
    ifs.read(temp, sizeof(Image::BITMAPFILEHEADER));
    bfh = (Image::BITMAPFILEHEADER*)temp;
      // Reading information about BITMAPINFOHEADER
    temp = new char[sizeof(Image::BITMAPINFOHEADER)];
    ifs.read(temp, sizeof(Image::BITMAPINFOHEADER));
    bih = (Image::BITMAPINFOHEADER*)(temp); 
    //printarInformacoesDaImagem();
    
    BLUE = alocarMatriz(BLUE);
    GREEN = alocarMatriz(GREEN);
    RED = alocarMatriz(RED);
    COINS = alocarMatriz(COINS);
    for (int i = 0; i < bih->biHeight; i++) {
        for (int j = 0; j < bih->biWidth; j++) {
			COINS[i][j] = BRANCO;
		}
	}
    
    ifs.seekg(bfh->bfOffBits, ios::beg); // posiciona o ponteiro do arquivo aonde começam as informações de cor
    char r,g,b;
    for (int i = 0; i < bih->biHeight; i++) {
        for (int j = 0; j < bih->biWidth; j++) {
            ifs.read(&r, 1);
            RED[i][j] = static_cast<unsigned char>(r);//recasting para ficar unsigned
            ifs.read(&g, 1);
            GREEN[i][j] = static_cast<unsigned char>(g);//recasting para ficar unsigned
            ifs.read(&b, 1);
            BLUE[i][j] = static_cast<unsigned char>(b);//recasting para ficar unsigned   
        }
    }
    image = new Image(RED,GREEN,BLUE,COINS,bfh,bih);
    //image->printarMatrizDeCor(BLUE);
}



