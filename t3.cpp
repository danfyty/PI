#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
using namespace std;
typedef unsigned char byte;

void usage() {
    cout<<"Trabalho 3\n";
    cout<<"compilar: g++ t3.cpp -o t3\n";
    cout<<"Executar:\n";
    cout<<"./t3 a.pgm x y new_color\n";
}

struct img_pgm{
    byte **grid; //contem todos os pixels da imagem
    int height, width, max_val;
    string type;
    img_pgm();
    img_pgm(int width, int height, int max_val):height(height), width(width), max_val(max_val) {
        grid=new byte*[height+10];
        for(size_t i=0;i<height;i++)
            grid[i]=new byte[width+1];
    }
    ~img_pgm() {
        for(size_t i=0;i<height;i++)
            delete[] grid[i];
        delete[] grid;
    }
};

/*
    le pgm 
    cria objeto img_pgm e retorna
 */
img_pgm* read_img(const char filename[]) {
    ifstream fpin(filename);
    if(!fpin.is_open())
        return NULL;
    string line, str, type;
    img_pgm *ret=NULL;

    int px_read=0, lr=0;//pixes read so far, lines read so far.
    bool will_read_maxval=false;

    while(getline(fpin, line)) {
        if(!line.size() || line[0]=='#') 
            continue;
        if(lr==0) 
            type=line;
        else if(lr==1) {
            stringstream IN(line);
            int height, width, max_val=255;
            int cx=0, tmp;
            while(IN>>tmp) {
                if(cx==0)
                    width=tmp;
                else if(cx==1)
                    height=tmp;
                else max_val=tmp;
                ++cx;
            }
            if(cx==2)
                will_read_maxval=true;
            ret=new img_pgm(width, height, max_val);
        }
        else if(lr>1) {
            stringstream IN(line);
            int btv;
            if(will_read_maxval) {
                IN>>ret->max_val;
                will_read_maxval=0;
            }

            for(;IN>>btv;px_read++) { 
                ret->grid[px_read/ret->width][px_read%ret->width]=btv;
                //cout<<btv<<endl;
            }
        }
        ++lr;
    }
    ret->type=type;
    fpin.close();
    return ret;
}

void write_img(const char filename[], img_pgm *img) {
    ofstream fpout(filename);
    if(!fpout.is_open())
        return ;
    fpout<<img->type<<'\n';
    fpout<<img->width<<' '<<img->height<<' '<<img->max_val<<'\n';
    for(size_t i=0;i<img->height;i++) {
        for(size_t j=0;j<img->width;j++) {
            if((i*img->width+j)%20==0)
                fpout<<'\n';
            fpout<<(int)img->grid[i][j]<<' ';
        }
    }
    fpout.close();
}

/*
   nome da imagem na qual o flood_fill sera feito,
   sx, sy => pixel de inicio (0-based)
   cval -> nova cor
 */
void flood_fill(char filename[], int sx, int sy, int cval) {
    img_pgm *img=read_img(filename);
    if(img==NULL)
        return ;
    byte orig_col=img->grid[sy][sx];

    /*bfs*/
    vector<vector<bool> >mark(img->height, vector<bool>(img->width, false));
    queue<pair<int, int> >q;
    q.push(pair<int, int>(sy, sx) );
    mark[sy][sx]=1;
    int dir[][2]={{0,1},{1,0},{0,-1},{-1,0}};
    while(!q.empty()) {
        int ui=q.front().first;
        int uj=q.front().second;
        img->grid[ui][uj]=cval;
       // cout<<(int)img->grid[ui][uj]<<"$$\n";
        q.pop();
        for(size_t d=0;d<4;d++) {
            int vi=ui+dir[d][0];
            int vj=uj+dir[d][1];
            if(vi>=img->height||vi<0||vj>=img->width||vj<0||img->grid[vi][vj]!=orig_col||mark[vi][vj])
                continue;
            mark[vi][vj]=true;
            q.push(pair<int,int>(vi,vj));
        }
    }
    /*fim bfs*/
    write_img(filename, img);
    delete img;
}

int main(int argc, char *argv[]) {
    if(argc<5) {
        usage();
        return 0;
    }

    int sx, sy, nc;
    sscanf(argv[2], "%d", &sx);
    sscanf(argv[3], "%d", &sy);
    sscanf(argv[4], "%d", &nc);
    flood_fill(argv[1], sx, sy, nc);
    return 0;
}
