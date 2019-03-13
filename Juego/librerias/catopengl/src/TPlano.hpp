#ifndef TPlano_HPP
#define TPlano_HPP

#include "TEntidad.hpp"

class TPlano : public TEntidad
{
    private:

        bool CargarTextura(const char * _ruta);
        void CargarMalla(unsigned int, unsigned int, float);

        // const char * _rutafile;
        // unsigned int px, py;
        // float scaleimage;
        int width, height, nrComponents;
        unsigned int textureID;
        unsigned int VAO, VBO, EBO; //Datos de render

    public:
        // Constructor y destructor
        TPlano(const char *, unsigned int, unsigned int, float, Shader *);
        ~TPlano();

        // sobrecarga metodos TEntidad
        void beginDraw();
        void endDraw();
};

#endif
