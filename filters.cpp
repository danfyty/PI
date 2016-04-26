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

std::vector<std::vector<double> >
get_gaussian_filter_mask(int n, size_t sig) {
    std::vector<std::vector<double> > mask(2*n+1,std::vector<double>(2*n+1));
    n/=2;

    size_t sqr_sig=sig*sig;
    double aux;
    double mm=1;
    for(int y=-n;y<=n;++y) {
        for(int x=-n;x<=n;++x) {
            aux=((double)(x*x+y*y))/(double)sqr_sig;
            mask[y+n][x+n]=exp(-0.5*aux); 
            if(mask[y+n][x+n]<mm)
                mm=mask[y+n][x+n];
        }
    }
    for(int y=-n;y<=n;++y) {
        for(int x=-n;x<=n;++x) 
            mask[y+n][x+n]/=mm;
    }
    return mask;
}

Pgm* gaussian(Pgm *img, size_t sig) {
    if(img==NULL)
        return NULL;
    Pgm *ret=new Pgm();
    *ret=*img;
    size_t n=6 * sig| !(sig&1);
    std::vector<std::vector<double> >mask;
    mask=get_gaussian_filter_mask(n, sig);

    n/=2;
    double s=0;
    for(size_t i=0;i<mask.size();i++)
        for(size_t j=0;j<mask[i].size();j++)
            s+=mask[i][j];

    for(size_t i=n;i<img->get_height()-n;++i)
        for(size_t j=n;j<img->get_width()-n;++j) {
            double val=0;
            for(size_t ki=i-n;ki<=i+n;++ki)
                for(size_t kj=j-n;kj<=j+n;kj++) 
                    val+=mask[ki-i+n][kj-j+n] * img->grid[ki][kj];
            ret->grid[i][j]=(uint32_t)round(val / s);
        }
    return ret;
}


