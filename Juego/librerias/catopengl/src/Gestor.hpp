#include <string>
#include <vector>
#include "Recurso.hpp"
#include "RMalla.hpp"
#include "TMalla.hpp"
#include "TEntidad.hpp"
#include "TNodo.hpp"

//PARA INFORMACION MAS DETALLADA SOBRE LAS FUNCIONES MIRAR EN EL CPP
class Gestor
{

    public:

        //clase singleton en public
        ~Gestor();

        static Gestor * GetInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if(!_unica_instancia)
            {
                _unica_instancia = new Gestor();
            }
            
            return _unica_instancia;  
        }
        //fin singleton public

        unsigned short ObtenerRecurso(const char *,TNodo *,int);//obtiene el recurso y lo instancia en memoria

        unsigned char * CargarImagen(const char *,int *, int *, int *);//devuelve la imagen cargada

        bool DestruirObjeto(unsigned short);//destruye el objeto de memoria (no lo destruye de opengl, para esto hay que llamar a interfaz.RemoveObject(id a destruir))

        bool LimpiarRecursos();//limpia todos los recursos en memoria (no en opengl) CUIDADO

        bool LimpiarImagenes();//limpia todas las imagenes en memoria (no en opengl) CUIDADO

    private:

        //clase singleton 
        Gestor();
        static Gestor * _unica_instancia;
        //fin clase singleton private

        //clase que nos sirve para almacenar el recurso de forma mas organizada
        struct Archivador //para mallas
        {
            ~Archivador()
            {
                id = 0;
                _nombre = nullptr;
                _recursos = nullptr;
            };
            unsigned char id;//id del archivo
            const char * _nombre;//nombre del archivo
            Recurso * _recursos;
        };

        struct Imagen
        {
            Imagen()
            {
                _imagen = nullptr;
                _nombre = nullptr;
            }
            ~Imagen()
            {
                if(_imagen != nullptr)
                {
                    stbi_image_free(_imagen);
                }

                if(_nombre != nullptr)
                {
                    delete [] _nombre;
                }
            }
            unsigned char * _imagen;//datos de la imagen
            //char * _nombre;//nombre del recurso por el que se identifica
            const char * _nombre;//nombre del recurso por el que se identifica 
            int width, height, nrComponents;//altura, anchura y numero de componentes de la imagen
        };

        std::vector<Archivador *> archivadores;//contiene los ids,nombres y punteros a los recursos en memoria (disco o ram)

        std::vector<Imagen *> imagenes;//contiene todas las imagenes que se han instanciado en el juego

        unsigned short ids = 0;//comenzamos a dar ids desde 0

        unsigned short generarId();//genera un id para un archivador

        bool buscarRecurso(unsigned short);//nos dice si un recurso con un id existe o no

        unsigned short buscarRecurso(const char *);//nos busca por la ruta del recurso si existe te devuelve su archivador si no te devuelve 0

        int buscarImagen(const char *);//busca la imagen si no existe devuelve -1, si existe devuelve la posicion en el vector de imagenes

        Archivador * recuperarRecurso(unsigned short);//sirve para devolver el archivador


};
