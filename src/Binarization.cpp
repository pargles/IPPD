
#include "../inc/Binarization.h"


/**
 *@file Binarization.cpp
 *@brief Método construtor, inicializa a classe Binarization com valores default.
 */
Binarization::Binarization(Parser *parse) {
    this->parser = parse;
    this->executionTime = 0;
}

void Binarization::run() {
    if(parser->isParallel())
        cout << "implementar metodo\n";

}

