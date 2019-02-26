#include "Enemigo.hpp"
#include "Pollo.hpp"
#include "../Jugando/Jugando.hpp"
#include "../ConstantesComunes.hpp"

Enemigo::Enemigo()
{
    tiempoMerodear = 0.0f;
    lastTiempoMerodear = 0.0f;
    vectorOrientacion.vX = 0.0f;
    vectorOrientacion.vY = 0.0f;
    vectorOrientacion.vZ = 0.0f;
    vectorOrientacion.modulo = 0.0f;
    modo = MODO_DEFAULT;
}

Enemigo::Enemigo(float nX, float nY, float nZ)
{
    tiempoMerodear = 0.0f;
    lastTiempoMerodear = 0.0f;
    vectorOrientacion.vX = 0.0f;
    vectorOrientacion.vY = 0.0f;
    vectorOrientacion.vZ = 0.0f;
    vectorOrientacion.modulo = 0.0f;
    modo = MODO_DEFAULT;

    atacktime = 0.0f;
    posIni.x = nX;
    posIni.y = nY;
    posIni.z = nZ;
}

Enemigo::~Enemigo()
{
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
    tipoEnemigo = 0;
    pos_ataques = 0;
    accionRealizada = false;
    
    // INnpc
    tipo = 0;
    vida = 0;
    barraAtEs = 0;
    ataque = 0;
    suerte = 0;
    danyoCritico = 0;
    proAtaCritico = 0;
    //TO DO: int buffos[4];
    malla = "";
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
    SenseEventos* _eventos = SenseEventos::getInstance();
    _eventos->agregarEvento(_sonid);
}

void Enemigo::queEscuchas()
{
    SenseEventos* _eventos = SenseEventos::getInstance();
    std::vector<EventoSonido* > listaSonidos =  _eventos->listarSonidos(posActual.x, posActual.y);//le pasamos nuestra x e y
    //int cuantos = listaSonidos.size();
    //cout << "Esta escuchando " << cuantos << " sonidos" << endl;
}

void Enemigo::queVes()
{
    /*SenseEventos* _eventos = SenseEventos::getInstance();
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
    switch (tipoEnemigo)
    {
        case 0:
        {
            Pollo *pollo = (Pollo*) this;
            pollo->RunIA();
        }
            break;
        default:
            break;
    }
}

void Enemigo::UpdateBehavior(short *i)
{
    switch (tipoEnemigo)
    {
        case 0:
        {
            Pollo *pollo = (Pollo*) this;
            pollo->UpdatePollo(i);
        }
            break;
        default:
            break;
    }
}

int Enemigo::Atacar(int i)
{
    Constantes constantes;
    int danyo = 0;
    if(vida > 0 && atacktime == 0)
    {
      MotorFisicas* _fisicas = MotorFisicas::getInstance();
      //MotorAudioSystem* _motora = MotorAudioSystem::getInstance();

      //Calcular posiciones
      int distance = 4;
      atx = distance * sin(constantes.PI * this->getRY() / constantes.PI_RADIAN) + this->getX();
      aty = this->getY();
      atz = distance * cos(constantes.PI * this->getRY() / constantes.PI_RADIAN) + this->getZ();
      atgx = this->getRX();
      atgy = this->getRY();
      atgz = this->getRZ();

      //Acutualizar posicion del ataque
      _fisicas->updateAtaqueEnemigos(atx/2,aty/2,atz/2,i);

      //Colision
      if(_fisicas->IfCollision(_fisicas->getEnemiesAtack(i),_fisicas->getJugador()))
      {
        cout << "Jugador Atacado" << endl;
        danyo = 10.0f;
        cout << "danyo del enemigo -> " << danyo << endl;
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
    Constantes constantes;
    float danyoF = 0.f, aumentosAtaque = 0.f, critico = 1.f, por1 = 1.f;
    int danyo = 0, por10 = 10, por100 = 100;
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    MotorAudioSystem* _motora = MotorAudioSystem::getInstance();
    MotorGrafico* _motor = MotorGrafico::GetInstance();

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
        aumentosAtaque += (por1 * 2);
        aumentosAtaque = roundf(aumentosAtaque * por10) / por10;

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
        return danyo;
    }
    else
    {
        barraAtEs += 1;
    }
    return danyo;
}

void Enemigo::QuitarVida(int can)
{
    vida-=can;
}

bool Enemigo::estasMuerto(){
    //cout << "Muere enemigo??: " << vida << endl;
    if(vida <= 0){
        return true;
    }
    return false;
}

bool Enemigo::finalAnimMuerte(){
    Times* _tiempo = Times::GetInstance();
    if(_tiempo->CalcularTiempoPasado(tiempoPasadoMuerte) >= animacionMuerteTiem && tiempoPasadoMuerte != 0){//sino se cumple no ha acabado
        return true;
    }
    return false;
}

void Enemigo::MuereEnemigo(int enemi){
    Times* _tiempo = Times::GetInstance();
    MotorGrafico* _motor = MotorGrafico::GetInstance();
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
    MotorAudioSystem* _motora = MotorAudioSystem::getInstance();
    _motora->getEvent("Chicken2")->setPosition(this->getX(),this->getY(),this->getZ());
    _motora->getEvent("Chicken2")->start();
}

void Enemigo::RecuperarVida(int can)
{

}

void Enemigo::AumentarBarraAtEs(int can)
{
    barraAtEs += can;
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

void Enemigo::setVida(int vid)
{
    vida = vid;
}

void Enemigo::setTipo(int tip)
{

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
    _armaEspecial = new Arma(ataque, "",2,2,2,_rutaArmaEspecial,"");
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
//ia

void Enemigo::setArbol(Arbol ia)
{
    arbol = new Arbol(ia.GetRaiz(), ia.GetRaiz()->getNombre());
}

Arbol * Enemigo::getArbol()
{
    return arbol;
}

short int* Enemigo::RunIA(bool funciona)
{
    //aun por determinar primero definir bien la carga de arboles
    return arbol->ContinuarSiguienteNodo(funciona);//el true lo ponemos para detectar la primera ejecucion del bucle
    //bool salir = false;//cuando terminemos el arbol salimos
    /*while(!salir)
    {
        bool es = Acciones(accion);
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
    bool Enemigo::Acciones(int accion)
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
                return pedirAyuda();
            case 9://oye pedir ayuda enemigo ?
                return oir(2);
            case 10://contestacion a auxilio
                return ContestarAyuda();
        }

        return false;//cambiamos de rama si no se encuentra la tarea
    }

    bool Enemigo::ver(int tipo)
    {
        //vamos a  ver si vemos al jugador
        SenseEventos* _eventos = SenseEventos::getInstance();
        if(tipo == 1)//ves al jugador ?
        {
            int* loqueve = _eventos->listaObjetos(posActual.x, posActual.y, posActual.z,rotActual.y,20,1,true); //le pedimos al motor de sentidos que nos diga lo que vemos y nos devuelve una lista

            if(loqueve != nullptr)
            {
                if(loqueve[0] == 1)
                {
                    delete loqueve;
                    return true;
                }
            }

            delete loqueve;

        }

        return false;
    }

    bool Enemigo::oir(int tipo)//tipo 1 oir al jugador si lo oye true, tipo 2 si oye al enemigo pedir ayuda si lo oye true si no false
    {
        SenseEventos* _eventos = SenseEventos::getInstance();
        std::vector<EventoSonido* > listaSonidos =  _eventos->listarSonidos(posActual.x, posActual.y);//le pasamos nuestra x e y

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

    bool Enemigo::pedirAyuda()
    {
        Jugando* _nivel = Jugando::GetInstance();
        MotorGrafico* _motor = MotorGrafico::GetInstance();
        //Comprueba si ya se esta respondiendo a la peticion de algun enemigo
        if(_nivel->getEnemigoPideAyuda() == nullptr && _motor->getPathfindingActivado())
        {
            //vamos a generar un sonido de ayuda
            generarSonido(60,1.500,2); //un sonido que se propaga en 0.500 ms, 2 significa que es un grito de ayuda
            _nivel->setEnemigoPideAyuda(this); //En caso de no estar buscando a ningun aliado se anade este como peticionario
            return true;
        }
        //cout << " grita pidiendo ayuda "<< endl;
        return false;
    }

    bool Enemigo::ContestarAyuda()
    {
        //vamos a generar un sonido de ayuda
        generarSonido(10,5.750,3); //un sonido que se propaga en 0.500 ms, 2 significa que es un grito de ayuda
        MotorGrafico* _motor = MotorGrafico::GetInstance();
        if(_motor->getPathfindingActivado()){
            Jugando* _nivel = Jugando::GetInstance();
            _nivel->updateRecorridoPathfinding(this);//se llama al pathfinding y se pone en cola al enemigo que responde a la peticion de ayuda
        }
        //cout << " contesta a la llamada de auxilio "<< endl;

        return true;
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
        velocidad.x = vectorOrientacion.vX * velocidadMaxima;
        velocidad.z = vectorOrientacion.vZ * velocidadMaxima;
        posiciones.x = posFutura.x + velocidad.x;
        posiciones.z = posFutura.z + velocidad.z;

        this->setNewPosiciones(posiciones.x, posFutura.y, posiciones.z);
        this->setPosicionesFisicas(velocidad.x, 0.0f, velocidad.z);

	    return false;
    }

//fin comportamientos bases
