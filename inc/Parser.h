#pragma once
#include <iostream>// cout
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

/**
 *@file Parser.h
 *@brief Responsável por separar os parametros que vao ser informados quando o programa for chamado.
 */
class Parser {

	private:
            bool parallel;//1.1
            bool parallelPthread;//1.1
            string imageAdress;

	public:
		Parser();
                bool isParallel();

                bool isParallelPthread() ;
                void setParallel();
                void setParallelPthread();
                string getImageAdress();
                void setImageAdress(string Adress);
		void parse(vector<string> Arguments);
};