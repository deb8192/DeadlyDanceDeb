#ifndef TBillboard_HPP
#define TBillboard_HPP

#include <ft2build.h>
#include FT_FREETYPE_H

#include "TEntidad.hpp"

class TBillboard : public TEntidad
{
    private:

        //opciones de board
        GLuint VAO, VBO, EBO;
        GLuint texture;
        int width, height, nrComponents;
        GLfloat posx, posy, posz;
        glm::vec3 color;
        glm::vec3 localxyz;

        //Cargar cuadrado de billboard
        void CargarBillboard(const char *);

    public:

        // Constructor y destructor
        TBillboard(GLfloat, GLfloat, GLfloat, const char *, Shader *, GLfloat, GLfloat, GLfloat);
        ~TBillboard();

        //sobrecarga metodos TEntidad
        void beginDraw();
        void endDraw();
};

#endif
