#include "../inc/Parser.h"
#include <cstdio>


/**
 *@file Parser.cpp
 *@brief Método construtor, inicializa a classe Parser com valores default.
 */
Parser::Parser() {
	this->parallel= false;
}

/**
 *@file Parser.cpp
 *@brief Retorna true se a a execução for paralela
 *@return bool
 */
bool Parser::isParallel() {
	return this->parallel;
}

void Parser::setParallel() {
	this->parallel = true;
}

void Parser::setImageAdress(string Adress) {
    this->imageAdress = Adress;
}

string Parser::getImageAdress() {
    return imageAdress;
}

void Parser::parse(vector<string> Arguments) {
	for (register int i = 0; i < Arguments.size(); i++)
		if (Arguments[i].compare("-parallel") == 0)
			this->setParallel();
		else if (Arguments[i].compare("-img") == 0)
			setImageAdress(Arguments[i + 1]);
		else if (Arguments[i].compare("-help") == 0) {
			cout << "-img imageAdress\n";
			cout << "-parallel\n";
		}
}

