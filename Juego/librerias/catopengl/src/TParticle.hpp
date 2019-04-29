#ifndef TParticle_HPP
#define TParticle_HPP

#include "TEntidad.hpp"

//Particula y sus propiedades
struct Particle
{
    glm::vec3 Position, Velocity;
    glm::vec4 Color;
    GLfloat Life;

    Particle():Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f){}
};

class TParticle : public TEntidad
{
    private:

        //opciones de particulas
        GLuint VAO, VBO, EBO;
        GLuint texture;
        int width, height, nrComponents;
        std::vector<Particle> particles;
        glm::vec3 iniVelocidad;
        GLuint max_particles;          //numero de particulas maximo
        GLuint lastUsedParticle = 0;   //ultima paritucula cargada
        GLfloat colocarZ = 0;          //pone los sprites delante
        GLfloat output = 0;            //espacio de aparicion de particulas
        GLfloat life_particles = 1.0f; //Tiempo de vida de las particulas
        bool stop = false;             //parar sistema

        //Funciones privadas
        void GeneradordeParticulas(const char * _ruta); //Crea las particulas
        GLuint ParticulaNoUsada();                      //Devuelve el indice de la primera particula no usada en el array.
        void RespawnParticulas(Particle &particle); //Respawn de las particulas
        void UpdateParticulas(float deltaT, GLuint newParticles);  //Actualizar sistema de particulas

    public:

        // Constructor y destructor
        TParticle(float, float, float, unsigned int, float, float, const char *, Shader *);
        ~TParticle();

        void stopParticles();
        void startParticles();

        //sobrecarga metodos TEntidad
        void beginDraw();
        void endDraw();
};

#endif
