#include "../inc/Parser.h"
#include "../inc/Binarization.h"
#include "../inc/ImageLoader.h"
#include "../inc/ParallelImageLoader.h"
#include "../inc/ParallelBinarization.h"
#include "../inc/ParallelImageLoaderPthread.h"
#include "../inc/ParallelBinarizationPthread.h"
#include "../inc/SequentialImageLoader.h"
#include "../inc/SequentialBinarization.h"
#include "../inc/CoinCounter.h"
#include "../inc/SequentialCoinCounter.h"
#include "../inc/OMPCoinCounter.h"
#include "../inc/PthreadCoinCounter.h"
#include <iostream>
#include <map>

int main(int argc, char * argv[]) {
    int numCPU; 
	Parser *commands = new Parser();
	Binarization *imageBinarization;
	CoinCounter *coins;
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
	
	numCPU = commands->getNumCores();
	omp_set_num_threads(numCPU);
	cout << "voce tem: "<<numCPU<<" processadores"<<endl;
        
        if (commands->isOMP()){
            imgLoader = new ParallelImageLoader(commands->getImageAdress());
            imageBinarization = new ParallelBinarization(imgLoader->image);
            coins = new OMPCoinCounter(imgLoader->image);
        }else if(commands->isPthread()){
            imgLoader = new ParallelImageLoaderPthread(commands->getImageAdress());
            imageBinarization = new ParallelBinarizationPthread(imgLoader->image);
            coins = new PthreadCoinCounter(imgLoader->image);
        }else{
            imgLoader = new SequentialImageLoader(commands->getImageAdress());
            imageBinarization = new SequentialBinarization(imgLoader->image);
            coins = new SequentialCoinCounter(imgLoader->image);
        }
        imageBinarization->run();
        cout<< "moedas "<< coins->run()<<endl;
        cout << "tempo de processamento: " << imgLoader->time + imageBinarization->time +coins->time << endl;
        imgLoader->image->salvarImagemRGB(commands->getImageOutName());
	return 0;
}
