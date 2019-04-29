#ifndef TTexto_HPP
#define TTexto_HPP

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "TEntidad.hpp"

//Caracteres
struct Character {
    GLuint TextureID;   // Textura glyph
    glm::ivec2 Size;    // Tamanyo de glyph
    glm::ivec2 Bearing; // Desplazamiento desde la línea base del glyph a la izquierda/arriba
    long int Advance;   // Desplazamiento horizontal para avanzar al siguiente glyph
};

class TTexto : public TEntidad
{
    private:

        //opciones de texto
        GLuint texture;
        GLuint VAO, VBO;
        std::string texto;
        GLfloat x, y, endx, endy, scale;
        glm::vec3 color;
        float salto_linea;

        //mapa de caracteres
        std::map<GLchar, Character> Characters;

    public:

        // Constructor y destructor
        TTexto(GLuint, GLuint, Shader *);
        ~TTexto();

        //Cargar la lista de caracteres
        void CargarFuente(std::string, GLuint);
        //Crear texto nuevo
        void CrearTexto(std::string, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, float, float, float);

        //sobrecarga metodos TEntidad
        void beginDraw();
        void endDraw();

        //para cambiar de texto
        void CambiarTexto(std::string newtext);
        void CambiarPosicion(GLfloat xx, GLfloat yy);

        //cambio de propiedades de texto
        void CambiarAnchura(unsigned int);
        void CambiarColor(float,float,float);
};

#endif
