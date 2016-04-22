#ifndef FILTERS_H
#define FILTERS_H

#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "pgm.h"


Pgm* median(Pgm *img, size_t n);
Pgm* mean(Pgm *img, size_t n);
Pgm* gaussian(Pgm *img, size_t mi);
std::vector<std::vector<double> >
get_gaussian_filter_mask(int n, size_t sig);


#endif
