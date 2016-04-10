#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdint>
#include "pgm.h"

using namespace std;

void usage() {
	cout<<"Para Compilar:\nmake t5\n";
	cout<<"./t5 img.pgm filtro{Media, Mediana, Gauss} parametro\n";
}

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

	return 0;
}
