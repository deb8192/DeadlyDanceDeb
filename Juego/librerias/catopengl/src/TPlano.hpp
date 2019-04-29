#ifndef TPlano_HPP
#define TPlano_HPP

#include "TEntidad.hpp"
//#include "Gestor.hpp"

class TPlano : public TEntidad
{
    private:

        bool CargarTextura(const char * _ruta,unsigned int = 1);
        void CargarMalla(unsigned int, unsigned int, float, float);
        void UdateMesh();

        GLuint winwidth, winheight;
        // const char * _rutafile;
        // unsigned int px, py;
        // float scaleimage;
        bool cambios = false;
        float pixx, pixy;
        float escaladox, escaladoy;
        int width, height, nrComponents;
        unsigned int textureID;//textura sin pulsar y sin pasar por encima
        unsigned int textureIDPulsado;//textura para cuando pulsas encima
        unsigned int textureIDEncima;//textura para cuando pasas por encima
        bool esPulsable;//si lo es se pone a true,si no lo es a false
        bool esEncima;//si lo es se pone a true,si no lo es a false
        unsigned int estado;//nos determina que imagen estamos cargando por defecto es estado = textureID
        unsigned int VAO, VBO, EBO; //Datos de render
        int id;//id del boton

    public:
        // Constructor y destructor
        TPlano(const char *, unsigned int, unsigned int, float, Shader *, GLuint, GLuint,const char * rutapulsado = nullptr,const char * rutaencima = nullptr);
        ~TPlano();

        void setSize(float,float); //ancho largo
        void setPosition(float,float); //x,y
        void setScale(float,float); //escalado
        bool botonPulsado(double *); //pulsar boton

        // sobrecarga metodos TEntidad
        void beginDraw();
        void endDraw();

        //seccion para botones
        bool Comprobar();
        void CambiarId(int);
        int getID();

        //escalados
        void setScaleY(float);
        void setScaleX(float);

        //estado de la imagen
        bool GetEsPulsable();//te dice si esta imagen tiene estado de pulsado
        bool GetEsEncima();//te dice si esta imagen tiene estado de estar encima
        void CambiarEstado(unsigned int);//1 para normal, 2 para pulsable, 3 para encima (si no existe el estado se queda en el que esta)
};

#endif
