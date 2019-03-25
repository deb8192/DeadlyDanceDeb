#include "Enemigo.hpp"
#include "Pollo.hpp"
#include "Murcielago.hpp"
#include "MuerteBoss.hpp"
#include "Guardian.hpp"
#include "../ConstantesComunes.hpp"
#include "../Personajes/Jugador.hpp"
#include "cmath"
#include "../Motores/MotorFisicas.hpp"

Enemigo::Enemigo()
{
    _tiempo = Times::GetInstance();
    _motora = MotorAudioSystem::getInstance();
    _motor = MotorGrafico::GetInstance();
    _eventos = SenseEventos::getInstance();

    tiempoMerodear = 0.0f;
    lastTiempoMerodear = 0.0f;
    vectorOrientacion.vX = 0.0f;
    vectorOrientacion.vY = 0.0f;
    vectorOrientacion.vZ = 0.0f;
    vectorOrientacion.modulo = 0.0f;
    modo = MODO_DEFAULT;
    atacktime = 0.0f;
    pedirAyuda = false;
    contestar = false;
    distanciaMinimaEsquivar = 3;

    posicionComunBandada.vX = INT_MAX;
    posicionComunBandada.vY = INT_MAX;
    posicionComunBandada.vZ = INT_MAX;

    distanciaMaximaCohesionBandada = 10;

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

    /*ancho = anchoN;
    largo = largoN;
    alto = altoN;

    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    _fisicas->crearCuerpo(accion,nX/2,nY/2,nZ/2,2,ancho,alto,largo,2);
    _fisicas->crearCuerpo(0,     nX/2,nY/2,nZ/2,2,5,5,5,7); //Para ataques
    _fisicas->crearCuerpo(0,     nX/2,nY/2,nZ/2,2,5,5,5,8); //Para ataques especiales
    _fisicas = nullptr;*/
}

Enemigo::~Enemigo()
{
    //Punteros a clases singleton
    _tiempo = nullptr;
    _motora = nullptr;
    _motor = nullptr;
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
    atacktime = 0;
    velocidadMaxima = 0;
    porcentajeVelocidad = 0;
    pesoRotacion = 0;
    tipoEnemigo = 0;
    pos_ataques = 0;
    accionRealizada = false;
    contestar = false;
    distanciaMinimaEsquivar = 0;

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

float Enemigo::GetRotation()
{
    return rotation;
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

Sala* Enemigo::getSala()
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
            default:
            {
                MuerteBoss* _boss = (MuerteBoss*) this;
                _boss->RunIA();
            }
                break;
        }
    }
}

void Enemigo::UpdateBehavior(short *i, int* _jugador, 
    std::vector<Zona*> &_getZonas, bool ayuda)
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
                murcielago->UpdateMurcielago(i, _jugador, _getZonas);
            }
                break;
            case 3:
            {
                Guardian *guardian = (Guardian*) this;
                guardian->RunIA();
                guardian->UpdateGuardian(i, _jugador, _getZonas);
            }
                break;
            case 4:
            {
                Guardian *guardian = (Guardian*) this;
                guardian->RunIA();
                guardian->UpdateGuardian(i, _jugador, _getZonas);
            }
                break;
            default:
            {
                MuerteBoss* _boss = (MuerteBoss*) this;
                _boss->UpdateMuerteBoss(_jugador);
            }
                break;
        }
    }
}

int Enemigo::Atacar(int i)
{
    Constantes constantes;
    float danyoF = 0.f, critico = 1.f;
    int danyo = 0, por10 = 10, por100 = 100;
    bool atacado = false;
    if(vida > 0 && atacktime == 0)
    {
        MotorFisicas* _fisicas = MotorFisicas::getInstance();
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

        if (i >= 0) // Comprueba si ataca al boss o a los enemigos
        {
            //Acutualizar posicion del ataque
            _fisicas->updateAtaqueEnemigos(atposX,iniAtposY,atposZ,i);
            
            //Colision
            if(_fisicas->IfCollision(_fisicas->getEnemiesAtack(i),_fisicas->getJugador()))
            {
                atacado = true;
                cout << "Jugador Atacado" << endl;
            }
        }
        else
        {
            //Acutualizar posicion del ataque
            _fisicas->updateAtaqueBoss(atx/2,aty/2,atz/2);

            //Colision
            if(_fisicas->IfCollision(_fisicas->getBossAtack(),_fisicas->getJugador()))
            {
                atacado = true;
                cout << "Jugador Atacado por Boss" << endl;
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
        _fisicas = nullptr;
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
    Constantes constantes;
    float danyoF = 0.f, aumentosAtaque = 0.f, critico = 1.f;
    int danyo = 0, por10 = 10, por100 = 100;
    MotorFisicas* _fisicas = MotorFisicas::getInstance();

    cout << vida << " " << barraAtEs << " " << por100 << endl;
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
            _motora->getEvent("Arpa")->setVolume(0.8f);
            _motora->getEvent("Arpa")->start();
            _motor->dibujarObjetoTemporal(atespx, atespy, atespz, atgx, atgy, atgz, 4, 4, 4, 2);
        }

        //Se calcula el danyo del ataque
        //Se lanza un random y si esta dentro de la probabilidad de critico lanza un critico
        int probabilidad = rand() % por100 + 1;
        if(probabilidad <= proAtaCritico)
        {
            critico += (float) danyoCritico / por100;
            critico = roundf(critico * por10) / por10;
            cout<<"critico " << proAtaCritico << " " << critico <<endl;
        }

        //Se aplican todas las modificaciones en la variable danyo
        danyoF = ataque * critico * aumentosAtaque;
        cout << "daño: " <<danyoF<<endl;

        //Colision
        if(_fisicas->IfCollision(_fisicas->getEnemiesAtEsp(getPosAtaques()),_fisicas->getJugador()))
        {
            cout << "Jugador Atacado por ataque especial" << endl;
            danyo = roundf(danyoF * por10) / por10;
        }
        barraAtEs = 0;
        _fisicas = nullptr;
        return danyo;
    }
    else
    {
        barraAtEs += 1;
    }
    _fisicas = nullptr;
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
    _motora->getEvent("Chicken2")->setPosition(this->getX(),this->getY(),this->getZ());
    _motora->getEvent("Chicken2")->start();
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
    Constantes constantes;
    vida += vid;
    if(vid < 0)
    {
        if(tipoEnemigo == 3 || tipoEnemigo == 4)
        {
            if(vida <= vidaIni * constantes.UN_CUARTO)
            {
                modo = MODO_PELIGRO
            }
            else
            {
                modo = MODO_ATAQUE;
            }
        }
        else
        {
            modo = MODO_ATAQUE;
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

/*************** Modificar BarraAtEs *****************
 *  Funcion que actualiza la barra del ataque especial
 *  Entradas: 
 *      bar: valor en positivo o negativo
 *  Salidas:
 * 
 */
void Enemigo::ModificarBarraAtEs(int bar)
{
    /*barraAtEs += bar;
    if(barraAtEs < 0)
        barraAtEs = 0;
    if(barraAtEs > 100)
        barraAtEs = 100;*/
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
    Constantes constantes;
    _armaEspecial = new Arma(ataque, "",2,2,2,_rutaArmaEspecial,"",constantes.ARMA);
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

void Enemigo::setTimeAtEsp(float time)
{
    atackEspTime = time;
}

void Enemigo::setLastTimeAtEsp(float time)
{
    lastAtackEspTime = time;
}

void Enemigo::setSala(Sala* sala)
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
}

int Enemigo::getID()
{
    return id;
}

void Enemigo::setRotation(float rot)
{
    rotation = rot;
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
    Constantes constantes;
    vectorOrientacion.vX = sin(constantes.PI * rotFutura.y / constantes.PI_RADIAN);
    vectorOrientacion.vY = 0.0f;
    vectorOrientacion.vZ = cos(constantes.PI * rotFutura.y / constantes.PI_RADIAN);
}

void Enemigo::setTimeMerodear(float t)
{
    tiempoMerodear = t;
}

void Enemigo::setLastTimeMerodear(float t)
{
    lastTiempoMerodear = t;
}

void Enemigo::setAtackTime(float t)
{
  atacktime = t;
}

void Enemigo::SetEnemigo(int enemigo)
{
    tipoEnemigo = enemigo;
}

void Enemigo::SetModo(int newModo)
{
    modo = newModo;
}

void Enemigo::SetPosicionComunBandada(INnpc::VectorEspacial posicion)
{
    posicionComunBandada = posicion;
}

float Enemigo::getTimeMerodear()
{
    return tiempoMerodear;
}

float Enemigo::getLastTimeMerodear()
{
    return lastTiempoMerodear;
}

float Enemigo::getAtackTime()
{
  return atacktime;
}

float Enemigo::getTimeAt()
{
    return atackTime;
}

float Enemigo::getLastTimeAt()
{
    return lastAtackTime;
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

Zona* Enemigo::getZonaMasCercana(vector <Zona*> zonas, short enemigo)
{
    Constantes constantes;
    Zona* _zonaElegida = nullptr;
    VectorEspacial distanciaZonaActual, distanciaZonaElegida;
    vector<Zona*> zonasCompletas;
    zonasCompletas.reserve(zonas.size());

    unsigned short i = 0;
    while(i < zonas.size() && (_zonaElegida == nullptr || distanciaZonaElegida.modulo > 0.0f))
    {
        if(zonas.at(i) != nullptr && zonas.at(i)->getTipo() == Zona::tiposZona::Z_DARK)
        {
            distanciaZonaActual.vX = abs(zonas.at(i)->getX() - posActual.x);
            distanciaZonaActual.vY = abs(zonas.at(i)->getY() - posActual.y);
            distanciaZonaActual.vZ = abs(zonas.at(i)->getZ() - posActual.z);
            distanciaZonaActual.modulo = pow(distanciaZonaActual.vX, constantes.DOS) + pow(distanciaZonaActual.vY, constantes.DOS) + pow(distanciaZonaActual.vZ, constantes.DOS);
            distanciaZonaActual.modulo = sqrt(distanciaZonaActual.modulo);

            if(_zonaElegida == nullptr || distanciaZonaElegida.modulo > distanciaZonaActual.modulo)
            {
                distanciaZonaElegida = distanciaZonaActual;
                _zonaElegida = zonas.at(i);
            }
        }
        i++;
    }
    return _zonaElegida;
}
//ia

void Enemigo::setArbol(Arbol ia)
{
    arbol = new Arbol(ia.GetRaiz(), ia.GetRaiz()->getNombre());
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
                return ver(1);
            case 2://merodeo
                return Merodear();//merodeo pollo
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
        bool controlRotacion = false;
        if(modo == MODO_ATAQUE || modo == MODO_AUXILIAR_ALIADO)
        {
            pesoRotacion = 0.35f;
            contraRotacion = 1.0 - pesoRotacion;
            if(this->ver(constantes.TRES))
            {
                controlRotacion = true;
            }
        }
        else
        {
            pesoRotacion = 1.0f;
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
            rotation *= -1;
        }

        this->setNewRotacion(rotActual.x, rotation, rotActual.z);
        this->setVectorOrientacion();
    }

    bool Enemigo::ver(int tipo)
    {
        Constantes constantes;
        bool ve = false;
        short posicionArray = 0;
        int* loqueve = _eventos->listaObjetos(posActual.x, posActual.y, posActual.z,rotActual.y,30, tipo, true); //le pedimos al motor de sentidos que nos diga lo que vemos y nos devuelve una lista

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
                    
                    delete loqueve;
                    return true;
                }
            }
            delete loqueve;
        }
        if(tipo == 2)//ves algun objeto ?
        {
            int* destino = new int[6];
            if(loqueve != nullptr)
            {
                //Ve algo en la lejania de su visor central
                if(loqueve[0] == 1)
                {   
                    distanciaEnemigoObstaculo.vX = loqueve[1] - posActual.x;
                    distanciaEnemigoObstaculo.vY = loqueve[2] - posActual.y;
                    distanciaEnemigoObstaculo.vZ = loqueve[3] - posActual.z;
                    distanciaEnemigoObstaculo.modulo = sqrt(pow(distanciaEnemigoObstaculo.vX, constantes.DOS) + pow(distanciaEnemigoObstaculo.vY, constantes.DOS) + pow(distanciaEnemigoObstaculo.vZ, constantes.DOS));                
                    //Si entra aqui dentro es que detecta un obstaculo con su visor izquierdo
                    if(loqueve[7] == 1)
                    {
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

                            //Creamos un vector con una nueva direccion normalizando el vector director anterior y sumandole la normal del obstaculo
                            VectorEspacial vectorDirector = this->normalizarVector(destino);
                            //esto es para que gire hacia atras ya que al valor que devuelve atan hay que darle la vuelta 180
                            vectorDirector.vZ < 0 ?
                                rotation = constantes.PI_RADIAN + (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ)) :
                                rotation = constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ) ;
                            cout<<"COLISIONA POR DELANTE"<<endl;
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

                            //Creamos un vector con una nueva direccion normalizando el vector director anterior y sumandole la normal del obstaculo
                            VectorEspacial vectorDirector = this->normalizarVector(destino);
                            //esto es para que gire hacia atras ya que al valor que devuelve atan hay que darle la vuelta 180
                            vectorDirector.vZ < 0 ?
                                rotation = constantes.PI_RADIAN + (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ)) :
                                rotation = constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ) ;
                            cout<<"COLISIONA POR LA IZQUIERDA"<<endl;
                        }
                    }
                    //Si entra aqui dentro es que detecta un obstaculo con su visor derecho                    
                    else if(loqueve[14] == 1)
                    {
                        //Coordenadas del punto de obstaculo
                        destino[0] = loqueve[15];
                        destino[1] = loqueve[16];
                        destino[2] = loqueve[17];
                        //Valores del vector Normal
                        destino[3] = loqueve[18];
                        destino[4] = loqueve[19];
                        destino[5] = loqueve[20];

                        //Creamos un vector con una nueva direccion normalizando el vector director anterior y sumandole la normal del obstaculo
                        VectorEspacial vectorDirector = this->normalizarVector(destino);
                        //esto es para que gire hacia atras ya que al valor que devuelve atan hay que darle la vuelta 180
                        vectorDirector.vZ < 0 ?
                            rotation = constantes.PI_RADIAN + (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ)) :
                            rotation = constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ) ;
                        cout<<"COLISIONA POR LA DERECHA"<<endl;
                    }
                    //Si entra aquí es que los visores laterales no detectan nada pero si el visor central
                    //y el enemigo en cuestion esta muy cerca del obstaculo que debe esquivar
                    else if(distanciaEnemigoObstaculo.modulo <= distanciaMinimaEsquivar)
                    {
                        destino[0] = loqueve[1];
                        destino[1] = loqueve[2];
                        destino[2] = loqueve[3];
                        destino[3] = loqueve[4];
                        destino[4] = loqueve[5];
                        destino[5] = loqueve[6];

                        //Creamos un vector con una nueva direccion normalizando el vector director anterior y sumandole la normal del obstaculo
                        VectorEspacial vectorDirector = this->normalizarVector(destino);
                        //esto es para que gire hacia atras ya que al valor que devuelve atan hay que darle la vuelta 180
                        vectorDirector.vZ < 0 ?
                            rotation = constantes.PI_RADIAN + (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ)) :
                            rotation = constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ) ;
                        cout<<"QUE SE SALE"<<endl;
                    }
                    this->setNewRotacion(0.0f, rotation, 0.0f);
                    this->setVectorOrientacion();
                    delete loqueve;
                    return true;                    
                }
            }
            delete loqueve;
        }
        if(tipo == 3) //Ves algun enemigo?
        {
            bool obsPorDelante = false, colisiona = false;
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
                        if(porcentajeVelocidad >= 0.6)
                        {
                            porcentajeVelocidad *= 0.9;
                        }
                        obsPorDelante = true;
                    }
                    
                    
                    cout<<"VE AL ENEMIGO POR DELANTE"<<endl;
                    /*this->setNewRotacion(0.0f, rotActual.y, 0.0f);
                    this->setVectorOrientacion();
                    delete loqueve;
                    return true;*/                    
                }
                //Si entra aqui dentro es que detecta un obstaculo por delante con el visores izquierdo
                if(loqueve[7] == 1)
                {
                    if(!obsPorDelante && porcentajeVelocidad >= 0.6)
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

                            /*//Creamos un vector con una nueva direccion normalizando el vector director anterior y sumandole la normal del obstaculo
                            VectorEspacial vectorDirector = this->normalizarVector(destino);
                            //esto es para que gire hacia atras ya que al valor que devuelve atan hay que darle la vuelta 180
                            vectorDirector.vZ < 0 ?
                                rotation = (constantes.PI_RADIAN + (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ))) * pesoRotacion :
                                rotation = (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ)) * pesoRotacion ;
                        //}*/
                        
                        cout<<"COLISIONA CON ENEMIGO POR DELANTE"<<endl;
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
                        cout<<"COLISIONA CON ENEMIGO POR LA IZQUIERDA"<<endl;
                    }
                }
                //Si entra aqui dentro es que detecta un obstaculo con su visor derecho                    
                else if(loqueve[14] == 1)
                {
                    if(!obsPorDelante && porcentajeVelocidad >= 0.6)
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
                        
                        cout<<"COLISIONA CON ENEMIGO POR LA DERECHA"<<endl;
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
                //Creamos un vector con una nueva direccion normalizando el vector director anterior y sumandole la normal del obstaculo
                VectorEspacial vectorDirector = this->normalizarVector(destino);
                //esto es para que gire hacia atras ya que al valor que devuelve atan hay que darle la vuelta 180
                vectorDirector.vZ < 0 ?
                    rotation = (constantes.PI_RADIAN + (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ))) * pesoRotacion :
                    rotation = (constantes.RAD_TO_DEG * atan(vectorDirector.vX/vectorDirector.vZ)) * pesoRotacion ;
            }
            delete loqueve;
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
    //ESTO TAL CUAL SE PARECE MAS A BUSCAR, PERSEGUIR PREDICE LA RUTA DEL OBJETIVO DEL ENEMIGO
    bool Enemigo::perseguir(int* _jug)
    {
        Jugador* _jugador = (Jugador*)_jug;
        Constantes constantes;
        bool funciona = true;
        VectorEspacial datosDesplazamiento, objetivo;
        float distancia = 4.0f;

        if(comprobarDistanciaFlocking())
        {
            objetivo.vX = posicionComunBandada.vX;
            objetivo.vY = posicionComunBandada.vY;
            objetivo.vZ = posicionComunBandada.vZ;
        }
        else
        {
            objetivo.vX = _jugador->getX();
            objetivo.vY = _jugador->getY();
            objetivo.vZ = _jugador->getZ();
        }

        this->alinearse(&objetivo, false);

        datosDesplazamiento.vX = vectorOrientacion.vX * velocidadMaxima * porcentajeVelocidad;
        datosDesplazamiento.vZ = vectorOrientacion.vZ* velocidadMaxima * porcentajeVelocidad;

        if((abs(objetivo.vX - this->getX())) > abs(distancia) || (abs(objetivo.vZ - this->getZ()) > abs(distancia)))
        {
            this->setNewPosiciones(posFutura.x + datosDesplazamiento.vX, posFutura.y, posFutura.z + datosDesplazamiento.vZ);
            this->setPosicionesFisicas(datosDesplazamiento.vX, constantes.CERO, datosDesplazamiento.vZ);
        }
                
        //Se comprueba si la distancia entre el enemigo y el jugador es menor o igual a la distancia maxima que que indica la variable "distancia"
        if(abs(objetivo.vZ - this->getZ()) <= abs(distancia))
        {
            if(abs(objetivo.vX - this->getX()) <= abs(distancia))
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

    bool Enemigo::buscar(VectorEspacial* objetivo)
    {
        Constantes constantes;
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
            cout << "\e[42m Pide ayuda ID:\e[0m" <<id<< endl;
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

    bool Enemigo::ContestarAyuda()
    {
        //vamos a generar un sonido de ayuda
        generarSonido(10,5.750,3); //un sonido que se propaga en 0.500 ms, 2 significa que es un grito de ayuda
        //if(_motor->getPathfindingActivado()){
        SetContestar(true);//Jugando::updateRecorridoPathfinding(this);//se llama al pathfinding y se pone en cola al enemigo que responde a la peticion de ayuda
        //}
        cout << " contesta a la llamada de auxilio ID:"<<id<< endl;

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

    bool Enemigo::Merodear()
    {
        Constantes constantes;
        struct 
        {
            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;
        }
        velocidad, posiciones;
        this->setNewRotacion(rotActual.x, rotActual.y + rotation, rotActual.z);
        this->setVectorOrientacion();
        velocidad.x = vectorOrientacion.vX* velocidadMaxima * porcentajeVelocidad;
        velocidad.z = vectorOrientacion.vZ* velocidadMaxima * porcentajeVelocidad;
        posiciones.x = posFutura.x + velocidad.x;
        posiciones.z = posFutura.z + velocidad.z;

        this->setNewPosiciones(posiciones.x, posFutura.y, posiciones.z);
        this->setPosicionesFisicas(velocidad.x, 0.0f, velocidad.z);

	    return false;
    }
    INnpc::VectorEspacial Enemigo::normalizarVector(int* destino)
    {
        Constantes constantes;
        //Se obtiene el vector director del movimiento del enemigo y su modulo
        VectorEspacial vectorDirector;
        vectorDirector.vX = destino[0] - posActual.x;
        vectorDirector.vY = destino[1] - posActual.y;
        vectorDirector.vZ = destino[2] - posActual.z;
        vectorDirector.modulo = sqrt(pow(vectorDirector.vX, constantes.DOS) + pow(vectorDirector.vY, constantes.DOS) + pow(vectorDirector.vZ, constantes.DOS));

        //Se normaliza el vector director del movimiento del enemigo
        vectorDirector.vX /= vectorDirector.modulo;
        vectorDirector.vY /= vectorDirector.modulo;
        vectorDirector.vZ /= vectorDirector.modulo;
        
        //Se obtiene la nueva direccion del movimiento sumando las componentes de la normal del obstaculo con las del vector director
        vectorDirector.vX += destino[3];
        vectorDirector.vY += destino[4];
        vectorDirector.vZ += destino[5];
        vectorDirector.modulo = 1;

        return vectorDirector;
    }

    bool Enemigo::comprobarDistanciaFlocking()
    {
        Constantes constantes;
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

int Enemigo::GetTipoEnemigo()
{
    return tipoEnemigo;
}

void Enemigo::Render(short pos, 
    float updTime, float drawTime)
{
    moverseEntidad(1 / updTime);
    UpdateTimeMove(drawTime);
    RotarEntidad(1 / updTime);
    UpdateTimeRotate(drawTime);

    if (pos >= 0) // Enemigos
    {
        _motor->mostrarEnemigos(
            posActual.x, posActual.y, posActual.z,
            rotActual.x, rotActual.y, rotActual.z,
            pos
        );
    }
    else
    { // Boss
        _motor->mostrarBoss(
            posActual.x, posActual.y, posActual.z,
            rotActual.x, rotActual.y, rotActual.z
        );
    }

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