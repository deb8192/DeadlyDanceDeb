#ifndef INnpc_HPP
#define INnpc_HPP
#include <iostream>

using namespace std;

//aqui definimos la clase interfaz de las entidades genericas (clases no virtuales)
class INnpc {

public:
    using VectorEspacial = struct Vector
    {
        float vX = 0.0f;
        float vY = 0.0f;
        float vZ = 0.0f;
        float modulo = 0.0f;
    };

    virtual ~INnpc() = default;
    
    virtual int Atacar(int)=0;//efectua un ataque normal, llama al motor para ejecutar la animacion.
    virtual int AtacarEspecial()=0;//efectua el ataque especial segun el tipo, esto llama a motor grafico para realizar la animacion, cuando se termina se pone a cero la barra
    virtual void Interactuar(int, int)=0;//llama a la mecanica de interactuar
    
    //set y gets

    virtual void ModificarVida(int vid)=0;//aumenta/disminuye vida a la entidad
    virtual void setVida(int vid)=0;
    virtual void setTipo(int tip)=0;
    virtual void ModificarBarraAtEs(int bar)=0;//aumenta/disminuye el valor de la barra de ataque critico
    virtual void setBarraAtEs(int bar)=0;
    virtual void setAtaque(int ataq)=0;
    virtual void setSuerte(int suer)=0;
    virtual void setTimeAt(float time)=0;
    virtual void setLastTimeAt(float time)=0;
    virtual void setTimeAtEsp(float time)=0;
    virtual void setLastTimeAtEsp(float time)=0;
    virtual void setDanyoCritico(int danyoC)=0;
    virtual void setProAtaCritico(int probabilidad)=0;
    virtual void setVectorOrientacion()=0;

    virtual int getVidaIni()=0;
    virtual int getVida()=0;
    virtual int getTipo()=0;
    virtual int getBarraAtEs()=0;
    virtual int getAtaque()=0;
    virtual int getSuerte()=0;
    virtual float getTimeAtEsp()=0;
    virtual float getLastTimeAtEsp()=0;
    virtual float getTimeAt()=0;
    virtual float getLastTimeAt()=0;
    virtual int getDanyoCritico()=0;
    virtual int getProAtaCritico()=0;
    virtual int* getBuffos()=0;
    virtual INnpc::VectorEspacial GetVectorOrientacion()=0;

/*el protected es para que tenga acceso sus descendientes o parientes*/
protected:
    VectorEspacial vectorOrientacion; //vector para indicar la velocidad vectorial del npc
    float velocidadMaxima; //Valor de la velocidad maxima del npc
    float porcentajeVelocidad;  //Porcentaje de la velocidad que usara para desplazarse (valores de 0 - 1)
    int tipo;//tipo de enemigo(mayor de cero) o jugador(0)
    int vidaIni;//maximo de vida que tiene la entidad
    int vida;//vida de la entida
    int barraAtEs;//barra que va de 0 a 100, cuando se 100 se puede ejecutar ataque especial.
    int ataque;//dano base que hace la entidad
    int suerte;//valor que determina la probabilidad de ataque critico y en el caso de jugador tambien de que suerte objetos
    int danyoCritico;//valor base del danyo anyadido a un golpe critico;
    int proAtaCritico;//valor que determina cuantas veces se hacen ataques criticos.
    int buffos[4];//1 aumento de vida, 2 aumento de ataque, 3 aumento de suerte, 4 aumento de pCritica.
    //Variables para el metodo morir
    float atackTime, atackEspTime;//Tiempo actual del ataque y del ataque especial
    float lastAtackTime, lastAtackEspTime;//Tiempo antiguo del ataque y del ataque especial
    float animacionMuerteTiem = 3000.0f;//tiempo de animacion del estado muerte para cualquier NPC
    float tiempoPasadoMuerte = 0;
    //tiempos animaciones
    float tiempoAtaque, tiempoPasadoAtaque, tiempoAtaEsp, tiempoPasadoAtaEsp,tiempoCogerObjeto,tiempoPasadoCogerObjeto,tiempoEnMorir,tiempoPasadoEnMorir;
};

#endif /* INnpc_HPP */
