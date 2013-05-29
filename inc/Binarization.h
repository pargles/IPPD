#include "Parser.h"
#include "Image.h"
#include <cstdio>
#include <iostream>//cout
class Binarization {
    
public:
    Binarization(Parser *parse);
    void run();
    void sequencialBin();
    void parallelBin();
private:
    Parser *parser;
    Image *img;
    int executionTime;  

};

