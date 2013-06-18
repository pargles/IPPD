#pragma once
#include <iostream>// cout
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#elif MACOS
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>
#endif

using namespace std;

/**
 *@file Parser.h
 *@brief Responsável por separar os parametros que vao ser informados quando o programa for chamado.
 */
class Parser {

	private:
            bool omp;//1.1
            bool pthread;//1.2
            bool showTasks;
            bool otsu;
            bool showHeaderInfo;
            bool imageOut;
            string imageOutName;
            string imageAdress;
            short numOfThreads;
   	public:
		Parser();
                bool isOMP();
                bool isPthread() ;
                bool isOTSU() ;
                bool isshowHeader() ;
                bool isshowTasks() ;
                bool isimageOut() ;
                void setOMP();
                void setPthread();
                void setTasks();
                void setImageOut();
                void setOTSU();
                 void setShowHeader();

                string getImageAdress();
                string getImageOutName();
                int getNumCores();
                int getNumOfThreads();
                void setNumOfThreads(int num);
                void setImageAdress(string Adress);
                void setImageOutName(string name);
		void parse(vector<string> Arguments);
};
