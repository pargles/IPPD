/* 
 * File:   Image.cpp
 * Author: gaci
 * 
 * Created on 23 de Maio de 2013, 14:44
 */

#include "../inc/Image.h"



Image::Image() {
}



void Image::load(string fileName) {

	int x, y;         /* X and Y position in image */
    int length;       /* Line length */
    int bitsize;      /* Size of bitmap */
    int infosize;     /* Size of header information */

    GLubyte bits;        /* Bitmap pixel bits */
    GLubyte ptr;         /* Pointer into bitmap */
    GLubyte temp;         /* Temporary variable to swap red and blue */


    reader.open(fileName.c_str(), ios::in | ios::binary);
    if (this->reader == NULL) {
    	cerr << "Nao foi Possivel Abrir o Arquivo: " << fileName;
        reader.close();
    	exit(1);
    }

    reader.read((char*) &header, sizeof(BMPFileHeader));

    if (header < 1){
    	cerr << "Arquivo sem header";
        reader.close();
        exit(1);
    }

    if (this->header.bfType != 'MB'){
    	cerr << "Não é arquico BMP";
        reader.close();
        exit(1);
    }

    infosize = header.bfOffBits - 18;
    reader.read((char*) &info, infosize);

    reader.read((char*) &bits, bitsize);

    reader.close();

    //return (bits);

    /* Swap red and blue */
    //   length = ((*info)->bmiHeader.biWidth * 3 + 3) & ~3;
    //   for (y = 0; y < (*info)->bmiHeader.biHeight; y ++)
    //       for (ptr = bits + y * length, x = (*info)->bmiHeader.biWidth;
    //            x > 0;
   	//     x --, ptr += 3)
   	//   {
   	//    temp   = ptr[0];
   	//    ptr[0] = ptr[1];
   	//    ptr[1] = temp;
   	//    }

       /* OK, everything went fine - return the allocated bitmap... */

}

