#include <vector>
#include <algorithm>
#include "filters.h"
#include "pgm.h"


/*considerando n impar*/
Pgm* median(Pgm *img, size_t n) {
    if(img==NULL)
        return NULL;
    Pgm *ret=new Pgm();
    *ret=*img;

    n/=2;
    for(size_t i=n;i<img->get_height()-n;++i)
        for(size_t j=n;j<img->get_width()-n;++j) {
            size_t s=0;
            for(size_t ki=i-n;ki<=i+n;++ki)
                for(size_t kj=j-n;kj<=j+n;kj++)
                    s+=img->grid[ki][kj];
            /*floor*/
            ret->grid[i][j]=s / ((2*n+1)*(2*n+1));
        }
    return ret;
}

Pgm* mean(Pgm *img, size_t n) {
    if(img==NULL)
        return NULL;
    Pgm *ret=new Pgm();
    *ret=*img;

    n/=2;
    for(size_t i=n;i<img->get_height()-n;++i)
        for(size_t j=n;j<img->get_width()-n;++j) {
            std::vector<uint32_t> aux;
            for(size_t ki=i-n;ki<=i+n;++ki)
                for(size_t kj=j-n;kj<=j+n;kj++)
                    aux.push_back(img->grid[ki][kj]);
            std::sort(aux.begin(), aux.end());
            /*floor*/
            ret->grid[i][j]=aux[aux.size()/2];
        }
    return ret;

}
