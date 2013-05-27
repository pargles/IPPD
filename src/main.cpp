#include "../inc/Parser.h"
#include "../inc/Binarization.h"
#include <iostream>

int main(int argc, char * argv[]) {
	Parser *commands = new Parser();
	Binarization *imageBinarization;
	/*
	 *Coloca em um vetor todos os argumentos
	 *   a serem passados para o parser
	 */
	vector<string> args;

	/*
	 *Adiciona cada entrada no vetor de strings
	 */
	Image *img = new Image();
	img->load("lena.bmp");

	for (int i = 0; i < argc; i++)
		args.push_back(argv[i]);

        if (args.size()==1) {
		args.push_back("-help");
                commands->parse(args);
                exit(1);
	}
	commands->parse(args);

	imageBinarization = new Binarization(commands);
	imageBinarization->run();
	return 0;
}
