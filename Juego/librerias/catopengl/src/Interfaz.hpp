#include "CatOpengl.hpp"

#include <vector>
#include <iostream>

#include "TNodo.hpp"
#include "TTransform.hpp"
#include "TEntidad.hpp"
#include "TLuz.hpp"
#include "TCamara.hpp"
#include "TMalla.hpp"
#include "Shader.hpp"

class Interfaz
{
    public:

        Interfaz();

        ~Interfaz();

        unsigned short AddCamara();//creamos una camara

        unsigned short AddLuz(int);//creamos una luz

        unsigned short AddMalla(const char *,int initf);//creamos una malla

        void Draw();//pintamos el arbol de escena, antes se calcula la matriz view project y luego model individual para las mallas

        void RemoveObject(unsigned short);//remueve objeto de la escena

        void Trasladar(unsigned short,float,float,float);//trasladar

        void Rotar(unsigned short,float,float,float,float);//rotar

        void Escalar(unsigned short,float,float,float);//escalar

        bool VentanaEstaAbierta();//devuelve true si esta en ejecucion devuelve false si no lo esta

        double * GetPosicionRaton();//devuelve un array de tres posiciones (1,2,3) que es donde esta situado el raton

        void LimpiarGui();// limpiamos todos los elementos pertenecientes a la graphic user interfaces(GUI), rimagen y otros.
        
        void LimpiarEscena();// limpiamos todos los elementos pertenecientes a la escena, objetos y luces

        void EliminarCamara(unsigned short);// destruimos la camara a la que pertenezca el id

        void CambiarFondo(float r, float g, float b,float a);//cambia el fondo de la ventana

        void DefinirVentana(short unsigned int,short unsigned int,const char *); // cambia los valores width,height,title,si no existe tambien crea la ventana

    private:

        CatOpengl::Video::Ventana * window;

        Shader * shaders[4];//cuatro programas de shader(vertex y fragment cada uno)

        std::vector<TNodo *> camaras;//registro de camaras

        std::vector<TNodo *> luces;//registro de luces

        unsigned short ids = 0;//comenzamos a dar ids desde 0

        TNodo * _raiz; //puntero a raiz de arbol de escena

        unsigned short generarId(); //genera un id

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

        bool ventana_inicializada = true;//nos sirve para saber si tenemos que llamar a inicializar ventana

        void ventanaInicializar();

        void ventanaLimpiar();

        float x,y,z;
};
