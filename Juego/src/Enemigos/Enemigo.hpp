#ifndef Enemigo_HPP
#define Enemigo_HPP
#include "../INnpc.hpp"
#include "../INdrawable.hpp"
#include "../INsentidos.hpp"
#include "../Armas/Arma.hpp"
#include "../Jugando/Sala.hpp"
#include <vector>
#include "../Arbol.hpp"

class Enemigo : public INnpc , public INdrawable, public INsentidos //multiple herencia a esto se le llama derivacion multiple
{

    public:
        Enemigo();
        ~Enemigo();

        void definirSala(Sala * sala);

        //sentidos metodos
        void generarSonido(int intensidad,double duracion,int tipo);//la intensidad es el alcance y la duracion es cuanto dura el sonido, el tipo 1 son sonidos del jugador, 2 es pedir ayuda de los enemigos

        void queEscuchas();//recupera la informacion de los sonidos que escucha

        void queVes();//recupera informacion de los objetos,enemigos,jugador que ve.
        //drawables metodos

        //npc metodos
        int Atacar(int i);//efectua un ataque normal, llama al motor para ejecutar la animacion.
        //void AtacarEspecial();//efectua el ataque especial segun el tipo, esto llama a motor grafico para realizar la animacion, cuando se termina se pone a cero la barra
        int AtacarEspecial();//efectua el ataque especial segun el tipo, esto llama a motor grafico para realizar la animacion, cuando se termina se pone a cero la barra
        void QuitarVida(int);//quita vida a la entidad
        bool estasMuerto();//llama desde Nivel
        bool finalAnimMuerte();// si la animacion de muerte acaba, entonces en nivel lo mataremos del todo
        void MuereEnemigo(int enemi);//Animacion de muertes
        void RecuperarVida(int);//le suma vida a la entidad
        void AumentarBarraAtEs(int);//aumenta el valor de la barra de ataque critico
        void Interactuar(int, int);//llama a la mecanica de interactuar
        void moverseEntidad(float);//Realiza el desplazamiento mediante la interpolacion
        void RotarEntidad(float);//Realiza la rotacion mediante la interpolacion
        void UpdateTimeMove(float);//actualiza el tiempo del movimiento de la interpolacion
        void UpdateTimeRotate(float);
        
        //getters y setters

        void setID(int);
        void setPosiciones(float nx,float ny,float nz);
        void setNewPosiciones(float nx,float ny,float nz);
        void setLastPosiciones(float nx,float ny,float nz);
        void setRotacion(float nrx, float nry, float nrz);
        void setNewRotacion(float nrx, float nry, float nrz);
        void setLastRotacion(float nrx, float nry, float nrz);
        void setVectorOrientacion();
        void setPosicionesFisicas(float nx,float ny,float nz);
        void initPosicionesFisicas(float nx,float ny,float nz);
        void setVida(int vid);
        void setTipo(int tip);
        void setBarraAtEs(int bar);
        void setAtaque(int ataq);
        void setArmaEspecial(int ataque);
        void setSuerte(int suer);
        void setDanyoCritico(int danyoC);
        void setProAtaCritico(int probabilidad);
        void setSala(Sala* sala);
        void setTimeMerodear(float t);
        void setLastTimeMerodear(float t);
        void setAtackTime(float t);
        void setTimeAt(float time);
        void setLastTimeAt(float time);
        void setTimeAtEsp(float time);
        void setLastTimeAtEsp(float time);
        void setRotation(float rot);
        void setPosAtaques(int p);
        void setVelocidadMaxima(float velocidad); //modifica la VelocidadMaxima de desplazamiento
        void SetEnemigo(int);

        int getID();
        int getVida();
        int getTipo();
        int getBarraAtEs();
        int getAtaque();
        int getPosAtaques();
        int getSuerte();
        int getDanyoCritico();
        int getProAtaCritico();
        int* getBuffos();
        Sala* getSala();
        float getTimeMerodear();
        float getLastTimeMerodear();
        float getAtackTime();
        float getTimeAt();
        float getLastTimeAt();
        float getTimeAtEsp();
        float getLastTimeAtEsp();
        float getX();
        float getY();
        float getZ();
        float getNewX();
        float getNewY();
        float getNewZ();
        float getLastX();
        float getLastY();
        float getLastZ();
        float getFisX();
        float getFisY();
        float getFisZ();
        float getRX();
        float getRY();
        float getRZ();
        float getAtX();
        float getAtY();
        float getAtZ();
        float getVelocidadMaxima(); //se obtiene la VelocidadMaxima de desplazamiento
        int GetEnemigo();

        //comportamientos bases
            bool ver(int tipo);//1 si ve al jugador
            bool oir(int tipo);//1 si se oye jugador, 2 si se oye enemigo(pedir ayuda)
            bool buscar();//por defecto devuelve true
            bool perseguir();//por defecto devuelve true
            bool Acciones(int);//esto es para recorrer el arbol
            bool pedirAyuda();//pide ayuda
            bool ContestarAyuda();//esto es de prueba no hace dayo tampoco
            bool Merodear(short int maxRotacion);//para dar vueltas por una zona, segun entero que reciba ira en una direccion
        //fin comportamientos bases

        //ia
        short int randomBinomial();//devuelve un valor random entre -1 y 1
        void setArbol(Arbol);//asigna un arbol de ia al enemigo
        Arbol *getArbol();//devuelve el puntero al arbol de ia que tiene, CUIDADO si no tiene arbol devuelve nullptr
        void UpdateIA(); //funcion que llama desde nivel a la IA del enemigo que sea que activara la lectura del arbol segun sea un pollo, un murcielago... etc
        void UpdateBehavior(short int i); //actualiza el comportamiento actual del pollo
        short int* RunIA(bool);//corre la ia del enemigo
        //fin ia

    protected:

        //Comparadores de la lectura de las acciones y objetivos de las tareas
        enum accionesEnemigo 
        {  
            EN_MOVERSE = 0,
            EN_ATACAR,
            EN_VER,
            EN_PIDE_AYUDA,
            EN_MERODEA
        };

        Sala * estoy;//sala en la que esta el enemigo
        float atx, atespx, aty, atespy, atz, atespz, atgx, atgy, atgz, incrAtDisCirc, atespposX, atespposY, atespposZ;
        float atacktime = 0.0f;
        float tiempoMerodear, lastTiempoMerodear;
        Arma *armaEspecial;
        const char * rutaArmaEspecial = "assets/models/objeto.obj";
        int tipoEnemigo;//Tipo del enemigo: pollo, murcielago, guardian, boss
        Arbol *arbol;//este arbol es la ia para hacerlo funcionar debes llamar a runIA() desde nivel, cuidado porque si es nullptr puede dar errores.
        int pos_ataques; //para controlar el array de ataques en colisiones
        bool accionRealizada; //
        VectorEspacial vectorOrientacion; //Vector que sirve para orientar al enemigo
};

#endif
