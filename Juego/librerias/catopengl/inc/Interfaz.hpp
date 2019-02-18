#include "CatOpengl.hpp"

#include <vector>
#include <iostream>

#include "TNodo.hpp"
#include "TTransform.hpp"
#include "TEntidad.hpp"
#include "TLuz.hpp"
#include "TCamara.hpp"
#include "TMalla.hpp"

class Interfaz
{
    public:

        Interfaz();
        
        unsigned short AddCamara();//creamos una camara
        
        unsigned short AddLuz();//creamos una luz

        unsigned short AddMalla(const char *);//creamos una malla

        void Draw();//pintamos el arbol de escena, antes se calcula la matriz view project y luego model individual para las mallas

        void Remove();//borramos el arbol

        void RemoveObject(unsigned short);//remueve objeto de la escena

        void Trasladar(unsigned char,float,float,float);//trasladar 
        
        void Rotar(unsigned char,float,float,float);//rotar

        void Escalar(unsigned char,float,float,float);//escalar

    private:
        
        std::vector<TNodo *> camaras;
        
        std::vector<TNodo *> luces;
 
        unsigned short ids = 0;//comenzamos a dar ids desde 0

        TNodo * _raiz;

        ~Interfaz();

        unsigned short generarId();

        //nos sirve para buscar rapidamente un objeto y llamar a su funcion de pintado(esto se hace con una busqueda binaria)
        struct Nodo 
        {
            TNodo * recurso;//nodo que almacena escalado del objeto
            unsigned short id;//almacena el id a nivel local
            unsigned short idRecurso;//almacena el id del recurso (del gestor de recursos)
        };

        std::vector<Nodo *> nodos;//almacena los nodos

        CatOpengl::Gestor * gestorDeRecursos;

        Nodo * buscarNodo(unsigned short);
};