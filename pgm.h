#ifndef PGM_H
#define PGM_H

class Pgm{
    private:
    uint8_t **grid; //contem todos os pixels da imagem
    uint32_t height, width; 
    uint8_t maxval;
    std::string type;

    public:
    Pgm();
    Pgm(uint32_t width, uint32_t height, uint8_t max_val);
    ~Pgm();
    uint32_t get_height(){return height;}
    uint32_t get_width(){return width;}
    uint8_t get_maxval(){return maxval;}
    std::string get_type(){return type;}
    static Pgm* Pgm_from_file(const char* filename);
    void write_to_file(const char filename[]);
};

#endif
