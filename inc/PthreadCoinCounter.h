#pragma once
#include "CoinCounter.h"

using namespace std;

class PthreadCoinCounter : public CoinCounter {
public:
    PthreadCoinCounter(Image *im) : CoinCounter(im){};
    int run();
    void filtrar();
private:

};

