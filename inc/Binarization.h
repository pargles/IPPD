#include "Parser.h"
#include <cstdio>
#include <iostream>//cout
class Binarization {
    
public:
    Binarization(Parser *parse);
    void run();
private:
    Parser *parser;
    int executionTime;

};

