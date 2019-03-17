#ifndef Enemigo_HPP
#define Enemigo_HPP
#include "../Motores/INnpc.hpp"
#include "../Motores/INdrawable.hpp"
#include "../Motores/INsentidos.hpp"
#include "../Armas/Arma.hpp"
#include "../Jugando/Sala.hpp"
#include "../Jugando/Zona.hpp"
#include <vector>
#include "../Arbol.hpp"

#include "../Times.hpp"
#include "../Motores/MotorAudio.hpp"
#include "../Motores/MotorGrafico.hpp"
#include "../Motores/SenseEventos.hpp"

class Enemigo : public INnpc , public INdrawable, public INsentidos //multiple herencia a esto se le llama derivacion multiple
{

    public:
        Enemigo();
        Enemigo(float nX, float nY, float nZ, int maxVida);
        ~Enemigo();

        void definirSala(Sala* sala);

        //sentidos metodos
        void generarSonido(int intensidad,double duracion,int tipo);//la intensidad es el alcance y la duracion es cuanto dura el sonido, el tipo 1 son sonidos del jugador, 2 es pedir ayuda de los enemigos

        void queEscuchas();//recupera la informacion de los sonidos que escucha

        void queVes();//recupera informacion de los objetos,enemigos,jugador que ve.
        //drawables metodos

        //npc metodos
        int Atacar(int i);//efectua un ataque normal, llama al motor para ejecutar la animacion.
        //void AtacarEspecial();//efectua el ataque especial segun el tipo, esto llama a motor grafico para realizar la animacion, cuando se termina se pone a cero la barra
        int AtacarEspecial();//efectua el ataque especial segun el tipo, esto llama a motor grafico para realizar la animacion, cuando se termina se pone a cero la barra
        bool estasMuerto();//llama desde Nivel
        bool finalAnimMuerte();// si la animacion de muerte acaba, entonces en nivel lo mataremos del todo
        void MuereEnemigo(int enemi);//Animacion de muertes
        void Interactuar(int, int);//llama a la mecanica de interactuar
        void moverseEntidad(float);//Realiza el desplazamiento mediante la interpolacion
        void RotarEntidad(float);//Realiza la rotacion mediante la interpolacion
        void UpdateTimeMove(float);//actualiza el tiempo del movimiento de la interpolacion
        void UpdateTimeRotate(float);
        
        //getters y setters

        void setID(int);
        void setPosiciones(float nx,float ny,float nz);
        void setPosicionesAtaque(float nx,float ny,float nz);
        void setNewPosiciones(float nx,float ny,float nz);
        void setLastPosiciones(float nx,float ny,float nz);
        void setRotacion(float nrx, float nry, float nrz);
        void setNewRotacion(float nrx, float nry, float nrz);
        void setLastRotacion(float nrx, float nry, float nrz);
        void setRotation(float rot);
        void setVectorOrientacion();
        void setPosicionesFisicas(float nx,float ny,float nz);

        void initPosicionesFisicasAtaque(float nx,float ny,float nz);
        void initPosicionesFisicas(float nx,float ny,float nz);

        void ModificarVida(int vid);
        void setVida(int vid);
        void setTipo(int tip);
        void ModificarBarraAtEs(int bar);
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
        void setPosAtaques(int p);
        void setVelocidadMaxima(float velocidad); //modifica la VelocidadMaxima de desplazamiento
        void SetEnemigo(int);
        void SetModo(int);

        int getID();
        int getVidaIni();
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
        float getIniX();
        float getIniY();
        float getIniZ();
        float getFisX();
        float getFisY();
        float getFisZ();
        float getRX();
        float getRY();
        float getRZ();
        float GetRotation();
        float getAtX();
        float getAtY();
        float getAtZ();
        float getVelocidadMaxima(); //se obtiene la VelocidadMaxima de desplazamiento
        int GetEnemigo();
        int GetModo();

        bool ver(int tipo);//1 si ve al jugador

        //ia
        float randomBinomial();//devuelve un valor random entre -1 y 1
        void setArbol(Arbol);//asigna un arbol de ia al enemigo
        Arbol* getArbol();//devuelve el puntero al arbol de ia que tiene, CUIDADO si no tiene arbol devuelve nullptr
        void UpdateIA(); //funcion que llama desde nivel a la IA del enemigo que sea que activara la lectura del arbol segun sea un pollo, un murcielago... etc
        void UpdateBehavior(short *i, int* _jugador, std::vector<Zona*> &_getZonas, bool ayuda); //actualiza el comportamiento actual del pollo
        short * RunIA(bool);//corre la ia del enemigo
        void ForzarCambioNodo(const short *nodo);//Modifica el nodo actual en el que se encuentra la IA
        void AnnadirRecorridoAyuda(vector <Posiciones> recorrido);
        //fin ia

        const char* GetModelo(); // Malla 3D con la textura
        bool GetPedirAyuda();
        void SetPedirAyuda(bool);
        bool GetContestar();
        void SetContestar(bool);

        void Render(short pos, float updTime, float drawTime);
        void RenderAtaque();

    protected:
        Times* _tiempo;
        MotorAudioSystem* _motora;
        MotorGrafico* _motor;
        SenseEventos* _eventos;
        short int maxRotacion;

        //comportamientos bases
        void alinearse(VectorEspacial*, bool huir);
        bool oir(int tipo);//1 si se oye jugador, 2 si se oye enemigo(pedir ayuda)
        bool buscar();//por defecto devuelve true
        bool perseguir(int* _jug);//por defecto devuelve true TO IMPROVE
        bool buscar(VectorEspacial*);//busca un objetivo
        bool Acciones(int);//esto es para recorrer el arbol
        bool PedirAyuda(bool);//pide ayuda
        bool ContestarAyuda();//esto es de prueba no hace dayo tampoco
        void AuxiliarAliado();//se mueve hacia el proximo waypoint del camino a seguir
        bool Merodear();//para dar vueltas por una zona, segun entero que reciba ira en una direccion
        INnpc::VectorEspacial normalizarVector(int*);//Convierte el vector que se pasa en un vector con la misma direccion y sentido pero con modulo 1
        //fin comportamientos bases

        Zona* getZonaMasCercana(vector <Zona*> zonas, short enemigo);
        //Comparadores de la lectura de las acciones y objetivos de las tareas
        enum accionesEnemigo 
        {  
            EN_PERSIGUE = 0,
            EN_ATACAR,
            EN_VER,
            EN_PIDE_AYUDA,
            EN_MERODEA,
            EN_OIR,
            EN_BUSCA,
            EN_RECUPERA,
            EN_ACUDE_AYUDA
        };

        enum objetivosEnemigo
        {
            EN_JUGADOR = 0,
            EN_ZONA_COFRES,
            EN_AYUDA
        };

        enum modosEnemigo 
        {  
            MODO_DEFAULT = 0,
            MODO_ATAQUE,
            MODO_HUIDA,
            MODO_AUXILIAR_ALIADO
        };

        Sala* _estoy;//sala en la que esta el enemigo
        float atx, atespx, aty, atespy, atz, atespz, atgx, atgy, atgz, incrAtDisCirc,iniAtposX, iniAtposY, iniAtposZ, atposX, atposY, atposZ, atespposX, atespposY, atespposZ;
        float atacktime;
        float tiempoMerodear, lastTiempoMerodear;
        Arma* _armaEspecial;
        const char* _rutaArmaEspecial = "assets/models/objeto.obj";
        int tipoEnemigo;//Tipo del enemigo: pollo, murcielago, guardian, boss
        Arbol* arbol;//este arbol es la ia para hacerlo funcionar debes llamar a runIA() desde nivel, cuidado porque si es nullptr puede dar errores.
        int pos_ataques; //para controlar el array de ataques en colisiones
        bool accionRealizada; //
        short modo;
        VectorEspacial vectorOrientacion; //Vector que sirve para orientar al enemigo
        vector <Posiciones> recorridoAyuda;
        int distanciaMinimaEsquivar; //Variable que contiene la distancia mínima para esquivar objetos;
        const char* _modelo; // Malla 3D con la textura
        bool pedirAyuda;
        bool contestar;
};

#endif
