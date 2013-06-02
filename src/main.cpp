#include "../inc/Parser.h"
#include "../inc/Binarization.h"
#include "../inc/ImageLoader.h"
#include "../inc/ParallelImageLoader.h"
#include "../inc/ParallelBinarization.h"
#include "../inc/SequentialImageLoader.h"
#include "../inc/SequentialBinarization.h"
#include <iostream>

int main(int argc, char * argv[]) {
    
	Parser *commands = new Parser();
	Binarization *imageBinarization;
        ImageLoader *imgLoader;
	 //Coloca em um vetor todos os argumentos a serem passados para o parser
	vector<string> args;
	 //Adiciona cada entrada no vetor de string
	for (int i = 0; i < argc; i++)
		args.push_back(argv[i]);

        if (args.size()==1) {
		args.push_back("-help");
                commands->parse(args);
                exit(1);
	}
	commands->parse(args);
        
        if (commands->isParallel()){
            imgLoader = new ParallelImageLoader(commands->getImageAdress());
            imageBinarization = new ParallelBinarization(imgLoader->image);
        }else{
            imgLoader = new SequentialImageLoader(commands->getImageAdress());
            imageBinarization = new SequentialBinarization(imgLoader->image);
        }
	imageBinarization->run();
        imgLoader->image->salvarImagemRGB("out.bmp");
	return 0;
}
