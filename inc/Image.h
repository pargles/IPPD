#include <iostream>// cout
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <fstream>

using namespace std;

class Image {

	typedef unsigned char  GLubyte;

	struct BMPFileHeader{
	    unsigned short bfType;           /* Magic number for file */
	    unsigned int   bfSize;           /* Size of file */
	    unsigned short bfReserved1;      /* Reserved */
	    unsigned short bfReserved2;      /* ... */
	    unsigned int   bfOffBits;        /* Offset to bitmap data */
	};


	struct BMPInfoHeader{
	    unsigned int   biSize;           /* Size of info header */
	    int            biWidth;          /* Width of image */
	    int            biHeight;         /* Height of image */
	    unsigned short biPlanes;         /* Number of color planes */
	    unsigned short biBitCount;       /* Number of bits per pixel */
	    unsigned int   biCompression;    /* Type of compression to use */
	    unsigned int   biSizeImage;      /* Size of image data */
	    int            biXPelsPerMeter;  /* X pixels per meter */
	    int            biYPelsPerMeter;  /* Y pixels per meter */
	    unsigned int   biClrUsed;        /* Number of colors used */
	    unsigned int   biClrImportant;   /* Number of important colors */
	};

	struct RGBQuad{
	    unsigned char rgbBlue;          /* Blue value */
	    unsigned char rgbGreen;         /* Green value */
	    unsigned char rgbRed;           /* Red value */
	    unsigned char rgbReserved;      /* Reserved */
	};


	struct BMPInfo{
		BMPInfoHeader bmiHeader;      /* Image header */
	    RGBQuad bmiColors[256]; /* Image colormap */
	};

private:
	ifstream reader;//arquivo em c++
	BMPFileHeader header;       /* File header */
	BMPInfo info;



public:
    Image();
    void load(string fileName);
};



