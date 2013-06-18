#include "../inc/Parser.h"
#include <cstdio>


/**
 *@file Parser.cpp
 *@brief Método construtor, inicializa a classe Parser com valores default.
 */
Parser::Parser() {
	this->omp= false;
	this->pthread= false;
	this->showTasks= false;
	this->otsu = false;
	this->showHeaderInfo = false;
	this->imageOut = false;
	this->numOfThreads = getNumCores();
	this->imageOutName = "out.bmp";
}

/**
 *@file Parser.cpp
 *@brief Retorna true se a a execução for paralela
 *@return bool
 */
bool Parser::isOMP() {
	return this->omp;
}
bool Parser::isPthread() {
	return this->pthread;
}

bool Parser::isOTSU() {
	return this->otsu;
}

bool Parser::isshowHeader() {
	return this->showHeaderInfo;
}

bool Parser::isshowTasks() {
	return this->showTasks;
}

bool Parser::isimageOut() {
	return this->imageOut;
}

void Parser::setOMP() {
	this->omp = true;
}

void Parser::setNumOfThreads(int num) {
	this->numOfThreads = num;
}

void Parser::setOTSU() {
	this->otsu = true;
}
void Parser ::setPthread(){
    this->pthread=true;
}

void Parser ::setTasks(){
    this->showTasks=true;
}

void Parser ::setImageOut(){
    this->imageOut=true;
}

void Parser::setImageAdress(string Adress) {
    this->imageAdress = Adress;
}

void Parser::setImageOutName(string name) {
    this->imageOutName = name;
}

void Parser::setShowHeader() {
    this->showHeaderInfo = true;
}

string Parser::getImageAdress() {
    return imageAdress;
}

string Parser::getImageOutName() {
    return imageOutName;
}

int Parser::getNumOfThreads() {
    return numOfThreads;
}

int Parser::getNumCores() {
#ifdef WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
#elif MACOS
    int nm[2];
    size_t len = 4;
    uint32_t count;

    nm[0] = CTL_HW; nm[1] = HW_AVAILCPU;
    sysctl(nm, 2, &count, &len, NULL, 0);

    if(count < 1) {
        nm[1] = HW_NCPU;
        sysctl(nm, 2, &count, &len, NULL, 0);
        if(count < 1) { count = 1; }
    }
    return count;
#else
    return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}

void Parser::parse(vector<string> Arguments) {
	for (register int i = 0; i < Arguments.size(); i++)
		if (Arguments[i].compare("-omp") == 0)
			this->setOMP();
		else if (Arguments[i].compare("-t") == 0)
			this->setNumOfThreads(atoi(Arguments[i + 1].c_str()));
		else if (Arguments[i].compare("-pthread") == 0)
			this->setPthread();
		else if (Arguments[i].compare("-tasks") == 0)
			this->setTasks();
		else if (Arguments[i].compare("-otsu") == 0)
			this->setOTSU();
		else if (Arguments[i].compare("-header") == 0)
			this->setShowHeader();
		else if (Arguments[i].compare("-out") == 0){
			this->setImageOut();
			imageOutName = Arguments[i + 1];
		}
		else if (Arguments[i].compare("-img") == 0)
			imageAdress = Arguments[i + 1];
		else if (Arguments[i].compare("-help") == 0) {
			cout << "Use the following arguments:\n";
			cout << "-img imageAdress to open an image with imageAdress\n";
			cout << "-omp to execute in parallel with open mp library\n";
			cout << "-pthread to execute in parallel with pthread library\n";
			cout << "-t to set the number of threads\n";
			cout << "-out imageName to save an image with imageName\n";
			cout << "-tasks to show all task during the processing\n";
			cout << "-header show the image header informations\n";
		}
}


