#include "Jugador.hpp"
#include <stdlib.h>
#include "../Times.hpp"
#include "../ConstantesComunes.hpp"
#include "../Motores/MotorFisicas.hpp"

#define NOMBREHEAVY "Heavy"
#define NOMBREBAILAORA "Bailaora"

Jugador::Jugador()
{
    _motor = MotorGrafico::GetInstance();
    _motora = MotorAudioSystem::getInstance();
    _interfaz = InterfazJugador::getInstance();

    animacion = 0;
    //tiempos de animacion
    tiempoAtaque=2000.0f;//tiempo en milisegundos
    tiempoPasadoAtaque=0;
    tiempoAtaEsp=2000.0f;//tiempo en milisegundos
    tiempoPasadoAtaEsp=0;
    tiempoCogerObjeto=2000.0f;//tiempo en milisegundos
    tiempoPasadoCogerObjeto=0;
    tiempoEnMorir=2000.0f;//tiempo en milisegundos
    tiempoPasadoEnMorir=0;

    dinero = 0;
    _armaEquipada = NULL;
}

Jugador::Jugador(int nX,int nY,int nZ, int ancho, 
    int largo, int alto, int accion, int maxVida)
: Jugador()
{
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    _fisicas->crearCuerpo(accion,0,nX/2,nY/2,nZ/2,3,2,2,2,1);//creamos el cuerpo y su espacio de colisiones en el mundo de las fisicas
    _fisicas = nullptr;
    
    this->ancho = ancho;
    this->largo = largo;
    this->alto = alto;

    vidaIni = maxVida;
    vida = vidaIni;

    posIni.x = nX;
    posIni.y = nY;
    posIni.z = nZ;

    posActual.x = nX;
    posActual.y = nY;
    posActual.z = nZ;
}

Jugador::~Jugador()
{
    _motor = nullptr;
    _motora = nullptr;
    _interfaz = nullptr;
    
    _armaEquipada = nullptr;
    _armaEspecial = nullptr;

    _rutaArmaEspecial = nullptr;
    _nombreJugador = nullptr;

    // INnpc e INdrawable
    // Nada
}

void Jugador::movimiento(bool noMueve,bool a, bool s, bool d, bool w)
{
    Constantes constantes;
    float px = posFutura.x,
          pz = posFutura.z;

    if(w || s || a || d)
    {
        setAnimacion(1);
    }
    else
    {
        setAnimacion(0);//no se mueve
    }

    // Comprobar teclas para mover el personaje y la camara
    if(w)
    {
        //ax y az son las componentes del vector director (x,z), para calcular el angulo posteriormente.
        az = 50; //cuando mas alto mejor es el efecto de giro
    }
    if(s)
    {
        az = -50;
    }
    if(a)
    {
        ax = -50;

    }
    if(d)
    {
        ax = 50;
    }

    //Para giro: obtienes el maximo comun divisor y lo divides entre x, z
    //asi tambien evitas que ambas variables aumenten excesivamente de valor
        float div = (float)__gcd((int)abs(ax),(int)abs(az));

        if(div != 1.0 && div != 0.0)
        {
            ax /= div;
            az /= div;
        }

    //cout << "ax: " << ax << ", az: " << az << endl;

    //esto es para que gire hacia atras ya que al valor que devuelve atan hay que darle la vuelta 180
    az < 0 ?
        deg = constantes.PI_RADIAN + (constantes.RAD_TO_DEG * atan(ax/az)) :
        deg =  constantes.RAD_TO_DEG * atan(ax/az) ;

    float componente;
    if((w || s || a || d) && !noMueve)
    {
        componente = 1.5;
    }
    else
    {
        componente = 0.0;
    }
    px += componente*sin(deg*constantes.DEG_TO_RAD);
    pz += componente*cos(deg*constantes.DEG_TO_RAD);

    //cout << "deg: " << deg << ", px:" << px << ", pz:" << pz << endl;
    //ahora actualizas movimiento y rotacion
    //has obtenido la arcotangente que te da el angulo de giro en grados
    /*x = px;
    z = pz;*/
    setNewPosiciones(px, posActual.y, pz);
    setNewRotacion(rotActual.x, deg, rotActual.z);
}

/*************** moverseEntidad *****************
 * Funcion con la que el jugador se desplazaran
 * por el escenario mediante una interpolacion desde
 * el punto de origen al punto de destino
 */
void Jugador::moverseEntidad(float updTime)
{
    //pt es el porcentaje de tiempo pasado desde la posicion
    //de update antigua hasta la nueva
    float pt = moveTime / updTime;

    if(pt > 1.0f)
    {
        pt = 1.0f;
    }

    posActual.x = posPasada.x * (1 - pt) + posFutura.x * pt;
    posActual.z = posPasada.z * (1 - pt) + posFutura.z * pt;
}

/*************** rotarEntidad *****************
 * Funcion con la que el jugador rotara
 * sobre si mismo mediante una interpolacion desde
 * el punto de origen al punto de destino
 */
void Jugador::RotarEntidad(float updTime)
{
    //pt es el porcentaje de tiempo pasado desde la posicion
    //de update antigua hasta la nueva
    float pt = moveTime / updTime;

    if(pt > 1.0f)
    {
        pt = 1.0f;
    }

    rotActual.x = rotPasada.x * (1 - pt) + rotFutura.x * pt;
    rotActual.y = rotPasada.y * (1 - pt) + rotFutura.y * pt;
    rotActual.z = rotPasada.z * (1 - pt) + rotFutura.z * pt;
}

void Jugador::UpdateTimeMove(float updTime)
{
    moveTime += updTime;
}

// Se llama en update de jugando
bool Jugador::EstaMuerto()
{
    if(vida <= 0)
    {
        //setAnimacion(5);
        return true;
    }
    return false;
}

bool Jugador::finalAnimMuerte()
{
    Times* _tiempo = Times::GetInstance();
    if(_tiempo->CalcularTiempoPasado(tiempoPasadoMuerte) >= animacionMuerteTiem && tiempoPasadoMuerte != 0){//sino se cumple no ha acabado
        return true;
    }
    return false;
}

void Jugador::MuereJugador()
{
    Times* _tiempo = Times::GetInstance();

    if(tiempoPasadoMuerte == 0){
        //_motor->colorearJugador(255,0,0,0);//negro
        tiempoPasadoMuerte = _tiempo->GetTiempo(1);
    }
    if(_tiempo->CalcularTiempoPasado(tiempoPasadoMuerte) < animacionMuerteTiem){
        if(_tiempo->CalcularTiempoPasado(tiempoPasadoMuerte) >= 1000.0f){
            //_motor->colorearJugador(255,255,0,0);//rojo
        }
    }
}

int Jugador::Atacar(int i)
{
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    Constantes constantes;
    int danyo = 0;
    if(vida > 0)
    {
        //Calcular posiciones que no se modifican
        int distance = 5;
        if(this->getArma() == nullptr)distance= 3;
        atx = distance * sin(constantes.PI * getRY() / constantes.PI_RADIAN) + getX();
        aty = getY();
        atz = distance * cos(constantes.PI * getRY() / constantes.PI_RADIAN) + getZ();
        atgx = getRX();
        atgy = getRY();
        atgz = getRZ();

        //Posiciones en el mundo 3D
        atposX = (atx/2);
        atposY = (getY()/2);
        atposZ = (atz/2);

        //ATAQUE SIN ARMA
        if(this->getArma() == nullptr)
        {
            setAnimacion(2);
            _fisicas->crearCuerpo(0,0,atposX,atposY,atposZ,2,2,2,1,4);
            danyo = 50.0f;
            _motora->getEvent("SinArma")->setVolume(0.8f);
            _motora->getEvent("SinArma")->start();
        }
        //ATAQUE CUERPO A CUERPO
        else if(strcmp(this->getArma()->getNombre(),"guitarra") == 0)
        {
            //Crear cuerpo de colision de ataque delante del jugador
            _fisicas->crearCuerpo(0,0,atposX,atposY,atposZ,1,5,0,0,4);
            danyo = 70.0f;
            _motora->getEvent("GolpeGuitarra")->setVolume(0.8f);
            _motora->getEvent("GolpeGuitarra")->start();
        }
        //ATAQUE A DISTANCIA
        else if(strcmp(this->getArma()->getNombre(),"arpa") == 0)
        {
            //Crear cuerpo de colision de ataque delante del jugador
            _fisicas->crearCuerpo(0,0,atposX,atposY,atposZ,2,2,0.5,1,4);
            danyo = 55.0f;
            _motora->getEvent("Arpa")->setVolume(0.8f);
            _motora->getEvent("Arpa")->start();
        }
        atacados_normal.clear(); //Reiniciar vector con enemigos atacados
    }
    else {
        cout << "No supera las restricciones"<<endl;
    }
    return danyo;
}

void Jugador::AtacarUpdate(int danyo, std::vector<Enemigo*> &_getEnemigos)
{
    Constantes constantes;
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    if(vida > 0)
    {
        if(this->getArma() == nullptr) {
            _fisicas->updateAtaque(atposX,atposY,atposZ,atgx,atgy,atgz);
            _motor->dibujarObjetoTemporal(atx,aty,atz,atgx,atgy,atgz,2,1,1,2);
        }
        else if(strcmp(this->getArma()->getNombre(),"guitarra") == 0)
        {
            _fisicas->updateAtaque(atposX,atposY,atposZ,atgx,atgy,atgz);
            _motor->dibujarObjetoTemporal(atx,aty,atz,atgx,atgy,atgz,3,1,3,1);
        }
        else if(strcmp(this->getArma()->getNombre(),"arpa") == 0)
        {
            int distance = 1.5;
            atz += (distance * cos(constantes.PI * atgy / constantes.PI_RADIAN));
            atx += (distance * sin(constantes.PI * atgy / constantes.PI_RADIAN));
            atposZ += (distance * cos(constantes.PI * atgy / constantes.PI_RADIAN));
            atposX += (distance * sin(constantes.PI * atgy / constantes.PI_RADIAN));

            _fisicas->updateAtaque(atposX,atposY,atposZ,atgx,atgy,atgz);
            _motor->dibujarObjetoTemporal(atx,aty,atz,atgx,atgy,atgz,1,1,2,3);
        }

        //Enteros con los enemigos colisionados (atacados)
        vector <unsigned int> atacados = _fisicas->updateArma(atposX,atposY,atposZ);

        if(!atacados.empty())
        {
            //Pasar por cada uno de los atacados
            for(unsigned int i = 0; i < atacados.size(); i++)
            {
                //Buscar si esta en el vector guardado
                bool encontrado = false;
                long unsigned int j = 0;
                if(!atacados_normal.empty())
                {
                    while(j < atacados_normal.size())
                    {
                        if(atacados.at(i) == atacados_normal.at(j))
                        {
                        encontrado = true; //Ya se le ha atacado antes
                        break;
                        }
                        j++;
                    }
                }
                //Si no se ha encontrado es que no se le a atacado
                if (encontrado == false)
                {
                    float variacion = rand() % 7 - 3;
                    danyo += (int) variacion;
                    //CUANDO LE QUITAN VIDA BUSCA AL JUGADOR PARA ATACARLE
                    _getEnemigos.at(atacados.at(i))->ModificarVida(-danyo);
                    cout<<"Enemigo: "<< _getEnemigos.at(atacados.at(i))->getID() << endl;
                    cout<<"Daño "<<danyo<<endl;
                    danyo -= (int) variacion;
                    cout<<"variacion "<<variacion<<endl;
                    cout<<"Vida enemigo "<<_getEnemigos.at(atacados.at(i))->getID()<<" "<<_getEnemigos.at(atacados.at(i))->getVida()<<endl;
                    _motor->colorearEnemigo(255, 0, 255, 55, atacados.at(i));
                    //guardar el atacado para no repetir
                    atacados_normal.push_back(atacados.at(i));
                }
            }
        }
    }
    else
    {
        cout << "No supera las restricciones"<<endl;
    }
}

/*************** AtacarEspecial *****************
 *  Funcion que inicia la ejecucion del ataque
 *  especial del jugador si la barra de ataque
 *  especial esta completa y se pulsa el boton Q /
 *  click derecho del raton.
 *      Entradas:
 *      Salidas: int danyo;
 */
int Jugador::AtacarEspecial()
{
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    Constantes constantes;
    float danyoF = 0.f, aumentosAtaque = 0.f, critico = 1.f, por1 = 1.f;
    int danyo = 0, por10 = 10, por100 = 100;

    cout << vida << " " << barraAtEs << " " << por100 << endl;
    //Se comprueban las restricciones (de momento solo que esta vivo y la barra de ataque especial)
    if(vida > 0 && barraAtEs == por100)
    {
        //Calcular posiciones si se inicia el ataque especial
        setAnimacion(3);
        if(atackEspTime <= 0)
        {
            int distancia = 5;
            animacion = 3;
            atespx = distancia * sin(constantes.PI * getRY() / constantes.PI_RADIAN) + getX();
            atespy = getY();
            atespz = distancia * cos(constantes.PI * getRY() / constantes.PI_RADIAN) + getZ();
            atgx = getRX();
            atgy = getRY();
            atgz = getRZ();
            incrAtDisCirc = 0.0;

            _armaEspecial->setNewPosiciones(atespx, atespy, atespz);
            _armaEspecial->setNewRotacion(getRX(), getRY(), getRZ());

            //Posiciones en el mundo 3D
            _armaEspecial->initPosicionesFisicas(atespx/2, getY()/2, atespz/2);

            //ATAQUE ESPECIAL DEL HEAVY
            if(strcmp(_armaEspecial->getNombre(), NOMBREHEAVY) == 0)
            {
                //Crear cuerpo de colision de ataque delante del jugador
                _fisicas->crearCuerpo(0,0,_armaEspecial->getFisX(),_armaEspecial->getFisY(),_armaEspecial->getFisZ(),2,8,1,8,5);
                _motora->getEvent("Arpa")->setVolume(0.8f);
                _motora->getEvent("Arpa")->start();
            }
            //ATAQUE ESPECIAL DE LA BAILAORA
            else if(strcmp(_armaEspecial->getNombre(), NOMBREBAILAORA) == 0)
            {
                //Crear cuerpo de colision de ataque delante del jugador
                _fisicas->crearCuerpo(0,0,_armaEspecial->getFisX(),_armaEspecial->getFisY(),_armaEspecial->getFisZ(),2,8,8,8,5);
                _motora->getEvent("Arpa")->start();
            }
        }

        //Se calcula el danyo del ataque
        aumentosAtaque += por1;
        if(_armaEquipada != NULL)
        {
            aumentosAtaque += (float) _armaEquipada->getAtaque() / por100;// + (float) variacion / 100;
        }
        aumentosAtaque *= 2;
        aumentosAtaque = roundf(aumentosAtaque * por10) / por10;

        //Se lanza un random y si esta dentro de la probabilidad de critico lanza un critico
        int probabilidad = rand() % por100 + 1;
        if(probabilidad <= proAtaCritico)
        {
            critico += (float) danyoCritico / por100;
            critico = roundf(critico * por10) / por10;
        }

        //Se aplican todas las modificaciones en la variable danyo
        danyoF = ataque * critico * aumentosAtaque;
        danyo = roundf(danyoF * por10) / por10;
        setBarraAtEs(0);
        return danyo;
    }
    return danyo;
}
/*************** AtacarEspecialUpdate *****************
 *  Funcion que actualiza la posicion y
 *  la colision del ataque especial
 *      Entradas: int danyo
 *      Salidas:
 */
void Jugador::AtacarEspecialUpdate(int* danyo, std::vector<Enemigo*> &_getEnemigos)
{
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    Constantes constantes;
    
    //Si el ataque especial es el del Heavy, es cuerpo a cuerpo
    if(strcmp(_armaEspecial->getNombre(), NOMBREHEAVY) == 0)
    {
        int distancia = 5;
        //Calculo de la posicion del arma delante  int getAnimacion();del jugador
        atespx = distancia * sin(constantes.PI * this->getRY() / constantes.PI_RADIAN) + this->getX();
        atespz = distancia * cos(constantes.PI * this->getRY() / constantes.PI_RADIAN) + this->getZ();
        _armaEspecial->initPosicionesFisicas(atespx/2, this->getY()/2, atespz/2);
        _armaEspecial->setNewPosiciones(atespx, this->getY(), atespz);
        _armaEspecial->setNewRotacion(getRX(), this->getRY(), getRZ());
    }

    //Si el ataque especial es el de la Bailaora, es circular a distancia
    else if(strcmp(_armaEspecial->getNombre(), NOMBREBAILAORA) == 0)
    {
        //Formula de ataque circular aumentando la distancia
        incrAtDisCirc += 1.5;
        atespz = this->getZ();
        atespz += (incrAtDisCirc * cos(constantes.PI * atgy / constantes.PI_RADIAN));
        atespx = this->getX();
        atespx += (incrAtDisCirc * sin(constantes.PI * atgy / constantes.PI_RADIAN));
        atespposZ = atespz - this->getZ();
        atespposX = atespx - this->getX();
        _armaEspecial->setPosicionesFisicas(atespposZ, 0.0f, atespposZ);

        //Aumento de la rotacion hacia la izquierda.
        atgy += 30;

        if(atgy >= 360.0)
        {
            atgy -= 360.0;
        }
        else if(atgy < 0.0)
        {
            atgy += 360;
        }

        _armaEspecial->setNewPosiciones(atespx, this->getY(), atespz);
        _armaEspecial->setNewRotacion(getRX(), atgy, getRZ());
    }
    //lista de enteros que senyalan a los enemigos atacados
    vector <unsigned int> atacados = _fisicas->updateArmaEspecial(_armaEspecial->getFisX(),_armaEspecial->getFisY(),_armaEspecial->getFisZ());

    //Si hay colisiones se danya a los enemigos colisionados anyadiendole una variacion al danyo
    //y se colorean los enemigos danyados (actualmente todos al ser instancias de una malla) de color verde
    if(!atacados.empty() && *danyo > 0)
    {
        cout<<"Funciona"<<endl;
        for(unsigned int i = 0; i < atacados.size(); i++)
        {
            float variacion = rand() % 7 - 3;
            *danyo += (int) variacion;
            _getEnemigos.at(atacados.at(i))->ModificarVida(-(*danyo));
            cout<<"Daño "<<*danyo<<endl;
            *danyo -= (int) variacion;
            cout<<"variacion "<<variacion<<endl;
            cout<<"Vida enemigo "<<_getEnemigos.at(atacados.at(i))->getID()<<" "<<_getEnemigos.at(atacados.at(i))->getVida()<<endl;
            _motor->colorearEnemigo(255, 0, 255, 55, atacados.at(i));
        }
    }
}

void Jugador::generarSonido(int intensidad,double duracion,int tipo)
{
    Constantes constantes;
    EventoSonido * sonid = new EventoSonido(intensidad, duracion, posActual.x, posActual.y, posActual.z, constantes.DOS, tipo);
    SenseEventos * eventos = SenseEventos::getInstance();
    eventos->agregarEvento(sonid);
}

void Jugador::queEscuchas()
{
    SenseEventos * eventos = SenseEventos::getInstance();
    std::vector<EventoSonido *> listaSonidos =  eventos->listarSonidos(posActual.x, posActual.y);//le pasamos nuestra x e y
    //int cuantos = listaSonidos.size();
    //cout << "Esta escuchando " << cuantos << " sonidos" << endl;
}

void Jugador::queVes()
{
    /*codigo*/
}

void Jugador::Interactuar(int id, int id2)
{

}

/***********AnnadirLlave************
 * Metodo que anade la llave pasada por
 * parametro al vector de llaves que
 * posee el jugador
 * Entradas:
 *          Llave* llave: llave a anadir
 */
void Jugador::AnnadirLlave(Llave* llave)
{
    llaves.push_back(llave);
    cout<<"Llave añadida. Nº de llaves: "<<llaves.size()<<endl;
}

/***********EliminarLlave************
 * Metodo que elimina la llave pasada por
 * parametro del vector de llaves que
 * posee el jugador
 * Entradas:
 *          Llave* llave: llave a eliminar
 */
void Jugador::EliminarLlave(Llave* llave)
{
    unsigned int i = 0;
    bool encontrado = false;
    while(!encontrado)
    {
        i++;
        //Se elimina la llave si coinide con el codigo de la puerta de la llave pasada por parametro
        if(llave->GetCodigoPuerta() == llaves.at(i)->GetCodigoPuerta())
        {
            llaves.erase(llaves.begin() + i);
            encontrado = true;
        }
    }
}

bool Jugador::terminaAnimacion()
{
        Times* _tiempo = Times::GetInstance();

        switch(animacion)//comprobamos que la animacion haya terminado
        {
            case 0://andar
                return true;
            case 1://quieto
                return true;
            case 2://ataque
                if(_tiempo->CalcularTiempoPasado(tiempoPasadoAtaque) >= tiempoAtaque || tiempoPasadoAtaque == 0)
                {
                    tiempoPasadoAtaque = 0;
                    return true;
                }
                else
                {
                    return false;
                }
            case 3://ataque especial
                if(_tiempo->CalcularTiempoPasado(tiempoPasadoAtaEsp) >=  tiempoAtaEsp || tiempoPasadoAtaEsp == 0)
                {
                    tiempoPasadoAtaEsp = 0;
                    return true;
                }
                else
                {
                    return false;
                }
            case 4://coger objeto
                if(_tiempo->CalcularTiempoPasado(tiempoPasadoCogerObjeto) >= tiempoCogerObjeto || tiempoPasadoCogerObjeto == 0)
                {
                    tiempoPasadoCogerObjeto = 0;
                    return true;
                }
                else
                {
                    return false;
                }
            case 5://muerto
                return false;
        }
    return true;
}

float Jugador::getX()
{
    return posActual.x;
}

float Jugador::getY()
{
    return posActual.y;
}

float Jugador::getZ()
{
    return posActual.z;
}

float Jugador::getNewX()
{
    return posFutura.x;
}

float Jugador::getNewY()
{
    return posFutura.y;
}

float Jugador::getNewZ()
{
    return posFutura.z;
}

float Jugador::getLastX()
{
    return posPasada.x;
}

float Jugador::getLastY()
{
    return posPasada.y;
}

float Jugador::getLastZ()
{
    return posPasada.z;
}

float Jugador::getIniX()
{
    return posIni.x;
}

float Jugador::getIniY()
{
    return posIni.y;
}

float Jugador::getIniZ()
{
    return posIni.z;
}

float Jugador::getFisX()
{
    return posFisicas.x;
}

float Jugador::getFisY()
{
    return posFisicas.y;
}

float Jugador::getFisZ()
{
    return posFisicas.z;
}

float Jugador::getRX()
{
    return rotActual.x;
}

float Jugador::getRY()
{
    return rotActual.y;
}

float Jugador::getRZ()
{
    return rotActual.z;
}

//Devuelve la posicion y rotacion del ataque especial
float* Jugador::GetDatosAtEsp()
{
    float* atesp = new float [6];
    atesp[0] = _armaEspecial->getX();
    atesp[1] = _armaEspecial->getY();
    atesp[2] = _armaEspecial->getZ();
    atesp[3] = _armaEspecial->getRX();
    atesp[4] = _armaEspecial->getRY();
    atesp[5] = _armaEspecial->getRZ();

    return atesp;
}

int Jugador::getVidaIni()
{
    return vidaIni;
}

int Jugador::getVida()
{
    return vida;
}

int Jugador::getTipo()
{
    return -1;
}

// TO DO: revisar la parte del else
int Jugador::getBarraAtEs()
{
    if(barraAtEs >= 0 && barraAtEs <= 100)
    {
        return barraAtEs;
    }
    else
    {
        if(barraAtEs < 0)
            return 0;
        if(barraAtEs > 100)
            return 100;
    }

    return 1;
}

int Jugador::getAtaque()
{
    return -1;
}

Arma* Jugador::getArma()
{
    return _armaEquipada;
}


Arma* Jugador::getArmaEspecial()
{
    return _armaEspecial;
}

const char* Jugador::getNombre()
{
    return _nombreJugador;
}

int Jugador::getSuerte()
{
    return -1;
}

int Jugador::getDanyoCritico()
{
    return danyoCritico;
}

int Jugador::getProAtaCritico()
{
    return proAtaCritico;
}

int* Jugador::getBuffos()
{
    int* valores = new int[6];
    return valores;
}

float Jugador::getTimeAt()
{
    return atackTime;
}

float Jugador::getLastTimeAt()
{
    return lastAtackTime;
}

float Jugador::getTimeAtEsp()
{
    return atackEspTime;
}

float Jugador::getLastTimeAtEsp()
{
    return lastAtackEspTime;
}

const char*Jugador::getRutaArmaEsp()
{
    return _rutaArmaEspecial;
}

int Jugador::getDinero()
{
    return dinero;
}

/******----------------Modificar Dinero------------------******
 * Metodo que sirve para modificar la cantidad de monedas
 * que tiene el jugador a lo largo del juego
 * Entradas:
 *      monedas: valor negativo o positivo en el que se 
 *          incrementa o decrementa el dinero
 * Salida:
 * 
 */
void Jugador::ModificarDinero(int monedas)
{
    dinero += monedas;
    if(dinero > 9999)
        dinero = 9999;
    else if (dinero < 0) 
        dinero = 0;
    _interfaz->setDinero(dinero);
}

void Jugador::setDinero(int monedas)
{
    dinero = monedas;
    _interfaz->setDinero(dinero);
}

int Jugador::getAnimacion()
{
    return animacion;
}

std::vector <Llave*> Jugador::GetLlaves()
{
    return llaves;
}

int Jugador::getID()
{
    return id;
}


void Jugador::setPosiciones(float nx,float ny,float nz)
{
    posActual.x = nx;
    posActual.y = ny;
    posActual.z = nz;
}


void Jugador::setLastPosiciones(float nx,float ny,float nz)
{
    posPasada.x = nx;
    posPasada.y = ny;
    posPasada.z = nz;
}

void Jugador::setRotacion(float nrx, float nry, float nrz)
{
    rotActual.x = nrx;
    rotActual.y = nry;
    rotActual.z = nrz;
}

void Jugador::setNewRotacion(float nrx, float nry, float nrz)
{
    rotateTime = 0.0;
    this->setLastRotacion( rotFutura.x,  rotFutura.y, rotFutura.z);
    rotFutura.x = nrx;
    rotFutura.y = nry;
    rotFutura.z = nrz;
}

void Jugador::setLastRotacion(float nrx, float nry, float nrz)
{
    rotPasada.x = nrx;
    rotPasada.y = nry;
    rotPasada.z = nrz;
}

void Jugador::setNewPosiciones(float nx,float ny,float nz)
{
    moveTime = 0.0;
    this->setLastPosiciones(posFutura.x, posFutura.y, posFutura.z);
    posFutura.x = nx;
    posFutura.y = ny;
    posFutura.z = nz;
}

void Jugador::initPosicionesFisicas(float nx,float ny,float nz)
{
    posFisicas.x = nx;
    posFisicas.y = ny;
    posFisicas.z = nz;
}

void Jugador::setPosicionesFisicas(float nx,float ny,float nz)
{
    posFisicas.x += nx;
    posFisicas.y += ny;
    posFisicas.z += nz;
}

/******----------------Modificar Vida------------------******
 * Metodo que sirve para modificar la vida del jugador
 * a lo largo del juego.
 * Entradas:
 *      vid: valor negativo o positivo en el que se 
 *          incrementa o decrementa la vida
 * Salida:
 * 
 */
void Jugador::ModificarVida(int vid)
{
    if (vid < 0) // QuitarVida, aumenta barra ataque especial
    {
        ModificarBarraAtEs(abs(vid));
    }

    vida += vid;
    if (vida > vidaIni)
        vida = vidaIni;
    else if (vida < 0)
        vida = 0;
    _interfaz->setVida(vida);
}

// Asigna directamente el valor
void Jugador::setVida(int vid)
{
    vida = vid;
    _interfaz->setVida(vida);
}

void Jugador::setTipo(int tip)
{

}

/*************** Modificar BarraAtEs *****************
 *  Funcion que actualiza la barra del ataque especial
 *  Entradas: 
 *      bar: valor en positivo o negativo
 *  Salidas:
 * 
 */
void Jugador::ModificarBarraAtEs(int bar)
{
    barraAtEs += bar;
    if(barraAtEs < 0)
        barraAtEs = 0;
    if(barraAtEs > 100)
        barraAtEs = 100;
    _interfaz->setAtaqueEspecial(barraAtEs);
}

void Jugador::setBarraAtEs(int bar)
{
    barraAtEs = bar;
    _interfaz->setAtaqueEspecial(barraAtEs);
}

void Jugador::setAtaque(int ataq)
{
    ataque = ataq;
}

void Jugador::setArma(Arma* arma)
{
    _armaEquipada = arma;

    if(_armaEquipada)
    {
        if(strcmp(this->getArma()->getNombre(),"guitarra") == 0)//entonces es la guitarra cuerpo a cuerpo
        {
            _interfaz->setArma(2);
        }

        if(strcmp(this->getArma()->getNombre(),"arpa") == 0)//entonces es la guitarra cuerpo a cuerpo
        {
            _interfaz->setArma(3);
        }

        if(strcmp(this->getArma()->getNombre(),"llave") == 0)//entonces es la guitarra cuerpo a cuerpo
        {
            _interfaz->setArma(1);
        }

        // if(strcmp(this->getArma()->getNombre(),"dinero") == 0)//entonces es la guitarra cuerpo a cuerpo
        // {
        //     dinero = dinero+1;
        //     _interfaz->setArma(0);
        // }
    }
    else
    {
        _interfaz->setArma(0);
    }
}


void Jugador::setArmaEspecial(int ataque)
{
    _armaEspecial = new Arma(ataque, _nombreJugador,3,3,3,_rutaArmaEspecial,"");
}

void Jugador::setNombre(const char* nombre)
{
    _nombreJugador = nombre;
}

void Jugador::setSuerte(int suer)
{

}

void Jugador::setDanyoCritico(int danyoC)
{
    danyoCritico = danyoC;
}

void Jugador::setProAtaCritico(int probabilidad)
{
    proAtaCritico = probabilidad;
}

void Jugador::setTimeAt(float time)
{
    atackTime = time;
}

void Jugador::setLastTimeAt(float time)
{
    lastAtackTime = time;
}


void Jugador::setTimeAtEsp(float time)
{
    atackEspTime = time;
}

void Jugador::setLastTimeAtEsp(float time)
{
    lastAtackEspTime = time;
}


void Jugador::setAnimacion(int est)
{
    Times* _tiempo = Times::GetInstance();

    if(est != animacion)
    {
        //es una nueva animacion
        if(terminaAnimacion())
        {
            animacion = est; //cambiamos la animacion
            switch(animacion)
            {
                case 2:
                    tiempoPasadoAtaque = _tiempo->GetTiempo(1);
                break;
                case 3:
                    tiempoPasadoAtaEsp = _tiempo->GetTiempo(1);
                break;
                case 4:
                    tiempoPasadoCogerObjeto = _tiempo->GetTiempo(1);
                break;
            }
        }
    }
    else
    {
        //es la misma comprobamos si ha terminado si lo a echo nos ponemos en modo reposo o corriendo
        if(terminaAnimacion() && animacion != 0 && animacion != 1)
        {
            animacion = 0;//pasamos a modo reposo si no esta corriendo o en modo reposo
        }
    }
}

void Jugador::setID(int nid)
{
    id = nid;
}

const char* Jugador::GetTextura()
{
    return playerTextura;
}

const char* Jugador::GetModelo()
{
    return playerModelo;
}

int Jugador::GetAncho()
{
    return ancho;
}
int Jugador::GetLargo()
{
    return largo;
}
int Jugador::GetAlto()
{
    return alto;
}