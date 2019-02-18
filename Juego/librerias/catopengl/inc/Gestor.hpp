#include <string>
#include <vector>
//PARA INFORMACION MAS DETALLADA SOBRE LAS FUNCIONES MIRAR EN EL CPP
class Gestor
{

    public:

        Gestor();
        
        unsigned short ObtenerRecurso(const char *);//obtiene el recurso y lo instancia en memoria

        bool DestruirObjeto(unsigned short);//destruye el objeto de memoria (no lo destruye de opengl, para esto hay que llamar a interfaz.RemoveObject(id a destruir))

        bool LimpiarRecursos();//limpia todos los recursos en memoria (no en opengl) CUIDADO

        void Remove();//se destruye el gestor

    private:

        ~Gestor();

        //clase que nos sirve para almacenar el recurso de forma mas organizada
        struct Archivador
        {
            unsigned short id;//id del archivo 
            const char * _nombre;//nombre del archivo
            //recurso, clase especializada sea un shader(texto plano),malla(objetos 3d) o imagen(texturas)
        };

        std::vector<Archivador *> archivadores;//contiene los ids,nombres y punteros a los recursos en memoria (disco o ram)

        unsigned short ids = 0;//comenzamos a dar ids desde 0

        unsigned short generarId();//genera un id para un archivador

        bool buscarRecurso(unsigned short);//nos dice si un recurso con un id existe o no

        unsigned short buscarRecurso(const char *);//nos busca por la ruta del recurso si existe te devuelve su archivador si no te devuelve 0

};