#ifndef TMalla_HPP
#define TMalla_HPP

#include "TEntidad.hpp"

//recursos necesarios para tmalla
#include "RMalla.hpp"

class TMalla : public TEntidad
{
    private:
        //punteros a recursos
        RMalla * objetos;//diferentes frames para animaciones
        float frames_totales,mallas_totales,frame_inicial,frame_final,frame_actual,velocidad_animacion;
        float actual_time;
        bool bucle;//si esta activo esta en bucle si esta desactivado no esta en bucle, por defecto es true
        float transparente;
        bool render = false; //Dibujado de render o de profundidad
        std::vector<std::string> textures_animation;
        unsigned short actual_texture = 0;
        float actual_time_texture;
        float velocidad_animacion_texture;

    public:
        // Constructor y destructor
        TMalla(int ft);
        ~TMalla();
        void cargarMalla(unsigned short,unsigned short);

        // Recibir recurso
        void setRecursoObjeto(RMalla *);//recibe un puntero de la malla

        // sobrecarga metodos TEntidad
        void beginDraw();
        void endDraw();

        //Animacion
        void BucleAnimacion(unsigned short,unsigned short);
        void setVelocidadAnimacion(float);
        unsigned short getFrameInicio();
        unsigned short getFrameFinal();
        unsigned short getFrameActual();
        bool getBucle();//devuelve si esta en bucle o no la animacion
        void EstaEnBucleAnimacion(bool);//si se le pasa true la animacion se repetira indefinidamente, si esta en false cuando llegue a frame final se quedara en ese frame
        void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
        void setTexture(const char * _ruta);
        void setTransparencia(float t); //Aplicar transparencia
        void setRender(bool r);
        void Setanimationtexture(std::string ruta_textura1, std::string ruta_textura2, std::string ruta_textura3, float velocidad);
};

#endif
