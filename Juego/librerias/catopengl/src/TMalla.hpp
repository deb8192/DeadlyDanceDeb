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

};

#endif
