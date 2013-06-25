/* 
 * Created on 9 de Junho de 2013, 22:02
*/
#include "ImageLoader.h"

using namespace std;
typedef struct _ARGSI{
        unsigned short **mat;
        int i;
        int j;
        int iMax;
        int jMax;
}ARGSI;
class ParallelImageLoaderPthread : public ImageLoader{
public:
    ParallelImageLoaderPthread(string path):ImageLoader(path){load();};
    virtual unsigned short **alocarMatriz(unsigned short **matriz);
    
private:

};



