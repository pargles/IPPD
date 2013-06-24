#pragma once
#include "CoinCounter.h"
#include <pthread.h>
using namespace std;
typedef struct _ARGSF{
        Image *img;
        int i;
        int iMax;
}ARGSF;
typedef struct _ARGSC{
        Image * img;
        int i;
        int imax;
        int moedas;
}ARGSC;

class PthreadCoinCounter : public CoinCounter {
public:
    PthreadCoinCounter(Image *im) : CoinCounter(im){};
    int run();
    void filtrar();
private:
    int moedas;
};

