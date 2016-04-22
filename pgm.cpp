#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <cstdint>
#include "pgm.h"

using namespace std;

Pgm::Pgm() {
    height=width=maxval=0;
}
Pgm::Pgm(uint32_t width, uint32_t height, uint32_t maxval):height(height), width(width), maxval(maxval) {
    grid=new uint32_t*[height];
    for(size_t i=0;i<height;i++)
        grid[i]=new uint32_t[width];
}

void Pgm::release_grid() {
    for(size_t i=0;i<height;i++)
        delete[] grid[i];
    delete[] grid;
}

Pgm::~Pgm() {
    release_grid();
}

Pgm& Pgm::operator=(const Pgm &rhs){
    release_grid();
    height=rhs.get_height();
    width=rhs.get_width();
    maxval=rhs.get_maxval();
    type=rhs.get_type();

    grid=new uint32_t*[height];
    for(size_t i=0;i<height;i++)
        grid[i]=new uint32_t[width];

    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
            grid[i][j]=rhs.grid[i][j];
    return *this;
}

Pgm* Pgm::Pgm_from_file(const char filename[]) {
    ifstream fpin(filename);
    if(!fpin.is_open())
        return NULL;


    string line, str, type;
    Pgm *ret=NULL;
    uint32_t px_read=0; 
    size_t lr=0;//pixes read so far, lines read so far.
    bool will_read_maxval=false;

    while(getline(fpin, line)) {
        if(!line.size() || line[0]=='#') 
            continue;
        if(lr==0) 
            type=line;
        else if(lr==1) {
            stringstream IN(line);
            uint32_t height, width; 
            uint32_t maxval=255;
            int cx=0, tmp;
            while(IN>>tmp) {
                if(cx==0)
                    width=tmp;
                else if(cx==1)
                    height=tmp;
                else maxval=tmp;
                ++cx;
            }
            if(cx==2)
                will_read_maxval=true;
            ret=new Pgm(width, height, maxval);
        }
        else if(lr>1) {
            stringstream IN(line);
            uint32_t btv;
            if(will_read_maxval) {
                IN>>ret->maxval;
                will_read_maxval=0;
            }
            if(ret->width==0)
                return NULL;
            for(;IN>>btv;px_read++) { 
                if(px_read/ret->width >= ret->height || px_read%ret->width >= ret->width)
                    return NULL;
                ret->grid[px_read/ret->width][px_read%ret->width]=btv;
            }
        }
        ++lr;
    }
    ret->type=type;
    fpin.close();
    return ret;
}

void Pgm::write_to_file(const char filename[]) {
    ofstream fpout(filename);
    if(!fpout.is_open())
        return ;
    fpout<<type<<'\n';
    fpout<<(int)width<<' '<<(int)height<<' '<<(int)maxval<<'\n';
    for(size_t i=0;i<height;i++) {
        for(size_t j=0;j<width;j++) {
            if((i*width+j)%20==0)
                fpout<<'\n';
            fpout<<grid[i][j]<<' ';
        }
    }
    fpout.close();
}
