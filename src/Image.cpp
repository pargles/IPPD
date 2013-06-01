/* 
 * File:   Image.cpp
 * Author: pargles
 * 
 * Created on 23 de Maio de 2013, 14:44
 */

#include "../inc/Image.h"

Image::Image(string imageAdress) {
    adress = imageAdress;
    load();
    //sequencialBinarization();
    parallelBinarization();
    //image2GrayScale();
    //salvarImagemGrayScale("testesao.bmp");
    //salvarImagemBlackAndWhite("NegaLena.bmp");
    //printarInformacoesDaImagem();
    //printarMatrizDeCor(GRAY);
    salvarImagemRGB("out.bmp");
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
    
    BLUE = parallelAlocarMatriz(BLUE);
    GREEN = parallelAlocarMatriz(GREEN);
    RED = parallelAlocarMatriz(RED);
    
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
    
    //printarMatrizDeCor(BLUE);
}

unsigned short **Image::alocarMatriz(unsigned short **matriz) {
    unsigned short **mat = new unsigned short*[bih->biHeight];

    for (int i = 0; i < bih->biHeight; ++i)
        mat[i] = new unsigned short[bih->biWidth];

    //iniciando ela com zero
    for (int i = 0; i < bih->biHeight; ++i)
        for (int j = 0; j < bih->biWidth; ++j)
            mat[i][j] = 0;
        return mat;
}

unsigned short **Image::parallelAlocarMatriz(unsigned short **matriz) {
    unsigned short **mat = new unsigned short*[bih->biHeight];
#pragma omp parallel for
    for (int i = 0; i < bih->biHeight; ++i)
        mat[i] = new unsigned short[bih->biWidth];
#pragma omp parallel for
    //iniciando ela com zero
    for (int i = 0; i < bih->biHeight; ++i)
        for (int j = 0; j < bih->biWidth; ++j)
            mat[i][j] = 0;
        return mat;
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
void Image::image2GrayScale() {
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

void Image::parallelImage2GrayScale() {
    #pragma omp parallel for 
    {
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
}


void Image::sequencialBinarization() {
    image2GrayScale();//necessario ter a matriz em grayScale
    int max=-1,min=256,average=0;
    for (int i = 0; i < bih->biHeight; i++) {
        for (int j = 0; j < bih->biWidth; j++) {
            if((RED[i][j]) > max)
                max = (RED[i][j]);
            if(RED[i][j] < min)
                min = (RED[i][j]);
        }
    }
    this->maiorPixel = max;
    this->menorPixel = min;
    cout << max ; cout << "\n";
    cout << min;
    average = (max + min)/2;
    this->mediaPixels = average;
    for (int i = 0; i < bih->biHeight; i++) {
        for (int j = 0; j < bih->biWidth; j++) {
            if((RED[i][j]) > average)
                RED[i][j] = GREEN[i][j] = BLUE[i][j] = 255;
            else RED[i][j] = GREEN[i][j] = BLUE[i][j] = 0;
        }
    }
        //printarMatrizDeCor(BandW);    
}

void Image::parallelBinarization(){
    parallelImage2GrayScale();//necessario ter a matriz em grayScale
    #pragma omp parallel for
    {
        int max=-1,min=256,average=0;
        for (int i = 0; i < bih->biHeight; i++) {
            for (int j = 0; j < bih->biWidth; j++) {
                if((RED[i][j]) > max)
                    max = (RED[i][j]);
                if(RED[i][j] < min)
                    min = (RED[i][j]);
            }
        }
        this->maiorPixel = max;
        this->menorPixel = min;
        cout << max ; cout << "\n";
        cout << min;
        average = (max + min)/2;
        this->mediaPixels = average;
        for (int i = 0; i < bih->biHeight; i++) {
            for (int j = 0; j < bih->biWidth; j++) {
                if((RED[i][j]) > average)
                    RED[i][j] = GREEN[i][j] = BLUE[i][j] = 255;
                else RED[i][j] = GREEN[i][j] = BLUE[i][j] = 0;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////

void Image::salvarImagemBlackAndWhite(string nomeArquivo) {
    sequencialBinarization();
    ofstream pictureOut;
    int seek = bfh->bfOffBits;
    int tamanhoRGB=bfh->bfSize;
    unsigned short bitsPorPixel= bih->biBitCount;
    unsigned int tamanhoDaImagem=bih->biSizeImage;
    unsigned int paletaCores=bih->biClrUsed;
    pictureOut.open(nomeArquivo.c_str(),ios::out | ios::app | ios::binary);
    bfh->bfOffBits = 1078;//seek da imagem preto e branco
    bfh->bfSize = bih->biHeight*bih->biWidth+bfh->bfOffBits;//tamanho do arquivo grayScale
    char *temp = (char*)bfh;
    pictureOut.write(temp,sizeof(BITMAPFILEHEADER));
    bih->biBitCount=8;//preto e branco scale, so uma matriz
    bih->biSizeImage=bih->biHeight*bih->biWidth;//tamanho da imagem grayScale
    bih->biClrUsed=256;//256 bits por pixels
    temp=(char*)bih;
    pictureOut.write(temp,sizeof(BITMAPINFOHEADER));
    char bw;
    
    for (int i = 0; i < bih->biHeight; i++) {
        for (int j = 0; j < bih->biWidth; j++) {
            bw = static_cast<char>(GRAY[i][j]);//recasting para ficar unsigned
            pictureOut.write(&bw,sizeof(char));
        }
    }
    bfh->bfSize = tamanhoRGB;//devolvendo os valores originais da imagem RGB
    bfh->bfOffBits = seek;
    bih->biBitCount=bitsPorPixel;
    bih->biSizeImage=tamanhoDaImagem;
    bih->biClrImportant=paletaCores;
    
    pictureOut.close();
}


void Image::salvarImagemGrayScale(string nomeArquivo) {
    ofstream pictureOut;
    pictureOut.open(nomeArquivo.c_str(),ios::out | ios::app | ios::binary);
    
    char *temp = (char*)bfh;
    pictureOut.write(temp,sizeof(BITMAPFILEHEADER));
    temp=(char*)bih;
    pictureOut.write(temp,sizeof(BITMAPINFOHEADER));
    char r,g,b, gray;
    for (int i = 0; i < bih->biHeight; i++) {
        for (int j = 0; j < bih->biWidth; j++) {
            r = static_cast<char>(RED[i][j] * 0.2989);//recasting para ficar unsigned
            g = static_cast<char>(GREEN[i][j] * 0.5870);//recasting para ficar unsigned
            b = static_cast<char>(BLUE[i][j] * 0.1140 );//recasting para ficar unsigned
            gray = r + g + b;
            pictureOut.write(&gray,sizeof(char));
            pictureOut.write(&gray,sizeof(char));
            pictureOut.write(&gray,sizeof(char));
          }
    }
    
    pictureOut.close();    
}

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
