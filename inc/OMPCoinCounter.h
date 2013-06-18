#pragma once
#include "CoinCounter.h"

using namespace std;

class OMPCoinCounter : public CoinCounter {
public:
    OMPCoinCounter(Image *im) : CoinCounter(im){};
    int run();
    void filtrar();
private:

};
