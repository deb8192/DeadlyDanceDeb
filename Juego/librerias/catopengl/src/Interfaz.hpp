#include <vector>
#include <iostream>

#include "TNodo.hpp"
#include "TTransform.hpp"
#include "TEntidad.hpp"
#include "TLuz.hpp"
#include "TCamara.hpp"
#include "TMalla.hpp"
#include "TPlano.hpp"
#include "TTexto.hpp"
#include "TBillboard.hpp"
#include "TParticle.hpp"
#include "Shader.hpp"
#include "Ventana.hpp"
#include "Gestor.hpp"

#define maxNodos 65534 //maximo de nodos

class Interfaz
{
    public:

        Interfaz();

        ~Interfaz();

        void CerrarVentana();//cierra la ventana

        unsigned short AddCamara();//creamos una camara

        unsigned short AddLuz(int);//creamos una luz

        unsigned short AddMalla(const char *,int initf,int shader);//creamos una malla

        unsigned short AddImagen(const char *, unsigned int, unsigned int, float , const char * rutapulsado = nullptr, const char * rutaencima = nullptr );//creamos una imagen en plano

        unsigned short AddTexto(std::string, GLuint); //Crear un texto

        unsigned short AddBoard(float ,float ,float ,float, float, const char *,float); //Crear un billboard (world x, world y, world z, local x, local y, ruta imagen/texto, prioridad)

        unsigned short AddParticles(float ,float ,float,unsigned int, float, float, const char *); //Crear sistema de particulas

        void Draw();//pintamos el arbol de escena, antes se calcula la matriz view project y luego model individual para las mallas

        void RemoveObject(unsigned short);//remueve objeto de la escena

        void Trasladar(unsigned short,float,float,float);//trasladar

        void Rotar(unsigned short,float,float,float);//rotar

        void Escalar(unsigned short,float,float,float);//escalar

        bool VentanaEstaAbierta();//devuelve true si esta en ejecucion devuelve false si no lo esta

        double * GetPosicionRaton();//devuelve un array de tres posiciones (1,2,3) que es donde esta situado el raton

        void LimpiarGui();// limpiamos todos los elementos pertenecientes a la graphic user interfaces(GUI), rimagen y otros.

        void LimpiarEscena();// limpiamos todos los elementos pertenecientes a la escena, objetos y luces

        void EliminarCamara(unsigned short);// destruimos la camara a la que pertenezca el id

        void CambiarFondo(float r, float g, float b,float a);//cambia el fondo de la ventana

        void DefinirVentana(short unsigned int,short unsigned int,const char *); // cambia los valores width,height,title,si no existe tambien crea la ventana

        unsigned short CrearTexto(std::string texto,short x,short y,float r = 0.0f,float g = 0.0f,float b = 0.0f); // texto, x e y(max y min de la pantalla), tamayo del texto siempre superior

        bool IsKeyDown(short);//se le pasa la tecla que quiere comprobar, esto va a la ventana y le pregunta si esta pulsada

        bool IsMouseClick(short);// comprobaciones de los botones del raton

        bool IsMouseUp(short);//comprueba si se ha liberado el boton

        void ChangeTargetCamara(unsigned short id, float x, float y, float z);//cambia donde apunta la camara

        void DeclararBoton(unsigned short id, unsigned short newid);

        bool DetectarPulsacion(int);//se le pasa el id del objeto o boton que se quiere comprobar si esta siendo pulsado por el raton

        void DeshabilitarObjeto(unsigned short);//cuando se vaya a pintar los objetos deshabilitados no seran procesados

        void HabilitarObjeto(unsigned short);//cuando se habilite sera procesado por el pintado

        float * GetPosicion(unsigned short);//obtiene la posicion que tenga la transformacion

        float * GetTarget(unsigned short);//obtiene donde apunta la camara en el momento

        void EscalarImagen(unsigned short nid,float x,float y,bool enx = true, bool eny = true);//escala la imagen en x e y,si solo se quiere escalar de un lado se le tiene que pasar false en enx o eny

        void CambiarTexto(unsigned short nid,std::string texto);//cambia el texto del elemento que le pases como nid

        void CambiarPosicionTexto(unsigned short nid, float x, float y); //Cambia la posicion del texto

        int getStartFrame(unsigned short);//consigue el frame inicial

        int getFrameNr(unsigned short);//consigue el frame actual

        void setFrameLoop(unsigned short,int,int);//le asigna desde que frame a que frame debe cambiar la animacion

        void setAnimationSpeed(unsigned short,int);//le asigna velocidad a la animacion

        void SetColor(unsigned short did, unsigned char r, unsigned char g, unsigned char b, unsigned char a); //Cambia el color de una malla

        void SetTexture(unsigned short did, const char * _ruta); //Le asigna una texura a una malla

        void SetTransparencia(unsigned short did, float transp); //Se pone transparente la malla

        void RemoveObjectForID(signed int idPerson);//borra por el id personalizado = si el id es -1 no funciona este metodo

        void DefinirIdPersonalizado(unsigned short did, signed int idPerson);//le asigna el id personalizado

        void DefinirTextoBoton(unsigned short imagen,unsigned short texto);//le asigna a un boton(imagen), el texto

        void DetenerSistema(unsigned short part); //Detener sistema de particulas

        void IniciarSistema(unsigned short part); //Iniciar sistema de particulas

        void DistanciaLuz(unsigned short luz, float d); //Aplica una distancia a la luz

        //Colores de luz
        void ColorAmbiental(unsigned short luz, float r,float g,float b);
        void ColorDifusa(unsigned short luz, float r,float g,float b);
        void ColorSpecular(unsigned short luz, float r,float g,float b);

        //define el bucle de la animacion
        void setBucle(unsigned short,bool);

        //cercania y lejania de la camara
        void SetLejaniaCamara(unsigned short camara,float lejania);
        void SetCercaniaCamara(unsigned short camara,float cercania);

        //para saber si esta liberado
        bool IsKeyRelease(short);

        //cambia propiedades de los textos
        void AnchoTexto(unsigned short,unsigned int);//cambia ancho del texto
        void CambiarColorTexto(unsigned int did,float r, float g, float b);//cambia el color del texto

        //cambiar estado imagen o boton
        void CambiarEstadoImagen(unsigned int event,unsigned int nuevoEstado);//estado sobretodo para botones
        void CambiarPosicionImagen(unsigned int event, float x, float y);//mueve la imagen a la posicion que le digas

        //para activar y desactivar captura de texto, tambien sirve para saber que ha capturado
        void ActivarCapturaTexto();// habilita que el texto que se ponga se capture hasta un maximo de 30 digitos
        void DesactivarCapturaTexto();// deshabilita que el texto se capture
        void InicializarCapturaTexto(const char * texto);//inicializa el texto del capturador con lo que le pases
        char * DevolverTextoCapturado();//devuelve el texto que hay en el capturador
        void BorrarUltimaLetra();//borra la ultima letra del capturador



    private:

        bool ModoOneCamara;//nos sirve para saber si queremos tener una camara como si fueran varias (por defecto activo)

        Ventana * window;// instancia que contiene la clase que se encarga de gestionar las ventanas y las teclas / raton

        Shader * shaders[7];//cuatro programas de shader(vertex y fragment cada uno)

        unsigned short ids = 0;//comenzamos a dar ids desde 0

        TNodo * _raiz; //puntero a raiz de arbol de escena

        unsigned short generarId(); //genera un id

        //nos sirve para buscar rapidamente un objeto y llamar a su funcion de pintado(esto se hace con una busqueda binaria)
        struct Nodo
        {
            Nodo()
            {
                recurso = nullptr;//nodo que almacena escalado del objeto
                id = 0;//almacena el id a nivel local
                idRecurso = 0;//almacena el id del recurso (del gestor de recursos)
                tipo=0;//1 camara, 2 luces, 3 mallas, 4 imagenes, 5 textos
                activo = true;//solo para camaras
                idPersonalizado = -1;//sirve para identificar el id por el id
                id_texto = 0;
            }
            ~Nodo()
            {
                if(recurso != nullptr && recurso)
                {
                    delete recurso;
                    recurso = nullptr;
                }
            };
            TNodo * recurso;//nodo que almacena escalado del objeto
            unsigned short id;//almacena el id a nivel local
            unsigned short idRecurso;//almacena el id del recurso (del gestor de recursos)
            unsigned short tipo;//1 camara, 2 luces, 3 mallas, 4 imagenes, 5 textos
            unsigned short id_texto;//esto sirve para los botones(imagenes), se borra automaticamente cuando se borra la imagen
            bool activo;//solo para camaras
            int idPersonalizado;//sirve para identificar el id por el id
        };

        Nodo * banco[maxNodos];//contiene los punteros a los nodos del arbol

        std::vector<Nodo *> camaras;//registro de camaras

        std::vector<Nodo *> luces;//registro de luces

        std::vector<Nodo *> imagenes;//registro de imagenes en interfaz

        std::vector<Nodo *> textos;//registro de imagenes en interfaz

        std::vector<Nodo *> boards;//registro de billboards en interfaz

        std::vector<Nodo *> particles; //registro de sistemas de particulas en interfaz

        Gestor * gestorDeRecursos;//clase que gestona los recursos del motor

        Nodo * buscarNodo2(unsigned short);

        Nodo * buscarNodo3(signed int);

        bool ventana_inicializada = true;//nos sirve para saber si tenemos que llamar a inicializar ventana

        void ventanaInicializar();

        void ventanaLimpiar();

        float x,y,z;

        unsigned int cualborrar;

        void pulgarReferencia(Nodo * referencia,unsigned short tipo);//limpia la referencia del tipo de objeto que le pases

};
