#ifndef PGM_H
#define PGM_H

class Pgm{
    public:
    uint32_t **grid; //contem todos os pixels da imagem
    uint32_t height, width, maxval; 
    std::string type;

    Pgm();
    Pgm(uint32_t width, uint32_t height, uint32_t max_val);
    ~Pgm();
    uint32_t get_height()const {return height;}
    uint32_t get_width()const {return width;}
    uint32_t get_maxval()const {return maxval;}
    std::string get_type()const {return type;}
    static Pgm* Pgm_from_file(const char* filename);
    void write_to_file(const char filename[]);
    Pgm& operator=(const Pgm &rhs);
    void release_grid() ;
};

#endif
