#include "Enemigo.hpp"
#include "Pollo.hpp"
#include "Murcielago.hpp"
#include "TravornioBoss.hpp"
#include "MuerteBoss.hpp"
#include "Guardian.hpp"
#include "CofreArana.hpp"
#include "../ConstantesComunes.hpp"
#include "../Personajes/Jugador.hpp"
#include "cmath"
//#include "../Motores/MotorFisicas.hpp"

Enemigo::Enemigo()
{
    _tiempo = Times::GetInstance();
    _motora = MotorAudioSystem::getInstance();
    _motor = MotorGrafico::GetInstance();
    _fisicas = MotorFisicas::getInstance();
    _eventos = SenseEventos::getInstance();

    _animacion = nullptr;
    estadoMuerte = 0;//por defecto zero
    fps = 0;

    tiempoMerodear = 0.0f;
    tiempoMoverse = 0.0f;
    tiempoOcultarse = 0.0f;
    atackTime = 0.0f;
    atackEspTime = 0.0f;
    lastAtackTime = 0.0f;
    lastAtackEspTime = 0.0f;
    lastTiempoMerodear = 0.0f;
    lastTiempoMoverse = 0.0f;
    lastTiempoOcultarse = 0.0f;
    vectorOrientacion.vX = 0.0f;
    vectorOrientacion.vY = 0.0f;
    vectorOrientacion.vZ = 0.0f;
    detectiontime = 0.0f;
    soundx= 0.0f; 
    soundz= 0.0f;
    vectorOrientacion.modulo = 0.0f;
    modo = MODO_DEFAULT;
    pedirAyuda = false;
    respawnBoss = false;
    contestar = false;
    defensa = false;
    accionRealizada = false;
    controlRotacion = false;
    distanciaMinimaEsquivar = 3;
    multiplicadorAtaqueEspecial = 1;
    paredRota = -1;

    posicionComunBandada.vX = INT_MAX;
    posicionComunBandada.vY = INT_MAX;
    posicionComunBandada.vZ = INT_MAX;

    distanciaMaximaCohesionBandada = 15;

    distanciaEnemigoJugador.vX = INT_MAX;
    distanciaEnemigoJugador.vY = INT_MAX;
    distanciaEnemigoJugador.vZ = INT_MAX;
    distanciaEnemigoJugador.modulo = INT_MAX;

    distanciaEnemigoObstaculo.vX = INT_MAX;
    distanciaEnemigoObstaculo.vY = INT_MAX;
    distanciaEnemigoObstaculo.vZ = INT_MAX;
    distanciaEnemigoObstaculo.modulo = INT_MAX;

    porcentajeVelocidad = 1.0;
    pesoRotacion = 0.0f;

    

}

Enemigo::Enemigo(float nX, float nY, float nZ, int maxVida/*,
    int accion, int anchoN, int largoN, int altoN*/)
: Enemigo()
{
    vidaIni = maxVida;
    vida = vidaIni;
    posIni.x = nX;
    posIni.y = nY;
    posIni.z = nZ;

    _animacion = nullptr;
    estadoMuerte = 0;//por defecto zero
    fps = 0;

    /*ancho = anchoN;
    largo = largoN;
    alto = altoN;

    _fisicas->crearCuerpo(accion,nX/2,nY/2,nZ/2,2,ancho,alto,largo,2,false);
    _fisicas->crearCuerpo(0,     nX/2,nY/2,nZ/2,2,5,5,5,7,false); //Para ataques
    _fisicas->crearCuerpo(0,     nX/2,nY/2,nZ/2,2,5,5,5,8,false); //Para ataques especiales*/
}

Enemigo::~Enemigo()
{
    //Punteros a clases singleton
    _tiempo = nullptr;
    _motora = nullptr;
    _motor = nullptr;
    _fisicas = nullptr;
    _eventos = nullptr;

    // Enemigo
    atx = 0;
    atespx = 0;
    aty = 0;
    atespy = 0;
    atz = 0;
    atespz = 0;
    atgx = 0;
    atgy = 0;
    atgz = 0;
    atespposX = 0;
    atespposY = 0;
    atespposZ = 0;
    incrAtDisCirc = 0;
    velocidadMaxima = 0;
    porcentajeVelocidad = 0;
    pesoRotacion = 0;
    tipoEnemigo = 0;
    pos_ataques = 0;
    accionRealizada = false;
    contestar = false;
    defensa = false;
    respawnBoss = false;
    accionRealizada = false;
    controlRotacion = false;
    morirRapido = false;
    caminando = false;
    distanciaMinimaEsquivar = 0;
    multiplicadorAtaqueEspecial = 0;
    paredRota = 0;

    distanciaMaximaCohesionBandada = 0;

    posicionComunBandada.vX = 0;
    posicionComunBandada.vY = 0;
    posicionComunBandada.vZ = 0;

    distanciaEnemigoJugador.vX = 0;
    distanciaEnemigoJugador.vY = 0;
    distanciaEnemigoJugador.vZ = 0;
    distanciaEnemigoJugador.modulo = 0;

    distanciaEnemigoObstaculo.vX = 0;
    distanciaEnemigoObstaculo.vY = 0;
    distanciaEnemigoObstaculo.vZ = 0;
    distanciaEnemigoObstaculo.modulo = 0;

    // INnpc
    tipo = 0;
    vida = 0;
    barraAtEs = 0;
    ataque = 0;
    suerte = 0;
    danyoCritico = 0;
    proAtaCritico = 0;
    //TO DO: int buffos[4];
    atackTime = 0;
    atackEspTime = 0;
    lastAtackTime = 0;
    lastAtackEspTime = 0;
    tiempoMerodear = 0;
    tiempoMoverse = 0;
    tiempoOcultarse = 0;
    lastTiempoMerodear = 0;
    lastTiempoMerodear = 0;
    lastTiempoOcultarse = 0;
    animacionMuerteTiem = 0;
    tiempoPasadoMuerte = 0;
    tiempoAtaque = 0;
    tiempoPasadoAtaque = 0;
    tiempoAtaEsp = 0;
    tiempoPasadoAtaEsp = 0;
    tiempoCogerObjeto = 0;
    tiempoPasadoCogerObjeto = 0;
    tiempoEnMorir = 0;
    tiempoPasadoEnMorir = 0;

    // INdrawable
    posIni.x = 0;
    posIni.y = 0;
    posIni.z = 0;

    posActual.x = 0;
    posActual.y = 0;
    posActual.z = 0;

    posPasada.x = 0;
    posPasada.y = 0;
    posPasada.z = 0;

    posFutura.x = 0;
    posFutura.y = 0;
    posFutura.z = 0;

    posFisicas.x = 0;
    posFisicas.y = 0;
    posFisicas.z = 0;

    rotActual.x = 0;
    rotActual.y = 0;
    rotActual.z = 0;

    rotPasada.x = 0;
    rotPasada.y = 0;
    rotPasada.z = 0;

    rotFutura.x = 0;
    rotFutura.y = 0;
    rotFutura.z = 0;

    moveTime = 0;
    rotateTime = 0;
    rotation = 0;
    id = 0;
    animacion = 0;
    animacionAnterior = 0;

    // INsentidos
    //de momento nada
}

float Enemigo::getX()
{
    return posActual.x;
}

float Enemigo::getY()
{
    return posActual.y;
}

float Enemigo::getZ()
{
    return posActual.z;
}

float Enemigo::getNewX()
{
    return posFutura.x;
}

float Enemigo::getNewY()
{
    return posFutura.y;
}

float Enemigo::getNewZ()
{
    return posFutura.z;
}

float Enemigo::getLastX()
{
    return posPasada.x;
}

float Enemigo::getLastY()
{
    return posPasada.y;
}

float Enemigo::getLastZ()
{
    return posPasada.z;
}

float Enemigo::getIniX()
{
    return posIni.x;
}

float Enemigo::getIniY()
{
    return posIni.y;
}

float Enemigo::getIniZ()
{
    return posIni.z;
}

float Enemigo::getFisX()
{
    return posFisicas.x;
}

float Enemigo::getFisY()
{
    return posFisicas.y;
}

float Enemigo::getFisZ()
{
    return posFisicas.z;
}

float Enemigo::getRX()
{
    return rotActual.x;
}

float Enemigo::getRY()
{
    return rotActual.y;
}

float Enemigo::getRZ()
{
    return rotActual.z;
}

INnpc::VectorEspacial Enemigo::GetVectorOrientacion()
{
    return vectorOrientacion;
}

float Enemigo::GetRotation()
{
    return rotation;
}

float Enemigo::GetPesoRotacion()
{
    return pesoRotacion;
}

float Enemigo::getAtX()
{
    return atx;
}

float Enemigo::getAtY()
{
    return aty;
}

float Enemigo::getAtZ()
{
    return atz;
}

float Enemigo::getVelocidadMaxima()
{
    return velocidadMaxima;
}

void Enemigo::definirSala(Sala* sala)
{
    _estoy = sala;
}

void Enemigo::generarSonido(int intensidad,double duracion,int tipo)
{
    EventoSonido* _sonid = new EventoSonido(intensidad, duracion, posActual.x, posActual.y, posActual.z, 2, tipo);
    _eventos->agregarEvento(_sonid);
}

void Enemigo::queEscuchas()
{
    std::vector<EventoSonido* > listaSonidos =  _eventos->listarSonidos(posActual.x, posActual.y);//le pasamos nuestra x e y
    //int cuantos = listaSonidos.size();
    //cout << "Esta escuchando " << cuantos << " sonidos" << endl;
}

void Enemigo::queVes()
{
    /*
    //esto es un ejemplo


    int* loqueve = _eventos->listaObjetos(posActual.x, posActual.y, posActual.z,rotation,20,1,true); //le pedimos al motor de sentidos que nos diga lo que vemos y nos devuelve una lista

    if(loqueve != nullptr)
    {
        if(loqueve[0] == 1)
        {
            std::cout << "ve al jugador" << std::endl;
            std::cout << "" << std::endl;
            std::cout << "" << std::endl;
            std::cout << "" << std::endl;
        }
    }
    delete loqueve;
    if(rotation < 360)
    {
        rotation += 0.1f;
    }
    else
    {
        rotation = 0.0f;
    }*/



    //esto hay que editarlo para cada llamada segun el arbol de comportamientos puesto que a veces interesara ver ciertas cosas, si se le pasa 1 despues del 20 vera solo al jugador si esta, si es 2 se vera los objetos, si es 3 vera los enemigos(para socorrerlos)

}

Sala* Enemigo::GetSala()
{
    return _estoy;
}

void Enemigo::setPosiciones(float nx,float ny,float nz)
{
    posActual.x = nx;
    posActual.y = ny;
    posActual.z = nz;
}

void Enemigo::setPosicionesAtaque(float nx,float ny,float nz)
{
    atx = nx;
    aty = ny;
    atz = nz;
}

void Enemigo::setNewPosiciones(float nx,float ny,float nz)
{
    moveTime = 0.0;
    this->setLastPosiciones(posFutura.x, posFutura.y, posFutura.z);
    posFutura.x = nx;
    posFutura.y = ny;
    posFutura.z = nz;
}

void Enemigo::setLastPosiciones(float nx,float ny,float nz)
{
    posPasada.x = nx;
    posPasada.y = ny;
    posPasada.z = nz;
}

void Enemigo::initPosicionesFisicasAtaque(float nx,float ny,float nz)
{
    iniAtposX = nx;
    iniAtposY = ny;
    iniAtposZ = nz;
}

void Enemigo::initPosicionesFisicas(float nx,float ny,float nz)
{
    posFisicas.x = nx;
    posFisicas.y = ny;
    posFisicas.z = nz;
}

void Enemigo::setPosicionesFisicas(float nx,float ny,float nz)
{
    posFisicas.x += nx;
    posFisicas.y += ny;
    posFisicas.z += nz;
}


void Enemigo::setVelocidadMaxima(float newVelocidad)
{
    velocidadMaxima = newVelocidad;
}

float Enemigo::randomBinomial()
{
    return ((float) rand() - (float) rand()) / RAND_MAX;
}

void Enemigo::UpdateIA()
{
    if(vida > 0)
    {
        switch (tipoEnemigo)
        {
            case 0:
            {
                Pollo *pollo = (Pollo*) this;
                pollo->RunIA();
            }
                break;

            case 1:
            {
                Murcielago *murcielago = (Murcielago*) this;
                murcielago->RunIA();
            }
                break;

            case 2:
            {
                CofreArana *cofreArana = (CofreArana*) this;
                cofreArana->RunIA();
            }
                break;

            default:
                break;
        }
    }
}

void Enemigo::UpdateBehavior(short *i, int* _jugador,
    std::vector<ZonaOscura*> &_getZonasOscuras, std::vector<ZonaEscondite*> &_getZonasEscondite, bool ayuda)
{
    if(vida > 0)
    {
        switch (tipoEnemigo)
        {
            case 0:
            {
                Pollo *pollo = (Pollo*) this;
                pollo->UpdatePollo(i, _jugador, ayuda);
            }
                break;

            case 1:
            {
                Murcielago *murcielago = (Murcielago*) this;
                murcielago->UpdateMurcielago(i, _jugador, _getZonasOscuras);
            }
                break;

            case 2:
            {
                CofreArana* cofreArana = (CofreArana*) this;
                cofreArana->UpdateCofreArana(i, _jugador, ayuda);
            }
                break;

            case 3:
            {
                Guardian *guardian = (Guardian*) this;
                guardian->RunIA();
                guardian->UpdateGuardian(i, _jugador, _getZonasEscondite);
            }
                break;
            case 4:
            {
                Guardian *guardian = (Guardian*) this;
                guardian->RunIA();
                guardian->UpdateGuardian(i, _jugador, _getZonasEscondite);
            }
                break;
            case 5:
            {
                MuerteBoss* _boss = (MuerteBoss*) this;
                _boss->RunIA();
                _boss->UpdateMuerteBoss(i, _jugador, ayuda);
            }
                break;
            default:
            {
                TravornioBoss* _boss = (TravornioBoss*) this;
                _boss->RunIA();
                _boss->UpdateTravornioBoss(i, _jugador, ayuda);
            }
                break;
        }
    }
}

int Enemigo::Atacar(int i)
{
    float danyoF = 0.f, critico = 1.f;
    int danyo = 0, por10 = 10, por100 = 100;
    bool atacado = false;
    if(vida > 0)
    {
        int distance = 0;
        //Temporal
        if (i >= 0) {
            distance = 3;
        } else {
            distance = 5;
        }

        //Calcular posiciones del ataque
        //Calculo de la posicion del ataque en el motor grafico
        atx = this->getX();
        atx += (distance * sin(constantes.PI * this->getRY() / constantes.PI_RADIAN));
        aty = this->getY();
        atz = this->getZ();
        atz += (distance * cos(constantes.PI * this->getRY() / constantes.PI_RADIAN));

        //Calculo de la posicion del ataque en el motor de fisicas
        atposZ = iniAtposZ;
        atposX = iniAtposX;
        atposZ += atz - posIni.z;
        atposX += atx - posIni.x;

        /*//ATAQUE A DISTANCIA
        if(tipoEnemigo == constantes.BOSS)
        {
            _motor->CargarProyectil(getX(),getY(),getZ(),"assets/models/sphere.obj",NULL);
            //Crear cuerpo de colision de ataque delante del enemigo
            _fisicas->crearCuerpo(0,atposX,atposY,atposZ,2,2,0.5,1,4,0,0,false);
            _motora->getEvent("GolpeGuitarra")->start();
        }
        */

        //Acutualizar posicion del ataque
        _fisicas->updateAtaqueEnemigos(atposX,iniAtposY,atposZ,i);

        //Colision
        if(_fisicas->IfCollision(_fisicas->getEnemiesAtack(i),_fisicas->getJugador()))
        {
            atacado = true;
            //cout << "Jugador Atacado" << endl;
            //estos sonidos son para cuando nos ataca un enemigo
            if(tipoEnemigo == 0)
            {
                _motora->getEvent("pollohit")->setPosition(this->getX(),this->getY(),this->getZ());
                _motora->getEvent("pollohit")->start();  
            }
            else if(tipoEnemigo == 1)
            {
                //_motora->getEvent("murcihit")->setPosition(this->getX(),this->getY(),this->getZ());
                _motora->getEvent("murcihit")->start();  
            }
             else if(tipoEnemigo == 6)
            {
                _motora->getEvent("BN1ataca")->setPosition(this->getX(),this->getY(),this->getZ());
                _motora->getEvent("BN1ataca")->start(); 
                _motora->getEvent("enemyhit")->start(); 
            }
            else
            {
                _motora->getEvent("enemyhit")->start(); 
            }
 

        }

        if(atacado)
        {
            //Se calcula el danyo del ataque
            //Se lanza un random y si esta dentro de la probabilidad de critico lanza un critico
            int probabilidad = rand() % por100 + 1;
            if(probabilidad <= proAtaCritico)
            {
                critico += (float) danyoCritico / por100;
                critico = roundf(critico * por10) / por10;
            }

            //Se aplican todas las modificaciones en la variable danyo
            danyoF = ataque * critico;
            danyo = roundf(danyoF * por10) / por10;
        }
    }
    else
    {
        //cout << "No supera las restricciones"<<endl;
    }
    return danyo;
}

/*************** AtacarEspecial *****************
 * Funcion que inicia la ejecucion del ataque
 * especial del enemigo si la barra de ataque
 * especial esta completa y se pulsa el boton Q /
 * click derecho del raton.
 *     Entradas:
 *     Salidas: int danyo;
 */
int Enemigo::AtacarEspecial()
{
    float danyoF = 0.f, aumentosAtaque = 0.f, critico = 1.f;
    int danyo = 0, por10 = 10, por100 = 100;

    //cout << vida << " " << barraAtEs << " " << por100 << endl;
    //Se comprueban las restricciones (de momento solo que esta vivo y la barra de ataque especial)
    if(vida > 0 && barraAtEs == por100)
    {
        //Calcular posiciones si se inicia el ataque especial
        if(atackEspTime <= 0)
        {
            atespx = 6.5 * sin(constantes.PI * getRY() / constantes.PI_RADIAN) + getX();
            atespy = getY();
            atespz = 6.5 * cos(constantes.PI * getRY() / constantes.PI_RADIAN) + getZ();
            atgx = getRX();
            atgy = getRY();
            atgz = getRZ();
            incrAtDisCirc = 0.0;

            //Posiciones en el mundo 3D
            atespposX = (atespx/2);
            atespposY = (getY()/2);
            atespposZ = (atespz/2);

            //Acutualizar posicion del ataque especial
            _fisicas->updateAtaquEspecEnemigos(atespposX,atespposY,atespposZ,getPosAtaques());

            //Crear cuerpo de colision de ataque delante del jugador
            /*
            _motora->getEvent("Arpa")->start();*/
            _motor->dibujarObjetoTemporal(atespx, atespy, atespz, atgx, atgy, atgz, 4, 4, 4, 2);
        }

        //Se calcula el danyo del ataque
        //Se lanza un random y si esta dentro de la probabilidad de critico lanza un critico
        int probabilidad = rand() % por100 + 1;
        if(probabilidad <= proAtaCritico)
        {
            critico += (float) danyoCritico / por100;
            critico = roundf(critico * por10) / por10;
            //cout<<"critico " << proAtaCritico << " " << critico <<endl;
        }

        //Se aplican todas las modificaciones en la variable danyo
        danyoF = ataque * critico * aumentosAtaque;
        //cout << "daño: " <<danyoF<<endl;

        //Colision
        if(_fisicas->IfCollision(_fisicas->getEnemiesAtEsp(constantes.CERO),_fisicas->getJugador()))
        {
            //cout << "Jugador Atacado por ataque especial" << endl;
            danyo = roundf(danyoF * por10) / por10;
        }
        return danyo;
    }
    return danyo;
}

bool Enemigo::estasMuerto()
{
    //cout << "Muere enemigo??: " << vida << endl;
    if(vida <= 0)
    {
        return true;
    }
    return false;
}

bool Enemigo::finalAnimMuerte(){
    if(_tiempo->CalcularTiempoPasado(tiempoPasadoMuerte) >= animacionMuerteTiem && tiempoPasadoMuerte != 0){//sino se cumple no ha acabado
        return true;
    }
    return false;
}

void Enemigo::MuereEnemigo(int enemi){
    if(tiempoPasadoMuerte == 0){
        _motor->colorearEnemigo(255,0,0,0,enemi);//negro
        tiempoPasadoMuerte = _tiempo->GetTiempo(1);
    }
    if(_tiempo->CalcularTiempoPasado(tiempoPasadoMuerte) < animacionMuerteTiem){
        if(_tiempo->CalcularTiempoPasado(tiempoPasadoMuerte) >= 1000.0f){
            _motor->colorearEnemigo(255,255,0,0,enemi);//rojo
        }
    }
    //Sonido de muerte
    // TO DO: utilizar constantes de enemigos
    if(!morirRapido)
    {
        if(tipoEnemigo == 0)
        {        
            _motora->getEvent("Chicken2")->setPosition(this->getX(),this->getY(),this->getZ());
            _motora->getEvent("Chicken2")->start();
        }
        else if(tipoEnemigo == 1)
        {
            _motora->getEvent("Murci2")->setPosition(this->getX(),this->getY(),this->getZ());
            _motora->getEvent("Murci2")->start();
        }
        else if(tipoEnemigo == 3)
        {
            _motora->getEvent("GuardianDie")->setPosition(this->getX(),this->getY(),this->getZ());
            _motora->getEvent("GuardianDie")->start();
        }
    }
    morirRapido = true;
    _motora->getEvent(soundID)->stop();

}

void Enemigo::Interactuar(int id, int id2)
{

}

/*************** moverseEntidad *****************
 * Funcion con la que los enemigos se desplazaran
 * por el escenario mediante una interpolacion desde
 * el punto de origen al punto de destino
 */
void Enemigo::moverseEntidad(float updTime)
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
    
    if(tipoEnemigo == 0 || tipoEnemigo == 1 || tipoEnemigo == 2)
    {
        _motora->getEvent(soundID)->setPosition(this->getX(),this->getY(),this->getZ());
    }
    else if(tipoEnemigo == 3)
    {
        _motora->getEvent(soundID)->setPosition(this->getX(),this->getY(),this->getZ());

        if(soundx == posActual.x && soundz == posActual.z)
        {
            _motora->getEvent(soundID)->pause(); 
        }
        else
        {
            _motora->getEvent(soundID)->resume(); 
        }       

        if(_tiempo->CalcularTiempoPasado(detectiontime) > 2000.0f)
        {
        detectiontime = _tiempo->GetTiempo(1);
        }

        if(_tiempo->CalcularTiempoPasado(detectiontime) >= 1970.0f)
        {
            soundx = posActual.x;
            soundz = posActual.z;
        }
    }
}

void Enemigo::RespawnNoise()
{
    cout << "respawnNoise" << endl;
    _motora->LoadEvent("event:/SFX/SFX-Muerte invoca enemigos","respawnfire",1);  
    _motora->getEvent("respawnfire")->setPosition(this->getX(),this->getY(),this->getZ());
    _motora->getEvent("respawnfire")->start();  
}
/*************** rotarEntidad *****************
 * Funcion con la que el enemigo rotara
 * sobre si mismo mediante una interpolacion desde
 * el punto de origen al punto de destino
 */
void Enemigo::RotarEntidad(float updTime)
{
    //pt es el porcentaje de tiempo pasado desde la posicion
    //de update antigua hasta la nueva
    float pt = rotateTime / updTime;

    if(pt > 1.0f)
    {
        pt = 1.0f;
    }
    else if(pt < 0.0f)
    {
        pt = 0.0f;
    }

    rotActual.x = rotPasada.x * (1 - pt) + rotFutura.x * pt;
    rotActual.y = rotPasada.y * (1 - pt) + rotFutura.y * pt;
    rotActual.z = rotPasada.z * (1 - pt) + rotFutura.z * pt;
}

void Enemigo::UpdateTimeMove(float updTime)
{
    moveTime += updTime;
}

void Enemigo::UpdateTimeRotate(float updTime)
{
    rotateTime += updTime;
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
void Enemigo::ModificarVida(int vid)
{
    if(defensa && vid < 0)
    {
        vida += vid/constantes.DOS;
    }
    else
        {
            vida += vid;
        }
    float ultimoEstertor = vidaIni * constantes.UN_CUARTO;
    if(vid < 0)
    {
        if(tipoEnemigo == 3 || tipoEnemigo == 4)
        {
            if(vida <= ultimoEstertor)
            {
                modo = MODO_HUIDA;
            }
            else
            {
                modo = MODO_ATAQUE;
            }
        }
        else if(tipoEnemigo == constantes.BOSS || tipoEnemigo == constantes.TRAVORNIO)
        {
            ModificarBarraAtEs(abs(vid));
        }

    }
    if (vida > vidaIni)
        vida = vidaIni;
    else if (vida < 0)
        vida = 0;
}

void Enemigo::setVida(int vid)
{
    vida = vid;
}

void Enemigo::setTipo(int tip)
{

}

void Enemigo::SetRespawnBoss(bool crearEnemigos)
{
    respawnBoss = crearEnemigos;
}

/*************** Modificar BarraAtEs *****************
 *  Funcion que actualiza la barra del ataque especial
 *  Entradas:
 *      bar: valor en positivo o negativo
 *  Salidas:
 *
 */
void Enemigo::ModificarBarraAtEs(int bar)
{
    barraAtEs += bar * multiplicadorAtaqueEspecial;
    if(barraAtEs < 0)
        barraAtEs = 0;
    if(barraAtEs > 100)
        barraAtEs = 100;
}

void Enemigo::setBarraAtEs(int bar)
{
    barraAtEs = bar;
}

void Enemigo::setAtaque(int ataq)
{
    ataque = ataq;
}

void Enemigo::setArmaEspecial(int ataque)
{
    _armaEspecial = new Arma(ataque,2,2,2,constantes.ARMA);
}

void Enemigo::setSuerte(int suer)
{

}

void Enemigo::setPosAtaques(int p)
{
 pos_ataques = p;
}

int Enemigo::getPosAtaques()
{
  return pos_ataques;
}

void Enemigo::setDanyoCritico(int danyoC)
{
    danyoCritico = danyoC;
}

void Enemigo::setProAtaCritico(int probabilidad)
{
    proAtaCritico = probabilidad;
}

void Enemigo::setTimeAt(float time)
{
    atackTime = time;
}

void Enemigo::setLastTimeAt(float time)
{
    lastAtackTime = time;
}

void Enemigo::setTimeDefenderse(float time)
{
    tiempoDefenderse = time;
}

void Enemigo::setLastTimeDefenderse(float time)
{
    lastTiempoDefenderse = time;
}

void Enemigo::setTimeAtEsp(float time)
{
    atackEspTime = time;
}

void Enemigo::setLastTimeAtEsp(float time)
{
    lastAtackEspTime = time;
}

void Enemigo::SetSala(Sala* sala)
{
    _estoy = sala;
}

int Enemigo::getVidaIni()
{
    return vidaIni;
}

int Enemigo::getVida()
{
    return vida;
}

int Enemigo::getTipo()
{
    return -1;
}

int Enemigo::getBarraAtEs()
{
    return barraAtEs;
}

int Enemigo::getAtaque()
{
    return -1;
}

int Enemigo::getSuerte()
{
    return -1;
}

int Enemigo::getDanyoCritico()
{
    return -1;
}

int Enemigo::getProAtaCritico()
{
    return -1;
}

int* Enemigo::getBuffos()
{
    int* valores = new int[6];
    return valores;
}

void Enemigo::setID(int nid)
{
    id = nid;
    soundID = std::to_string(id);
}

int Enemigo::getID()
{
    return id;
}

void Enemigo::setRotation(float rot)
{
    rotation = rot;
}

void Enemigo::setPesoRotacion(float peso)
{
    pesoRotacion = peso;
}

void Enemigo::setRotacion(float nrx, float nry, float nrz)
{
    rotActual.x = nrx;
    rotActual.y = nry;
    rotActual.z = nrz;
}

void Enemigo::setNewRotacion(float nrx, float nry, float nrz)
{
    rotateTime = 0.0;
    this->setLastRotacion(rotFutura.x, rotFutura.y, rotFutura.z);
    rotFutura.x = nrx;
    rotFutura.y = nry;
    rotFutura.z = nrz;
}

void Enemigo::setLastRotacion(float nrx, float nry, float nrz)
{
    rotPasada.x = nrx;
    rotPasada.y = nry;
    rotPasada.z = nrz;
}

void Enemigo::setVectorOrientacion()
{
    vectorOrientacion.vX = sin(constantes.PI * rotFutura.y / constantes.PI_RADIAN);
    vectorOrientacion.vY = 0.0f;
    vectorOrientacion.vZ = cos(constantes.PI * rotFutura.y / constantes.PI_RADIAN);
}

void Enemigo::setTimeOcultarse(float t)
{
    tiempoOcultarse = t;
}

void Enemigo::setLastTimeOcultarse(float t)
{
    lastTiempoOcultarse = t;
}

void Enemigo::setTimeMerodear(float t)
{
    tiempoMerodear = t;
}

void Enemigo::setLastTimeMerodear(float t)
{
    lastTiempoMerodear = t;
}

void Enemigo::setTimeMoverse(float t)
{
    tiempoMoverse = t;
}

void Enemigo::setLastTimeMoverse(float t)
{
    lastTiempoMoverse = t;
}

void Enemigo::SetEnemigo(int enemigo)
{
    tipoEnemigo = enemigo;
}

void Enemigo::SetAranaSound()
{    
    _motora->LoadEvent("event:/SFX/SFX-Arana grito enemigo", soundID, 1);
    _motora->getEvent(soundID)->setPosition(posActual.x,0,posActual.z);
    _motora->getEvent(soundID)->start();
}
void Enemigo::SetModo(int newModo)
{
    modo = newModo;
}

void Enemigo::SetPosicionComunBandada(INnpc::VectorEspacial posicion)
{
    posicionComunBandada = posicion;
}

void Enemigo::SetMultiplicadorAtEsp(float multiplicador)
{
    multiplicadorAtaqueEspecial = multiplicador;
}

void Enemigo::setDefenderse(bool activarDefensa)
{
    defensa = activarDefensa;
}

float Enemigo::getTimeOcultarse()
{
    return tiempoOcultarse;
}

float Enemigo::getLastTimeOcultarse()
{
    return lastTiempoOcultarse;
}

float Enemigo::getTimeMerodear()
{
    return tiempoMerodear;
}

float Enemigo::getLastTimeMerodear()
{
    return lastTiempoMerodear;
}

float Enemigo::getTimeMoverse()
{
    return tiempoMoverse;
}

float Enemigo::getLastTimeMoverse()
{
    return lastTiempoMoverse;
}

float Enemigo::getTimeAt()
{
    return atackTime;
}

float Enemigo::getLastTimeAt()
{
    return lastAtackTime;
}

float Enemigo::getTimeDefenderse()
{
    return tiempoDefenderse;
}

float Enemigo::getLastTimeDefenderse()
{
    return lastTiempoDefenderse;
}

float Enemigo::getTimeAtEsp()
{
    return atackEspTime;
}

float Enemigo::getLastTimeAtEsp()
{
    return lastAtackEspTime;
}

int Enemigo::GetEnemigo()
{
    return tipoEnemigo;
}

int Enemigo::GetModo()
{
    return modo;
}

bool Enemigo::GetRespawnBoss()
{
    return respawnBoss;
}

bool Enemigo::getDefenderse()
{
    return defensa;
}

ZonaOscura* Enemigo::getZonaOscuraMasCercana(vector <ZonaOscura*>& zonasOscuras, ZonaOscura* _zonaUsada)
{
    ZonaOscura* _zonaElegida = nullptr;
    VectorEspacial distanciaZonaActual, distanciaZonaElegida;
    vector<Zona*> zonasCompletas;
    zonasCompletas.reserve(zonasOscuras.size());

    unsigned short i = 0;
    while(i < zonasOscuras.size() && (_zonaElegida == nullptr || distanciaZonaElegida.modulo > 0.0f))
    {
        if(zonasOscuras.at(i) != nullptr)
        {
            distanciaZonaActual.vX = abs(zonasOscuras.at(i)->getX() - posActual.x);
            distanciaZonaActual.vY = abs(zonasOscuras.at(i)->getY() - posActual.y);
            distanciaZonaActual.vZ = abs(zonasOscuras.at(i)->getZ() - posActual.z);
            distanciaZonaActual.modulo = pow(distanciaZonaActual.vX, constantes.DOS) + pow(distanciaZonaActual.vY, constantes.DOS) + pow(distanciaZonaActual.vZ, constantes.DOS);
            distanciaZonaActual.modulo = sqrt(distanciaZonaActual.modulo);

            if(_zonaElegida == nullptr || distanciaZonaElegida.modulo > distanciaZonaActual.modulo)
            {

                 distanciaZonaElegida = distanciaZonaActual;
                _zonaElegida = zonasOscuras.at(i);
            }
        }
        i++;
    }
    return _zonaElegida;
}
ZonaEscondite* Enemigo::getZonaEsconditeMasCercana(vector <ZonaEscondite*> &zonasEscondite, ZonaEscondite* _zonaUsada)
{
    ZonaEscondite* _zonaElegida = nullptr;
    VectorEspacial distanciaZonaActual, distanciaZonaElegida;
    vector<Zona*> zonasCompletas;
    zonasCompletas.reserve(zonasEscondite.size());

    unsigned short i = 0;
    while(i < zonasEscondite.size() && (_zonaElegida == nullptr || distanciaZonaElegida.modulo > 0.0f))
    {
        if(zonasEscondite.at(i) != nullptr)
        {
            distanciaZonaActual.vX = abs(zonasEscondite.at(i)->getX() - posActual.x);
            distanciaZonaActual.vY = abs(zonasEscondite.at(i)->getY() - posActual.y);
            distanciaZonaActual.vZ = abs(zonasEscondite.at(i)->getZ() - posActual.z);
            distanciaZonaActual.modulo = pow(distanciaZonaActual.vX, constantes.DOS) + pow(distanciaZonaActual.vY, constantes.DOS) + pow(distanciaZonaActual.vZ, constantes.DOS);
            distanciaZonaActual.modulo = sqrt(distanciaZonaActual.modulo);

            if(_zonaElegida == nullptr || distanciaZonaElegida.modulo > distanciaZonaActual.modulo)
            {

                 distanciaZonaElegida = distanciaZonaActual;
                    _zonaElegida = zonasEscondite.at(i);
            }
        }
        i++;
    }
    return _zonaElegida;
}
//ia

void Enemigo::setArbol(Arbol* ia)
{
    arbol = new Arbol(ia->GetRaiz(), ia->GetRaiz()->getNombre());
}

Arbol * Enemigo::getArbol()
{
    return arbol;
}

short int* Enemigo::RunIA(bool funciona/*, bool ayuda*/)//TO DO: ayuda es si _enemPideAyuda tiene algun enemigo
{
    //aun por determinar primero definir bien la carga de arboles
    return arbol->ContinuarSiguienteNodo(funciona);//el true lo ponemos para detectar la primera ejecucion del bucle
    //bool salir = false;//cuando terminemos el arbol salimos
    /*while(!salir)
    {
        bool es = Acciones(accion, ayuda);
        accion = arbol->siguiente(es);//cambiamos de rama(false) o de hoja(true)
        salir = arbol->estadoActual();//ultima rama o entras en bucle
    }*/
}

void Enemigo::ForzarCambioNodo(const short * nodo)
{
    arbol->CambiarNodo(nodo);
}

//fin ia

//comportamientos bases
    bool Enemigo::Acciones(int accion/*, bool ayuda*/)
    {
        switch(accion)
        {
            case 0://es raiz
                return false;
            break;
            case 1://ve al jugador
                return ver(1, 30);
            case 2://merodeo
                //return Merodear();//merodeo pollo
            case 3://esta cerca del jugador
                return true;
            case 4://atacar
                return true;
            case 6://oir al jugador
                return oir(1);
            case 8://pedir ayuda
                return PedirAyuda(/*ayuda*/false);
            case 9://oye pedir ayuda enemigo ?
                return oir(2);
            case 10://contestacion a auxilio
                return ContestarAyuda();
        }

        return false;//cambiamos de rama si no se encuentra la tarea
    }


    void Enemigo::alinearse(VectorEspacial* target, bool huir)
    {
        float contraRotacion = 0.0f;
        Constantes constantes;

        if(controlRotacion)
        {
            controlRotacion = false;
        
        }
        if(modo == MODO_ATAQUE || modo == MODO_AUXILIAR_ALIADO)
        {
            pesoRotacion = constantes.UN_MEDIO;
            contraRotacion = 1.0 - pesoRotacion;
            if(this->ver(constantes.TRES, constantes.SEIS * constantes.CINCO) && tipoEnemigo != constantes.BOSS)
            {
                controlRotacion = true;
            }
        }
        else
        {
            pesoRotacion = constantes.UN_TERCIO;
        }

        VectorEspacial distancia;
        distancia.vX = target->vX - this->getX();
        distancia.vY = target->vY - this->getY();
        distancia.vZ = target->vZ - this->getZ();
        distancia.modulo = pow(distancia.vX, constantes.DOS) + pow(distancia.vY, constantes.DOS) + pow(distancia.vZ, constantes.DOS);
        distancia.modulo = sqrt(distancia.modulo);

        if(controlRotacion)
        {
            distancia.vZ < 0 ?
                rotation += (constantes.PI_RADIAN + (constantes.RAD_TO_DEG * atan(distancia.vX/distancia.vZ))) * contraRotacion :
                rotation += (constantes.RAD_TO_DEG * atan(distancia.vX/distancia.vZ)) * contraRotacion;
        }
        else
        {
            distancia.vZ < 0 ?
            rotation = constantes.PI_RADIAN + (constantes.RAD_TO_DEG * atan(distancia.vX/distancia.vZ)) :
            rotation = constantes.RAD_TO_DEG * atan(distancia.vX/distancia.vZ);
        }


        if(huir)
        {
            rotation += constantes.PI_RADIAN;
        }

        this->setNewRotacion(rotActual.x, rotation, rotActual.z);
        this->setVectorOrientacion();
    }

    bool Enemigo::ver(int tipo, int longitud)
    {
        Constantes constantes;
        bool ve = false, obsPorDelante = false, colisiona = false;
        short posicionArray = 0;
        int* loqueve = _eventos->listaObjetos(posActual.x, posActual.y, posActual.z,rotActual.y,longitud, tipo, true); //le pedimos al motor de sentidos que nos diga lo que vemos y nos devuelve una lista

        //vamos a  ver si vemos al jugador
        if(tipo == 1)//ves al jugador ?
        {
            if(loqueve != nullptr)
            {
                if(loqueve[0] == 1)
                {
                    ve = true;
                }
                else if(loqueve[7] == 1)
                {
                    ve = true;
                    posicionArray = 7;
                }
                else if(loqueve[14])
                {
                    ve = true;
                    posicionArray = 14;
                }
                if(ve)
                {
                    distanciaEnemigoJugador.vX = loqueve[posicionArray + 1] - posActual.x;
                    distanciaEnemigoJugador.vY = loqueve[posicionArray + 2] - posActual.y;
                    distanciaEnemigoJugador.vZ = loqueve[posicionArray + 3] - posActual.z;
                    distanciaEnemigoJugador.modulo = sqrt(pow(distanciaEnemigoJugador.vX, constantes.DOS) + pow(distanciaEnemigoJugador.vY, constantes.DOS) + pow(distanciaEnemigoJugador.vZ, constantes.DOS));

                    delete [] loqueve;
                    return true;
                }
            }
            delete [] loqueve;
        }
        if(tipo == 2)//ves algun objeto ?
        {
            int* destino = new int[6];
            if(loqueve != nullptr)
            {
                //Ve algo en la lejania de su visor central
                if(loqueve[0] == 1)
                {
                    ve = true;
                    distanciaEnemigoObstaculo.vX = loqueve[1] - posActual.x;
                    distanciaEnemigoObstaculo.vY = loqueve[2] - posActual.y;
                    distanciaEnemigoObstaculo.vZ = loqueve[3] - posActual.z;
                    distanciaEnemigoObstaculo.modulo = sqrt(pow(distanciaEnemigoObstaculo.vX, constantes.DOS) + pow(distanciaEnemigoObstaculo.vY, constantes.DOS) + pow(distanciaEnemigoObstaculo.vZ, constantes.DOS));

                    //Si entra aquí es que el visor central
                    //y el enemigo en cuestion esta muy cerca del obstaculo que debe esquivar
                    if(distanciaEnemigoObstaculo.modulo <= distanciaMinimaEsquivar)
                    {
                        colisiona = true;
                        destino[0] = loqueve[1];
                        destino[1] = loqueve[2];
                        destino[2] = loqueve[3];
                        destino[3] = loqueve[4];
                        destino[4] = loqueve[5];
                        destino[5] = loqueve[6];


                        porcentajeVelocidad = (float) constantes.UNO;
                        //cout<<"QUE SE SALE"<<endl;
                    }
                    else
                    {
                        //Reducimos la velocidad para evitar que se salga
                        if(porcentajeVelocidad > 0.2)
                        {
                            porcentajeVelocidad *= 0.9;
                        }
                        else if(porcentajeVelocidad < 0.2)
                        {
                            porcentajeVelocidad = 0.2;
                        }
                        if(rotation <= 1.0f)
                        {
                            rotation = maxRotacion / constantes.DOS;
                        }
                    }
                }
                //Si entra aqui dentro es que detecta un obstaculo con su visor izquierdo
                if(loqueve[7] == 1 && !colisiona)
                {
                    ve = true;
                    //Reducimos la velocidad para evitar que se salga
                    if(porcentajeVelocidad > 0.0)
                    {
                        porcentajeVelocidad *= 0.9;
                    }
                    else if(porcentajeVelocidad < 0.0)
                    {
                        porcentajeVelocidad = 0.0;
                    }
                    colisiona = true;
                    //Si entra aqui dentro es que detecta un obstaculo por delante con los visores laterales
                    if(loqueve[14] == 1)
                    {
                        //Coordenadas del punto de obstaculo
                        destino[0] = loqueve[1];
                        destino[1] = loqueve[2];
                        destino[2] = loqueve[3];
                        //Valores del vector Normal
                        destino[3] = loqueve[4];
                        destino[4] = loqueve[5];
                        destino[5] = loqueve[6];

                        //cout<<"COLISIONA POR DELANTE"<<endl;
                    }
                    //Si entra aqui dentro es que detecta un obstaculo con su visor derecho
                    else
                    {
                        //Coordenadas del punto de obstaculo
                        destino[0] = loqueve[8];
                        destino[1] = loqueve[9];
                        destino[2] = loqueve[10];
                        //Valores del vector Normal
                        destino[3] = loqueve[11];
                        destino[4] = loqueve[12];
                        destino[5] = loqueve[13];

                        //cout<<"COLISIONA POR LA IZQUIERDA"<<endl;
                    }
                }
                //Si entra aqui dentro es que detecta un obstaculo con su visor derecho
                else if(loqueve[14] == 1 && !colisiona)
                {
                    ve = true;
                    //Reducimos la velocidad para evitar que se salga
                    if(porcentajeVelocidad > 0.0)
                    {
                        porcentajeVelocidad *= 0.9;
                    }
                    else if(porcentajeVelocidad < 0.0)
                    {
                        porcentajeVelocidad = 0.0;
                    }
                    colisiona = true;
                    //Coordenadas del punto de obstaculo
                    destino[0] = loqueve[15];
                    destino[1] = loqueve[16];
                    destino[2] = loqueve[17];
                    //Valores del vector Normal
                    destino[3] = loqueve[18];
                    destino[4] = loqueve[19];
                    destino[5] = loqueve[20];


                    //cout<<"COLISIONA POR LA DERECHA"<<endl;
                }
                if(colisiona)
                {
                    if(!controlRotacion)
                    {
                        controlRotacion = true;
                        //rotation = 0.0f;
                    }
                    //Creamos un vector con una nueva direccion normalizando el vector director anterior
                    VectorEspacial vectorDirector = this->normalizarVector(destino);
                    //Se suma la normal del obstaculo aplicando pesos a la normal y al vector director
                    if(vectorDirector.modulo != constantes.CERO)
                    {
                        this->modificarTrayectoria(&vectorDirector, destino); 
                        //esto es para que gire hacia atras ya que al valor que devuelve atan hay que darle la vuelta 180
                        vectorDirector.vZ < 0 ?
                            rotation = (constantes.PI_RADIAN + (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ))):
                            rotation = (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ));
                    }
                }
                else if(controlRotacion)
                {
                    controlRotacion = false;
                    rotation = 0.0f;
                    if(porcentajeVelocidad <= 0.0f)
                    {
                        porcentajeVelocidad = 0.2;
                    }
                }

                else if(!ve)
                {

                    if(porcentajeVelocidad < velocidadMaxima)
                    {
                        porcentajeVelocidad /= 0.9;
                    }
                    else if(porcentajeVelocidad > velocidadMaxima)
                    {
                        porcentajeVelocidad = velocidadMaxima;
                    }
                }
                delete loqueve;
                return true;
            }
            delete [] loqueve;
        }
        if(tipo == 3) //Ves algun enemigo?
        {
            VectorEspacial posicionEnemigo;
            int* destino = new int[6];
            if(loqueve != nullptr)
            {
                //Ve algo en la lejania de su visor central
                if(loqueve[0] == 1)
                {
                    posicionEnemigo.vX = loqueve[1] - posActual.x;
                    posicionEnemigo.vY = loqueve[2] - posActual.y;
                    posicionEnemigo.vZ = loqueve[3] - posActual.z;
                    posicionEnemigo.modulo = sqrt(pow(posicionEnemigo.vX, constantes.DOS) + pow(posicionEnemigo.vY, constantes.DOS) + pow(posicionEnemigo.vZ, constantes.DOS));

                    if(posicionEnemigo.modulo <= distanciaMinimaEsquivar)
                    {
                        colisiona = true;
                        destino[0] = loqueve[1];
                        destino[1] = loqueve[2];
                        destino[2] = loqueve[3];
                        destino[3] = loqueve[4];
                        destino[4] = loqueve[5];
                        destino[5] = loqueve[6];
                    }
                    else
                    {
                        if(porcentajeVelocidad >= 0.5)
                        {
                            porcentajeVelocidad *= 0.9;
                        }
                        obsPorDelante = true;
                    }

                    //cout<<"VE AL ENEMIGO POR DELANTE"<<endl;
                }
                //Si entra aqui dentro es que detecta un obstaculo por delante con el visores izquierdo
                if(loqueve[7] == 1)
                {
                    if(!obsPorDelante && porcentajeVelocidad >= 0.4)
                    {
                        porcentajeVelocidad *= 0.9;
                    }
                    colisiona = true;
                    posicionEnemigo.vX = loqueve[8] - posActual.x;
                    posicionEnemigo.vY = loqueve[9] - posActual.y;
                    posicionEnemigo.vZ = loqueve[10] - posActual.z;
                    posicionEnemigo.modulo = sqrt(pow(posicionEnemigo.vX, constantes.DOS) + pow(posicionEnemigo.vY, constantes.DOS) + pow(posicionEnemigo.vZ, constantes.DOS));

                    if(loqueve[14] == 1 && posicionEnemigo.modulo <= distanciaMinimaEsquivar)
                    {
                        /*if(porcentajeVelocidad <= 0.5f)
                        {*/

                            colisiona = true;
                            destino[0] = loqueve[1];
                            destino[1] = loqueve[2];
                            destino[2] = loqueve[3];
                            destino[3] = loqueve[4];
                            destino[4] = loqueve[5];
                            destino[5] = loqueve[6];

                        //cout<<"COLISIONA CON ENEMIGO POR DELANTE"<<endl;
                    }
                    else if(posicionEnemigo.modulo <= distanciaMinimaEsquivar)
                    {
                        colisiona = true;
                        destino[0] = loqueve[8];
                        destino[1] = loqueve[9];
                        destino[2] = loqueve[10];
                        destino[3] = loqueve[11];
                        destino[4] = loqueve[12];
                        destino[5] = loqueve[13];
                        //rotation += 15;
                        //cout<<"COLISIONA CON ENEMIGO POR LA IZQUIERDA"<<endl;
                    }
                }
                //Si entra aqui dentro es que detecta un obstaculo con su visor derecho
                else if(loqueve[14] == 1)
                {
                    if(!obsPorDelante && porcentajeVelocidad >= 0.4)
                    {
                        porcentajeVelocidad *= 0.9;
                    }
                    colisiona = true;
                    posicionEnemigo.vX = loqueve[15] - posActual.x;
                    posicionEnemigo.vY = loqueve[16] - posActual.y;
                    posicionEnemigo.vZ = loqueve[17] - posActual.z;
                    posicionEnemigo.modulo = sqrt(pow(posicionEnemigo.vX, constantes.DOS) + pow(posicionEnemigo.vY, constantes.DOS) + pow(posicionEnemigo.vZ, constantes.DOS));


                    if(posicionEnemigo.modulo <= distanciaMinimaEsquivar)
                    {
                        colisiona = true;
                        destino[0] = loqueve[15];
                        destino[1] = loqueve[16];
                        destino[2] = loqueve[17];
                        destino[3] = loqueve[18];
                        destino[4] = loqueve[19];
                        destino[5] = loqueve[20];
                        //rotation -= 15;

                        //cout<<"COLISIONA CON ENEMIGO POR LA DERECHA"<<endl;
                    }
                }
                else
                {
                    if(!obsPorDelante)
                        porcentajeVelocidad = 1.0;
                }
            }
            if(colisiona)
            {
                //Creamos un vector con una nueva direccion normalizando el vector director anterior
                VectorEspacial vectorDirector = this->normalizarVector(destino);
                //Se suma la normal del obstaculo aplicando pesos a la normal y al vector director
                if(vectorDirector.modulo != constantes.CERO)
                {
                    this->modificarTrayectoria(&vectorDirector, destino); 
                    //esto es para que gire hacia atras ya que al valor que devuelve atan hay que darle la vuelta 180
                    vectorDirector.vZ < 0 ?
                        rotation = (constantes.PI_RADIAN + (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ))):
                        rotation = (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ));
                }
            }
            delete [] loqueve;
            return colisiona;
        }

        return false;
    }

    bool Enemigo::oir(int tipo)//tipo 1 oir al jugador si lo oye true, tipo 2 si oye al enemigo pedir ayuda si lo oye true si no false
    {
        std::vector<EventoSonido* > listaSonidos =  _eventos->listarSonidos(posActual.x, posActual.z);//le pasamos nuestra x e y

        if(listaSonidos.size() > 0)
        {
            for(std::size_t i=0;i<listaSonidos.size();i++)
            {
                if(tipo == listaSonidos[i]->getTipo())
                {
                    return true;
                }
            }
        }

        return false;
    }

    /******************** perseguir **********************
     * Funcion que acerca los enemigos al jugador para
     * atacarlo posteriormente teniendo en cuenta la
     * orientacion del mismo
     *
     *      Entradas:
     *                  int* _jug: entero que es la direccion que apunta a donde se guarda el jugador
     *      Salidas:
     *                  bool funciona: booleano que indica si el comportamiento ha funcionado
    */
    bool Enemigo::perseguir(int* _jug, short int* _n)
    {
        Jugador* _jugador = (Jugador*)_jug;
        bool funciona = true;
        VectorEspacial datosDesplazamiento, objetivo;
        struct{
            float x = 0.0f;
            float z = 0.0f;
        }
        orientacion;

        orientacion.x = (vectorOrientacion.vX + _jugador->GetVectorOrientacion().vX) / constantes.DOS;
        if(abs(orientacion.x) < 0.1)
        {
            orientacion.x = vectorOrientacion.vX;
        }
        orientacion.z = (vectorOrientacion.vZ + _jugador->GetVectorOrientacion().vZ) / constantes.DOS;
        if(abs(orientacion.z) < 0.1)
        {
            orientacion.z = vectorOrientacion.vZ;
        }

        //Mentiene al grupo unido, si la distancia es mayor a la maxima que deben tener los enemigos
        //se acercan a su punto central de bandada. EN caso contrario, persiguen al objetivo
        if(comprobarDistanciaFlocking())
        {
            objetivo.vX = (posicionComunBandada.vX * constantes.DOS_TERCIOS + _jugador->getX() / constantes.DOS * constantes.UN_TERCIO);
            objetivo.vY = (posicionComunBandada.vY * constantes.DOS_TERCIOS + _jugador->getY() / constantes.DOS * constantes.UN_TERCIO);
            objetivo.vZ = (posicionComunBandada.vZ * constantes.DOS_TERCIOS + _jugador->getZ() / constantes.DOS * constantes.UN_TERCIO);
        }
        else
        {
            objetivo.vX = _jugador->getX();
            objetivo.vY = _jugador->getY();
            objetivo.vZ = _jugador->getZ();
        }

        datosDesplazamiento.vX = vectorOrientacion.vX * velocidadMaxima * porcentajeVelocidad;
        datosDesplazamiento.vZ = vectorOrientacion.vZ * velocidadMaxima * porcentajeVelocidad;
        if(_fisicas->enemyCollideObstacle((unsigned) *_n) || _fisicas->enemyCollideParedesRompibles((unsigned) *_n))
        {
            int* destino = _fisicas->ObtenerNormalColision(posPasada.x, posPasada.y, posPasada.z, rotActual.y + constantes.PI_MEDIOS);
            if(!destino)
            {
                destino = _fisicas->ObtenerNormalColision(posPasada.x, posPasada.y, posPasada.z, rotActual.y + constantes.PI_MEDIOS + constantes.PI_CUARTOS);
                if(!destino)
                {
                    destino = _fisicas->ObtenerNormalColision(posPasada.x, posPasada.y, posPasada.z, rotActual.y + constantes.PI_MEDIOS - constantes.PI_CUARTOS);
                }
            }
            
            //Creamos un vector con una nueva direccion normalizando el vector director anterior
            VectorEspacial vectorDirector = this->normalizarVector(destino);
            //Se suma la normal del obstaculo aplicando pesos a la normal y al vector director
            if(vectorDirector.modulo != constantes.CERO)
            {
                this->modificarTrayectoria(&vectorDirector, destino); 
                //esto es para que gire hacia atras ya que al valor que devuelve atan hay que darle la vuelta 180
                vectorDirector.vZ < 0 ?
                    rotation = (constantes.PI_RADIAN + (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ))):
                    rotation = (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ));
            }

            this->setNewRotacion(rotActual.x, rotation, rotActual.z);
            this->setVectorOrientacion();
            datosDesplazamiento.vX = vectorOrientacion.vX * velocidadMaxima * porcentajeVelocidad;
            datosDesplazamiento.vZ = vectorOrientacion.vZ * velocidadMaxima * porcentajeVelocidad;
            this->setNewPosiciones(posFutura.x + datosDesplazamiento.vX, posFutura.y, posFutura.z + datosDesplazamiento.vZ);
            this->setPosicionesFisicas(datosDesplazamiento.vX, constantes.CERO, datosDesplazamiento.vZ);
            funciona = false;
        }
        else
        {
            this->alinearse(&objetivo, false);

            //Persiguen al objetivo teniendo en cuenta tambien la direccion que tiene para avanzarse a sus pasos
            if(abs(_jugador->getX()) >= posActual.x + distanciaMinimaEsquivar)
            {
                if(abs(_jugador->getZ()) >= posActual.z + distanciaMinimaEsquivar)
                {
                    datosDesplazamiento.vX = orientacion.x * velocidadMaxima * porcentajeVelocidad;
                    datosDesplazamiento.vZ = orientacion.z * velocidadMaxima * porcentajeVelocidad;
                }
                else
                {
                    datosDesplazamiento.vX = orientacion.x * velocidadMaxima * porcentajeVelocidad;
                    datosDesplazamiento.vZ = vectorOrientacion.vZ * velocidadMaxima * porcentajeVelocidad ;
                }
                
            }
            else
            {
                if(abs(_jugador->getZ()) >= posActual.z + distanciaMinimaEsquivar)
                {
                    datosDesplazamiento.vX = vectorOrientacion.vX * velocidadMaxima * porcentajeVelocidad;
                    datosDesplazamiento.vZ = orientacion.z * velocidadMaxima * porcentajeVelocidad;
                }
                else
                {
                    datosDesplazamiento.vX = vectorOrientacion.vX * velocidadMaxima * porcentajeVelocidad;
                    datosDesplazamiento.vZ = vectorOrientacion.vZ * velocidadMaxima * porcentajeVelocidad;
                }
            }
            
            
            if((abs(objetivo.vX - this->getX())) > abs(distanciaMinimaEsquivar) || (abs(objetivo.vZ - this->getZ()) > abs(distanciaMinimaEsquivar)))
            {
                this->setNewPosiciones(posFutura.x + datosDesplazamiento.vX, posFutura.y, posFutura.z + datosDesplazamiento.vZ);
                this->setPosicionesFisicas(datosDesplazamiento.vX, constantes.CERO, datosDesplazamiento.vZ);
            }

            //Se comprueba si la distancia entre el enemigo y el jugador es menor o igual a la distancia maxima que que indica la variable "distancia"
            if(abs(objetivo.vZ - this->getZ()) <= abs(distanciaMinimaEsquivar))
            {
                if(abs(objetivo.vX - this->getX()) <= abs(distanciaMinimaEsquivar))
                {
                    funciona = true;
                }
                else
                {
                    funciona = false;
                }
            }
            else
            {
                funciona = false;
            }
        }
        return funciona;
    }

    void Enemigo::embestir(bool modificarDireccion, int* _jug)
    {
        Constantes constantes;
        Jugador* _jugador = (Jugador*) _jug;
        VectorEspacial velocidad, posiciones, target, datosDesplazamiento;
        if(modificarDireccion)
        {
            target.vX = _jugador->getX();
            target.vY = _jugador->getY();
            target.vZ = _jugador->getZ();
            target.modulo = sqrt(pow(posActual.x - target.vX, constantes.DOS) + pow(posActual.y - target.vY, constantes.DOS) + pow(posActual.z - target.vZ, constantes.DOS));

            this->alinearse(&target, false);
        }
        if(porcentajeVelocidad != constantes.PORC_VELOCIDAD_EMBESTIR)
        {
            porcentajeVelocidad = constantes.PORC_VELOCIDAD_EMBESTIR;
        }
        datosDesplazamiento.vX = vectorOrientacion.vX* velocidadMaxima * porcentajeVelocidad;
        datosDesplazamiento.vZ = vectorOrientacion.vZ* velocidadMaxima * porcentajeVelocidad;

        if(_fisicas->enemyCollideObstacle(constantes.CERO) || _fisicas->enemyCollideParedesRompibles(constantes.CERO))
        {
            this->setTimeAt(0);
            this->setLastTimeAt(0);
            this->setNewPosiciones(posFutura.x - (datosDesplazamiento.vX * constantes.DOS), posFutura.y, posFutura.z - (datosDesplazamiento.vZ * constantes.DOS));
            this->setPosicionesFisicas(-(datosDesplazamiento.vX * constantes.DOS), constantes.CERO, -(datosDesplazamiento.vZ * constantes.DOS));
            paredRota = _fisicas->enemyCollideAttackWall(constantes.CERO);
        }
        else
        {
            this->setNewPosiciones(posFutura.x + datosDesplazamiento.vX, posFutura.y, posFutura.z + datosDesplazamiento.vZ);
            this->setPosicionesFisicas(datosDesplazamiento.vX, constantes.CERO, datosDesplazamiento.vZ);
        }
    }

    void Enemigo::ataqueRebote(bool modificarDireccion, int* _jug)
    {
        Constantes constantes;
        Jugador* _jugador = (Jugador*) _jug;
        VectorEspacial velocidad, posiciones, target, datosDesplazamiento;
        int* destino = _fisicas->ObtenerNormalColision(posPasada.x, posPasada.y, posPasada.z, rotActual.y + constantes.PI_MEDIOS);
        if(modificarDireccion)
        {
            target.vX = _jugador->getX();
            target.vY = _jugador->getY();
            target.vZ = _jugador->getZ();
            target.modulo = sqrt(pow(posActual.x - target.vX, constantes.DOS) + pow(posActual.y - target.vY, constantes.DOS) + pow(posActual.z - target.vZ, constantes.DOS));

            this->alinearse(&target, false);
        }
        else if(destino)
        {
            if(_fisicas->enemyCollideObstacle(constantes.CERO) || _fisicas->enemyCollideParedesRompibles(constantes.CERO))
            {
                int* destino = _fisicas->ObtenerNormalColision(posPasada.x, posPasada.y, posPasada.z, rotActual.y + constantes.PI_MEDIOS);
                if(!destino)
                {
                    destino = _fisicas->ObtenerNormalColision(posPasada.x, posPasada.y, posPasada.z, rotActual.y + constantes.PI_MEDIOS + constantes.PI_CUARTOS);
                    if(!destino)
                    {
                        destino = _fisicas->ObtenerNormalColision(posPasada.x, posPasada.y, posPasada.z, rotActual.y + constantes.PI_MEDIOS - constantes.PI_CUARTOS);
                    }
                }
                
                //Creamos un vector con una nueva direccion normalizando el vector director anterior
                VectorEspacial vectorDirector = this->normalizarVector(destino);
                //Se suma la normal del obstaculo aplicando pesos a la normal y al vector director
                if(vectorDirector.modulo != constantes.CERO)
                {
                    this->modificarTrayectoria(&vectorDirector, destino); 
                    //esto es para que gire hacia atras ya que al valor que devuelve atan hay que darle la vuelta 180
                    vectorDirector.vZ < 0 ?
                        rotation = (constantes.PI_RADIAN + (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ))):
                        rotation = (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ));
                }

                this->setNewRotacion(rotActual.x, rotation, rotActual.z);
                this->setVectorOrientacion();
                paredRota = _fisicas->enemyCollideAttackWall(constantes.CERO);
            }

        }
        if(porcentajeVelocidad != constantes.PORC_VELOCIDAD_ATREBOTE)
        {
            porcentajeVelocidad = constantes.PORC_VELOCIDAD_ATREBOTE;
        }
        datosDesplazamiento.vX = vectorOrientacion.vX* velocidadMaxima * porcentajeVelocidad;
        datosDesplazamiento.vZ = vectorOrientacion.vZ* velocidadMaxima * porcentajeVelocidad;

        this->setNewPosiciones(posFutura.x + datosDesplazamiento.vX, posFutura.y, posFutura.z + datosDesplazamiento.vZ);
        this->setPosicionesFisicas(datosDesplazamiento.vX, constantes.CERO, datosDesplazamiento.vZ);
        delete destino;
        destino = nullptr;
    }

    bool Enemigo::buscar(VectorEspacial* objetivo)
    {
        bool funciona = true;
        VectorEspacial datosDesplazamiento;
        float distancia = 4.0f;

        this->alinearse(objetivo, false);

        datosDesplazamiento.vX = vectorOrientacion.vX* velocidadMaxima * porcentajeVelocidad;
        datosDesplazamiento.vZ = vectorOrientacion.vZ* velocidadMaxima * porcentajeVelocidad;

        this->setNewPosiciones(posFutura.x + datosDesplazamiento.vX, posFutura.y, posFutura.z + datosDesplazamiento.vZ);
        this->setPosicionesFisicas(datosDesplazamiento.vX, constantes.CERO, datosDesplazamiento.vZ);

        //Se comprueba si la distancia entre el enemigo y el jugador es menor o igual a la distancia maxima que que indica la variable "distancia"
        if(abs(objetivo->vZ - this->getZ()) <= abs(distancia))
        {
            if(abs(objetivo->vX - this->getX()) <= abs(distancia))
            {
                funciona = true;
            }
            else
            {
                funciona = false;
            }
        }
        else
        {
            funciona = false;
        }
        return funciona;
    }

    bool Enemigo::PedirAyuda(bool ayuda)
    {
        //Comprueba si ya se esta respondiendo a la peticion de algun enemigo
        if(!ayuda)
        {
            //cout << "\e[42m Pide ayuda ID:\e[0m" <<id<< endl;
            //vamos a generar un sonido de ayuda
            generarSonido(90,2,2); //un sonido que se propaga en 0.500 ms, 2 significa que es un grito de ayuda
            SetPedirAyuda(true); //En caso de no estar buscando a ningun aliado se anade este como peticionario
            return true;
        }
        return false;
    }

    void Enemigo::AnnadirRecorridoAyuda(vector <Posiciones> recorrido)
    {
        if(recorrido.size() > 0)
        {
            recorridoAyuda = recorrido;
            modo = MODO_AUXILIAR_ALIADO;
        }
    }

    void Enemigo::ResetTree()
    {
        arbol->ResetTree();
    }

    bool Enemigo::ContestarAyuda()
    {
        //vamos a generar un sonido de ayuda
        generarSonido(10,5.750,3); //un sonido que se propaga en 0.500 ms, 2 significa que es un grito de ayuda
        //if(_motor->getPathfindingActivado()){
        SetContestar(true);//Jugando::updateRecorridoPathfinding(this);//se llama al pathfinding y se pone en cola al enemigo que responde a la peticion de ayuda
        //}
        //cout << " contesta a la llamada de auxilio ID:"<<id<< endl;

        return true;
    }

    void Enemigo::AuxiliarAliado()
    {
        float distancia = 5;
        VectorEspacial objetivo;
        objetivo.vX = recorridoAyuda.front().x;
        objetivo.vY = recorridoAyuda.front().y;
        objetivo.vZ = recorridoAyuda.front().z;
        objetivo.modulo = 0;
        this->buscar(&objetivo);
        if(abs(objetivo.vZ - this->getZ()) <= abs(distancia))
        {
            if(abs(objetivo.vX - this->getX()) <= abs(distancia))
            {
                recorridoAyuda.erase(recorridoAyuda.begin());
                if(recorridoAyuda.empty())
                {
                    modo = MODO_ATAQUE;
                }
            }
        }
    }

    bool Enemigo::Merodear(short int* _n)
    {
        VectorEspacial datosDesplazamiento, posiciones;

        if(_fisicas->enemyCollideObstacle((unsigned) *_n) || _fisicas->enemyCollideParedesRompibles((unsigned) *_n))
        {
            int* destino = _fisicas->ObtenerNormalColision(posPasada.x, posPasada.y, posPasada.z, rotActual.y + constantes.PI_MEDIOS);
            if(!destino)
            {
                destino = _fisicas->ObtenerNormalColision(posPasada.x, posPasada.y, posPasada.z, rotActual.y + constantes.PI_MEDIOS + constantes.PI_CUARTOS);
                if(!destino)
                {
                    destino = _fisicas->ObtenerNormalColision(posPasada.x, posPasada.y, posPasada.z, rotActual.y + constantes.PI_MEDIOS - constantes.PI_CUARTOS);
                }
            }
            
            //Creamos un vector con una nueva direccion normalizando el vector director anterior
            VectorEspacial vectorDirector = this->normalizarVector(destino);
            //Se suma la normal del obstaculo aplicando pesos a la normal y al vector director
            if(vectorDirector.modulo != constantes.CERO)
            {
                this->modificarTrayectoria(&vectorDirector, destino); 
                //esto es para que gire hacia atras ya que al valor que devuelve atan hay que darle la vuelta 180
                vectorDirector.vZ < 0 ?
                    rotation = (constantes.PI_RADIAN + (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ))):
                    rotation = (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ));
            }
            this->setNewRotacion(rotActual.x, rotation, rotActual.z);
            this->setVectorOrientacion();
        }
        else
        {
            if(pesoRotacion != constantes.UN_TERCIO)
            {
                pesoRotacion = constantes.UN_TERCIO;
            }
            this->ver(constantes.DOS, constantes.CINCO * constantes.CINCO);

            this->setNewRotacion(rotActual.x, rotActual.y + rotation, rotActual.z);
            this->setVectorOrientacion();
            if(rotation > maxRotacion)
            {
                rotation = maxRotacion;
            }
            datosDesplazamiento.vX = vectorOrientacion.vX* velocidadMaxima * porcentajeVelocidad;
            datosDesplazamiento.vZ = vectorOrientacion.vZ* velocidadMaxima * porcentajeVelocidad;

            this->setNewPosiciones(posFutura.x + datosDesplazamiento.vX, posFutura.y, posFutura.z + datosDesplazamiento.vZ);
            this->setPosicionesFisicas(datosDesplazamiento.vX, constantes.CERO, datosDesplazamiento.vZ);
        }

	    return false;
    }
    /********************************** Moverse ********************************
     * Funcion a la que llama el boss para desplazarse por la sala mientras
     * pelea contra el jugador.
     *
     *      Entradas:
     *                  int nuevaDireccion: direccion que probablemente tomara
     *                  int direccion: direccion actual del boss
     *                  int* _jug: entero que contiene el puntero del jugador
     *                  int maxDistBossJugador: distancia maxima con el jugador
     *
     *      Salidas:
     *                  int direccion: la direccion que al final toma el boss
    */
    int Enemigo::Moverse(int nuevaDireccion, int direccion, int* _jug, int minDistBossJugador, int maxDistBossJugador, bool* seAcerca)
    {
        Constantes constantes;
        Jugador* _jugador = (Jugador*) _jug;
        VectorEspacial velocidad, posiciones, target;
        target.vX = _jugador->getX();
        target.vY = _jugador->getY();
        target.vZ = _jugador->getZ();
        target.modulo = sqrt(pow(posActual.x - target.vX, constantes.DOS) + pow(posActual.y - target.vY, constantes.DOS) + pow(posActual.z - target.vZ, constantes.DOS));

        //Si el enemigo se estaba acercando y ahora no esta muy alejado del jugador, deja de acercarse
        if(abs(target.modulo) < minDistBossJugador && *seAcerca)
        {
            *seAcerca = false;
        }
        //Tras calcular la distancia con el jugador, determinamos si el enemigo esta muy lejos para acercarlo o no
        //En este caso no esta lo sufciciente lejos para obligarlo a acercarse al jugador
        if(abs(target.modulo) < maxDistBossJugador && !*seAcerca)
        {
            //Si colisiona con la pared el BOSS se mueve en el sentido contrario
            if(_fisicas->enemyCollideObstacle(constantes.CERO) || _fisicas->enemyCollideParedesRompibles(constantes.CERO))
            {
                direccion -= constantes.CUATRO;
                if(direccion <= 0)
                {
                    direccion += constantes.OCHO;
                }
            }
            //Si hay nueva direccion 
            else if(nuevaDireccion > 0)
            {
                //Si la nueva direccion es distinta de la ya establecida, esta se sustituye con la nueva
                if(nuevaDireccion != direccion)
                {
                    direccion = nuevaDireccion;
                }
                //Si no es distinta, la establecida se modifica en +90º
                else
                {
                    direccion -= constantes.DOS;
                    //Si el marcador de la direccio es menor que 1 se le suma 8
                    if(direccion <= 0)
                    {
                        direccion += constantes.OCHO;
                    }
                }
            }

            //Se obtiene la nueva rotation en funcion de la direccion establecida
            switch(direccion)
            {
                case 1:
                    rotation = constantes.DOS_PI_RADIAN;
                    break;

                case 2:
                    rotation = constantes.PI_TRES_MEDIOS_CUARTOS;
                    break;

                case 3:
                    rotation = constantes.PI_TRES_MEDIOS;
                    break;

                case 4:
                    rotation = constantes.PI_RADIAN_CUARTOS;
                    break;

                case 5:
                    rotation = constantes.PI_RADIAN;
                    break;

                case 6:
                    rotation = constantes.PI_MEDIOS_CUARTOS;
                    break;

                case 7:
                    rotation = constantes.PI_MEDIOS;
                    break;

                case 8:
                    rotation = constantes.PI_CUARTOS;
                    break;

                default:
                    rotation = constantes.PI_MEDIOS;
                    break;
            }
        }
        //En este caso si esta lo sufciciente lejos para obligarlo a acercarse al jugador por lo que
        //ponemos a TRUE que se acerca y alineamos el movimiento del BOSS para que se acerque al jugador
        else
        {
            *seAcerca = true;
            this->alinearse(&target, false);
        }

        //Si no se acerca, se establece la rotacion determinada por la nueva direccion del movimiento para
        //desplazar al BOSS
        if(!*seAcerca)
        {
            this->setNewRotacion(rotActual.x, rotation, rotActual.z);
            this->setVectorOrientacion();
        }
      
        //Se establece que el BOSS se mueva con la mitad de su velocidad maxima
        if(porcentajeVelocidad != constantes.UN_MEDIO)
        {
            porcentajeVelocidad = constantes.UN_MEDIO;
        }

        velocidad.vX = vectorOrientacion.vX* velocidadMaxima * porcentajeVelocidad;
        velocidad.vZ = vectorOrientacion.vZ* velocidadMaxima * porcentajeVelocidad;
        
        posiciones.vX = posFutura.x + velocidad.vX;
        posiciones.vZ = posFutura.z + velocidad.vZ;
        this->setPosicionesFisicas(velocidad.vX, 0.0f, velocidad.vZ);
        
        if(!*seAcerca)
        {
            this->alinearse(&target, false);
            this->setRotacion(rotActual.x, rotation, rotActual.z);
        }
        this->setLastRotacion(rotActual.x, rotation, rotActual.z);
        this->setNewPosiciones(posiciones.vX, posFutura.y, posiciones.vZ);
	    
        return direccion;
    }
    INnpc::VectorEspacial Enemigo::normalizarVector(int* destino)
    {
        //Se obtiene el vector director del movimiento del enemigo y su modulo
        VectorEspacial vectorDirector;
        if(destino)
        {
            vectorDirector.vX = destino[0] - posPasada.x;
            vectorDirector.vY = destino[1] - posPasada.y;
            vectorDirector.vZ = destino[2] - posPasada.z;
            vectorDirector.modulo = sqrt(pow(vectorDirector.vX, constantes.DOS) + pow(vectorDirector.vY, constantes.DOS) + pow(vectorDirector.vZ, constantes.DOS));

            //Se normaliza el vector director del movimiento del enemigo
            vectorDirector.vX /= vectorDirector.modulo;
            vectorDirector.vY /= vectorDirector.modulo;
            vectorDirector.vZ /= vectorDirector.modulo;
            vectorDirector.modulo = sqrt(pow(vectorDirector.vX, constantes.DOS) + pow(vectorDirector.vY, constantes.DOS) + pow(vectorDirector.vZ, constantes.DOS));
        }


        //vectorDirector.vX *= 0.75;
        //vectorDirector.vY *= 0.75;
        //vectorDirector.vZ *= 0.75;
        return vectorDirector;
    }

    //TO DO vectorDirector = colision + normal * distanciaEsquivar
    void Enemigo::modificarTrayectoria(INnpc::VectorEspacial* vectorDirector, int* destino)
    {
        Constantes constantes;
        //Se obtiene la nueva direccion del movimiento sumando las componentes de la normal del obstaculo con las del vector director
        //En caso de girar 180 grados, se multiplica por -1 la coordenada del vector que se acerque a +-1
        /*vectorDirector->vX = vectorDirector->vX * contraRotacion + (destino[3] * distanciaMinimaEsquivar) * pesoRotacion;
        vectorDirector->vY = vectorDirector->vY * contraRotacion + (destino[4] * distanciaMinimaEsquivar) * pesoRotacion;
        vectorDirector->vZ = vectorDirector->vZ * contraRotacion + (destino[5] * distanciaMinimaEsquivar) * pesoRotacion;
        vectorDirector->modulo = 1;*/
        if(abs(destino[3]) == constantes.UNO)
        {
            vectorDirector->vX *= -constantes.CIEN;
        }
        else
        {
            vectorDirector->vX *= constantes.CIEN;
        }
        
        if(abs(destino[4]) == constantes.UNO)
        {
            vectorDirector->vY *= -constantes.CIEN;
        }
        else
        {
            vectorDirector->vY *= constantes.CIEN;
        }
        
        if(abs(destino[5]) == constantes.UNO)
        {
            vectorDirector->vZ *= -constantes.CIEN;
        }
        else
        {
            vectorDirector->vZ *= constantes.CIEN;
        }

        float div = (float)__gcd((int)abs(vectorDirector->vX),(int)abs(vectorDirector->vZ));

        if(div != 1.0 && div != 0.0)
        {
            vectorDirector->vX /= div;
            vectorDirector->vZ /= div;
        }
    }

    bool Enemigo::comprobarDistanciaFlocking()
    {
        if(posicionComunBandada.vX != INT_MAX)
        {
            VectorEspacial vectorDistancia;
            vectorDistancia.vX = posicionComunBandada.vX - posActual.x;
            vectorDistancia.vY = posicionComunBandada.vY - posActual.y;
            vectorDistancia.vZ = posicionComunBandada.vZ - posActual.z;
            vectorDistancia.modulo = sqrt(pow(vectorDistancia.vX, constantes.DOS) + pow(vectorDistancia.vY, constantes.DOS) + pow(vectorDistancia.vZ, constantes.DOS));
            if(vectorDistancia.modulo > distanciaMaximaCohesionBandada)
            {
                return true;
            }
            else return false;
        }
        return false;
    }

//fin comportamientos bases

const char* Enemigo::GetModelo()
{
    return _modelo;
}

const char* Enemigo::GetTextura()
{
    return _textura;
}

unsigned int Enemigo::GetFps()
{
    return fps;
}

const char* Enemigo::GetAnimacion()
{
    return _animacion;
}

bool Enemigo::GetPedirAyuda()
{
    return pedirAyuda;
}

void Enemigo::SetPedirAyuda(bool ayu)
{
    pedirAyuda = ayu;
}

bool Enemigo::GetContestar()
{
    return contestar;
}

void Enemigo::SetContestar(bool contesta)
{
    contestar = contesta;
}


void Enemigo::SetParedRota(int idPared)
{
    paredRota = idPared;
}

int Enemigo::GetParedRota()
{
    return paredRota;
}

int Enemigo::GetTipoEnemigo()
{
    return tipoEnemigo;
}

void Enemigo::Render(short posArray,
    float updTime, float drawTime)
{
    moverseEntidad(1 / updTime);
    UpdateTimeMove(drawTime);
    RotarEntidad(1 / updTime);
    UpdateTimeRotate(drawTime);

    _motor->mostrarEnemigos(
        posActual.x, posActual.y, posActual.z,
        rotActual.x, rotActual.y, rotActual.z,
        posArray
    );

    _motor->UpdateBoardsVidaEne(posArray,vida,vidaIni);

    _motor->dibujarObjetoTemporal(
        posActual.x, posActual.y, posActual.z,
        rotActual.x, rotActual.y, rotActual.z,
        3, 3, 3, 2
    );
}

void Enemigo::RenderAtaque()
{
    _motor->dibujarObjetoTemporal(
        atx, aty, atz,
        rotActual.x, rotActual.y, rotActual.z,
        4, 4, 4, 2
    );
}
void Enemigo::BorrarEnemigos(unsigned short n)
{
    _motor->EraseEnemigo(n);
    _fisicas->EraseEnemigo(n);
}

unsigned int Enemigo::GetEstadoMuerte()
{
    return estadoMuerte;
}
