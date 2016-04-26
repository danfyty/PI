#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <sstream>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "filters.h"
#include "pgm.h"

using namespace std;

void usage() {
	cout<<"Para Compilar:\nmake t5\n";
	cout<<"./t5 entrada.pgm filtro{Media, Mediana, Gauss} parametro saida.pgm\n";
}

/*
argv[1] <- input.pgm
argv[2] <- filter
argv[3] <- filter param
argv[4] <- output.pgm
 */

int main(int argc, char **argv) {
	if(argc < 4) {
		usage();
		return EXIT_SUCCESS;
	}
	Pgm *img=Pgm::Pgm_from_file(argv[1]);
	if(img==NULL) {
		usage();
		return EXIT_SUCCESS;
	}
    if(strcasecmp(argv[2], "gauss")==0) {
        size_t sig;
        sscanf(argv[3], "%zu", &sig);
        Pgm *ret=gaussian(img,sig);
        ret->write_to_file(argv[4]);
        delete ret;
    }
    else if(strcasecmp(argv[2], "media")==0) {
        size_t n;
        sscanf(argv[3], "%zu", &n);
        Pgm *ret=median(img,n);
        ret->write_to_file(argv[4]);
        delete ret;
    }
    else if(strcasecmp(argv[2], "mediana")==0){
        size_t n;
        sscanf(argv[3], "%zu", &n);
        Pgm *ret=mean(img,n);
        ret->write_to_file(argv[4]);
        delete ret;
    }
    delete img;
	return EXIT_SUCCESS;
}
