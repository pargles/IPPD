/* 
 * File:   ParallelBinarizationPthread.h
 * Author: vanderson
 *
 * Created on 9 de Junho de 2013, 22:00
 */


#include <iostream>// cout
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <fstream>

#include "Binarization.h"
#include <time.h>


using namespace std;
typedef struct _ARGS{
        Image *img;
        int i;
        int j;
        int iMax;
        int jMax;
        short thresh;
}ARGS;

class ParallelBinarizationPthread : public Binarization {
public:
    ParallelBinarizationPthread(Image *im) : Binarization(im){};
    void run();
    
    short simpleThresholding(Image *img);
    short otsuThresholding(Image *img);
private:

};


