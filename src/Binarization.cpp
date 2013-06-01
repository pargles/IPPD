
#include "../inc/Binarization.h"


/**
 *@file Binarization.cpp
 *@brief Método construtor, inicializa a classe Binarization com valores default.
 */
Binarization::Binarization(Parser *parse) {
    this->parser = parse;
    this->executionTime = 0;
    Image *img = new Image(parse->getImageAdress());
    
}

void Binarization::run() {
    if(parser->isParallel())
        cout << "implementar metodo\n";
    else sequencialBin();
}

void Binarization::sequencialBin() {
   // img->printarInformacoesDaImagem();//====> nao que merda que ta dando que os valores nao estao ficando no objeto img

}

void Binarization::parallelBin() {
   
}

