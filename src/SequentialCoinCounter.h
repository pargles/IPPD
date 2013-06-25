#pragma once
#include "CoinCounter.h"

using namespace std;

class SequentialCoinCounter : public CoinCounter {
public:
    SequentialCoinCounter(Image *im) : CoinCounter(im){};
    int run();
    void filtrar();
private:

};

