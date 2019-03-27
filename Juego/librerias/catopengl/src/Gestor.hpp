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

        Gestor();

        unsigned short ObtenerRecurso(const char *,TNodo *,int);//obtiene el recurso y lo instancia en memoria

        bool DestruirObjeto(unsigned short);//destruye el objeto de memoria (no lo destruye de opengl, para esto hay que llamar a interfaz.RemoveObject(id a destruir))

        bool LimpiarRecursos();//limpia todos los recursos en memoria (no en opengl) CUIDADO

        ~Gestor();//lo hacemos publico para borrarlo con  desde interfaz, esto a su vez llama a limpiarRecursos que hace delete de todos los recursos

    private:

        //clase que nos sirve para almacenar el recurso de forma mas organizada
        struct Archivador
        {
            ~Archivador()
            {
                id = 0;
                _nombre = nullptr;
                _recursos = nullptr;
            };
            unsigned short id;//id del archivo
            const char * _nombre;//nombre del archivo
            Recurso * _recursos;
        };

        std::vector<Archivador *> archivadores;//contiene los ids,nombres y punteros a los recursos en memoria (disco o ram)

        unsigned short ids = 0;//comenzamos a dar ids desde 0

        unsigned short generarId();//genera un id para un archivador

        bool buscarRecurso(unsigned short);//nos dice si un recurso con un id existe o no

        unsigned short buscarRecurso(const char *);//nos busca por la ruta del recurso si existe te devuelve su archivador si no te devuelve 0

        Archivador * recuperarRecurso(unsigned short);//sirve para devolver el archivador


};
