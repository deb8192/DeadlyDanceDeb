#include "Jugador.hpp"
#include <stdlib.h>
#include "../Times.hpp"

Jugador::Jugador()
{
    _motor = MotorGrafico::GetInstance();
    _motora = MotorAudioSystem::getInstance();
    _interfaz = InterfazJugador::getInstance();
    _fisicas = MotorFisicas::getInstance();

    invulnerabilidad = false; 
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
    
    //tiempos de ejecucion de acciones
    atackTime = 0.0f;
    atackEspTime = 0.0f;
    painAtackTime = 0.0f;
    lastAtackTime = 0.0f;
    lastAtackEspTime = 0.0f;
    lastPainAtackTime = 0.0f;
    velocidadMaxima = 2.5f;
    porcentajeVelocidad = 1.0f;
}

Jugador::Jugador(Sala* sala, unsigned short tipoJug, int nX,int nY,int nZ, int ancho,
    int largo, int alto, int accion, int maxVida)
: Jugador()
{
    _fisicas->crearCuerpo(accion,nX/2,nY/2,nZ/2,3,2,2,2,1,0,0,false);//creamos el cuerpo y su espacio de colisiones en el mundo de las fisicas

    this->tipoJug = tipoJug;
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

    posPasada.x = nX;
    posPasada.y = nY;
    posPasada.z = nZ;

    posFutura.x = nX;
    posFutura.y = nY;
    posFutura.z = nZ;

    salaActual = sala;
}

Jugador::~Jugador()
{
    _motor = nullptr;
    _motora = nullptr;
    _interfaz = nullptr;
    _fisicas = nullptr;

    _armaEquipada = nullptr;
    _armaEspecial = nullptr;

    _rutaArmaEspecial = nullptr;
    _rutaTexturaArmaEspecial = nullptr;

    dinero = 0;

    invulnerabilidad = false; 

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
    painAtackTime = 0;
    lastAtackTime = 0;
    lastAtackEspTime = 0;
    lastPainAtackTime = 0;
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
    velocidadMaxima = 0;
    porcentajeVelocidad = 0;

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

    salaActual = nullptr;
}

void Jugador::movimiento(bool noMueve,bool a, bool s, bool d, bool w)
{
    struct
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    }
    velocidad, posiciones;

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
        deg = constantes.RAD_TO_DEG * atan(ax/az) ;

    if((w || s || a || d) && !noMueve)
    {
        //TO DO  poner un evento para correr
        /*if(shift)
        {
            porcentajeVelocidad = constantes.UNO;
        }
        else*/
        porcentajeVelocidad = constantes.DOS_TERCIOS;
    }
    else
    {
        porcentajeVelocidad = 0.0;
    }
    //getGir se utiliza para orientar al jugador cuando se gira la camara
    deg -= gcam;

    setNewRotacion(rotActual.x, deg, rotActual.z);
    setVectorOrientacion();

    velocidad.x = vectorOrientacion.vX* velocidadMaxima * porcentajeVelocidad;
    velocidad.z = vectorOrientacion.vZ* velocidadMaxima * porcentajeVelocidad;
    posiciones.x = posFutura.x + velocidad.x;
    posiciones.z = posFutura.z + velocidad.z;

    //ahora actualizas movimiento y rotacion
    setNewPosiciones(posiciones.x, posActual.y, posiciones.z);
}

/*************** moverseEntidad *****************
 * Funcion con la que el jugador se desplazaran
 * por el escenario mediante una interpolacion desde
 * el punto de origen al punto de destino
 */

void Jugador::girarCamara()
{
    gcam >= 270 ? gcam = 0 : gcam += 90;
}

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
    else if(pt < 0.0f)
    {
        pt = 0.0f;
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
    float danyoF = 0.f, aumentosAtaque = 0.f, critico = 1.f, por1 = 1.f;
    int danyo = 0, por10 = 10, por100 = 100;
    if(vida > 0)
    {
        //Calcular posiciones que no se modifican
        int distance = 2;
        if(this->getArma() == nullptr)distance= 1;
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
            _fisicas->crearCuerpo(0,atposX,atposY,atposZ,2,3,3,3,4,0,0,false);
            _motora->getEvent("SinArma")->start();
        }
        else //ATAQUE CUERPO A CUERPO
        {
            unsigned short tipoArma = this->getArma()->GetTipoObjeto();
            if ((tipoArma == constantes.GUITARRA1) || (tipoArma == constantes.GUITARRA2) ||
                (tipoArma == constantes.GUITARRA3))
            {
                //Crear cuerpo de colision de ataque delante del jugador
                _fisicas->crearCuerpo(0,atposX,atposY,atposZ,1,5,0,0,4,0,0,false);
                _motora->getEvent("GolpeGuitarra")->start();
            }
            //ATAQUE A DISTANCIA
            else if ((tipoArma == constantes.ARPA1) || (tipoArma == constantes.ARPA2) ||
                (tipoArma == constantes.ARPA3))
            {
                _motor->CargarProyectil(getX(),getY(),getZ(),"assets/models/Flecha.obj","assets/texture/flecha.png");
                //Crear cuerpo de colision de ataque delante del jugador
                _fisicas->crearCuerpo(0,atposX,atposY,atposZ,2,2,0.5,1,4,0,0,false);
                _motora->getEvent("Arpa")->start();
            }
            //ATAQUE A MEDIA DISTANCIA
            else if ((tipoArma == constantes.FLAUTA1) || (tipoArma == constantes.FLAUTA2) ||
                (tipoArma == constantes.FLAUTA3))
            {
                tamanyoflecha = 1.0;
                aty = getY()+4;
                atposY = ((getY()+4)/2);
                _motor->CargarProyectil(getX(),getY(),getZ(),"assets/models/Onda.obj","assets/texture/Aire.png",true);
                //Crear cuerpo de colision de ataque delante del jugador
                _fisicas->crearCuerpo(0,atposX,atposY,atposZ,1,tamanyoflecha*2,0,0,4,0,0,false);
                _motora->getEvent("Flauta")->start();
            }
        }

        //Se calcula el danyo del ataque
        aumentosAtaque += por1;
        if(_armaEquipada != NULL)
        {
            aumentosAtaque += (float) _armaEquipada->getAtaque() / por100;// + (float) variacion / 100;
        }
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
        atacados_normal.clear(); //Reiniciar vector con enemigos atacados
    }
    return danyo;
}

/*************** AtacarEspecial *****************
 *  Funcion que inicia la ejecucion del ataque
 *  especial del jugador si la barra de ataque
 *  especial esta completa y se pulsa el boton Q /
 *  click derecho del raton.
 *      Entradas:
 *      Salidas: int danyo;
 */

int Jugador::GetTipoJug()
{
    return tipoJug;
}
int Jugador::AtacarEspecial()
{
    float danyoF = 0.f, aumentosAtaque = 0.f, critico = 1.f, por1 = 1.f;
    int danyo = 0, por10 = 10, por100 = 100;

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
            if(tipoJug == constantes.HEAVY)
            {
                //Crear cuerpo de colision de ataque delante del jugador
                _fisicas->crearCuerpo(0,
                    _armaEspecial->getFisX(),_armaEspecial->getFisY(),_armaEspecial->getFisZ(),
                    2,8,1,8,5,0,0,false);
                _motora->getEvent("GuitarraEspecial")->start();
            }
            //ATAQUE ESPECIAL DE LA BAILAORA (castanyuelas)
            else if(tipoJug == constantes.BAILAORA)
            {
                //Crear cuerpo de colision de ataque delante del jugador
                _fisicas->crearCuerpo(0,
                    _armaEspecial->getFisX(),_armaEspecial->getFisY(),_armaEspecial->getFisZ(),
                    2,8,8,8,5,0,0,false);
                _motora->getEvent("Arpa")->start(); // TO DO: Evento de sonido temporal
            }
        }

        //Se calcula el danyo del ataque
        aumentosAtaque += por1;
        if(_armaEquipada != NULL)
        {
            aumentosAtaque += (float) _armaEquipada->getAtaque() / por100;// + (float) variacion / 100;
        }
        aumentosAtaque *= constantes.CUATRO;
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

void Jugador::CrearCuerpoAtaque()
{
    unsigned short var1, var2, var3, var4;
    if(this->getArma() == nullptr)
    {
        var1 = 2, var2 = 1, var3 = 1, var4 = 2;
    }
    else
    {
        unsigned short tipoArma = this->getArma()->GetTipoObjeto();
        if ((tipoArma == constantes.GUITARRA1) || (tipoArma == constantes.GUITARRA2) ||
            (tipoArma == constantes.GUITARRA3))
        {
            var1 = 3, var2 = 1, var3 = 3, var4 = 1;
        }
        else if ((tipoArma == constantes.ARPA1) || (tipoArma == constantes.ARPA2) ||
            (tipoArma == constantes.ARPA3))
        {
            float velocidadflecha = 3.0f;
            int distance = 1.5;
            //Si ha chocado con un obstaculo no avanza
            if(_fisicas->collideAtackObstacle() == false)
            {
                atz += velocidadflecha*(distance *
                    cos(constantes.PI * atgy / constantes.PI_RADIAN));
                atx += velocidadflecha*(distance *
                    sin(constantes.PI * atgy / constantes.PI_RADIAN));
                atposZ += velocidadflecha*(distance *
                    cos(constantes.PI * atgy / constantes.PI_RADIAN));
                atposX += velocidadflecha*(distance *
                    sin(constantes.PI * atgy / constantes.PI_RADIAN));
            }
            var1 = 1, var2 = 1, var3 = 2, var4 = 3;
            tamanyoflecha = 1;
        }
        else if ((tipoArma == constantes.FLAUTA1) || (tipoArma == constantes.FLAUTA2) ||
            (tipoArma == constantes.FLAUTA3))
        {
            float velocidadflecha = 0;
            int distance = 1.0;
            if(_fisicas->collideAtackObstacle())
            {
                velocidadflecha = 0.4f;
                if(tamanyoflecha > 0)tamanyoflecha -= 0.1;
            }else
            {
                velocidadflecha = 1.0f;
                tamanyoflecha += 0.2;
            }

            atz += velocidadflecha*(distance *
                cos(constantes.PI * atgy / constantes.PI_RADIAN));
            atx += velocidadflecha*(distance *
                sin(constantes.PI * atgy / constantes.PI_RADIAN));

            if(_fisicas->collideAtackObstacle() == false)
            {
                atposZ += velocidadflecha* (distance * cos(constantes.PI * atgy / constantes.PI_RADIAN));
                atposX += velocidadflecha* (distance * sin(constantes.PI * atgy / constantes.PI_RADIAN));
                //Solo sustitulle una variable no crea cuerpos constante
                _fisicas->crearCuerpo(0,atposX,atposY,atposZ,1,tamanyoflecha*2,0,0,4,0,0,false);
            }
            var1 = 1, var2 = 1, var3 = 2, var4 = 3;
        }
    }

    _fisicas->updateAtaque(atposX,atposY,atposZ,atgx,atgy,atgz);
    _motor->dibujarObjetoTemporal(atx,aty,atz,atgx,atgy,atgz,
        var1,var2,var3,var4);

    if (this->getArma() != nullptr)
    {
        unsigned short tipoArma = this->getArma()->GetTipoObjeto();
        if ((tipoArma == constantes.ARPA1) || (tipoArma == constantes.FLAUTA1) || 
            (tipoArma == constantes.ARPA2) || (tipoArma == constantes.FLAUTA2) ||
            (tipoArma == constantes.ARPA3) || (tipoArma == constantes.FLAUTA3))
        {
            _motor->dispararProyectil(atx,aty,atz,atgx,atgy,atgz,tamanyoflecha);
        }
    }
}

void Jugador::AtacarUpdate(int danyo, std::vector<Enemigo*> &_getEnemigos)
{
    Constantes constantes;
    if(vida > 0)
    {
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
                if (encontrado == false && _getEnemigos.at(atacados.at(i)))
                {
                    _motor->startAnimaSprite(2,true,_getEnemigos.at(atacados.at(i))->getX(),
                        _getEnemigos.at(atacados.at(i))->getY(),_getEnemigos.at(atacados.at(i))->getZ());
                    float variacion = rand() % 7 - 3;
                    danyo += (int) variacion;
                    //CUANDO LE QUITAN VIDA BUSCA AL JUGADOR PARA ATACARLE
                    _getEnemigos.at(atacados.at(i))->ModificarVida(-danyo);

                    /*if(_fisicas->enemyCollideParedesRompibles(atacados.at(i)) || _fisicas->enemyCollideObstacleAndEnemies(atacados.at(i)))
                    {
                        _getEnemigos.at(atacados.at(i))->setNewPosiciones(posActual.x, posActual.y, posActual.z);
                        _getEnemigos.at(atacados.at(i))->initPosicionesFisicas(posActual.x/constantes.DOS, 0.0f, posActual.z/constantes.DOS);
                    }*/

                    danyo -= (int) variacion;
                    _motor->colorearEnemigo(255, 0, 255, 55, atacados.at(i));
                    //guardar el atacado para no repetir
                    atacados_normal.push_back(atacados.at(i));
                }
            }
        }
        else if(atacados.empty() && danyo > 0)
        {
            if(GetSala()->getPosicionEnGrafica() == 14)
            {
                _getEnemigos.at(0)->fallasSound();
                _getEnemigos.at(0)->stopPasearSound(GetTipoJug());
                _getEnemigos.at(0)->stopVentajaSound(GetTipoJug());
            }
        }
    }
    /*else
    {
        cout << "No supera las restricciones"<<endl;
    }*/
}

void Jugador::atacarEspUpdComun(int* danyo, std::vector<Enemigo*> &_getEnemigos)
{
    //lista de enteros que senyalan a los enemigos atacados
    vector <unsigned int> atacados = _fisicas->updateArmaEspecial(_armaEspecial->getFisX(),_armaEspecial->getFisY(),_armaEspecial->getFisZ());

    //Si hay colisiones se danya a los enemigos colisionados anyadiendole una variacion al danyo
    //y se colorean los enemigos danyados (actualmente todos al ser instancias de una malla) de color verde
    if(!atacados.empty() && *danyo > 0)
    {
        for(unsigned int i = 0; i < atacados.size(); i++)
        {
            if(_getEnemigos.at(atacados.at(i)))
            {
                _motor->startAnimaSprite(2,true,_getEnemigos.at(atacados.at(i))->getX()+2.0f,
                    _getEnemigos.at(atacados.at(i))->getY(),_getEnemigos.at(atacados.at(i))->getZ()-1.0f);
                float variacion = rand() % 7 - 3;
                *danyo += (int) variacion;
                _getEnemigos.at(atacados.at(i))->ModificarVida(-(*danyo));    
                *danyo -= (int) variacion;
                _motor->colorearEnemigo(255, 0, 255, 55, atacados.at(i));
            }
        }
    }
    else if(atacados.empty() && *danyo > 0)
    {
        if(GetSala()->getPosicionEnGrafica() == 14)
        {
            _getEnemigos.at(0)->fallasSound();
            _getEnemigos.at(0)->stopPasearSound(GetTipoJug());
            _getEnemigos.at(0)->stopVentajaSound(GetTipoJug());
        }
    }

}

void Jugador::generarSonido(int intensidad,double duracion,int tipo)
{
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

    // TO DO: terminar lo de la interfaz y la llave
    //_interfaz->setArma(1);
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

INnpc::VectorEspacial Jugador::GetVectorOrientacion()
{
    return vectorOrientacion;
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

bool Jugador::GetInvulnerabilidad()
{
    return invulnerabilidad;
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

float Jugador::getTimeInvulnerable()
{
    return painAtackTime;
}

float Jugador::getLastTimeInvulnerable()
{
    return lastPainAtackTime;
}

const char*Jugador::getRutaArmaEsp()
{
    return _rutaArmaEspecial;
}

const char*Jugador::getRutaTexturaArmaEsp()
{
    return _rutaTexturaArmaEspecial;
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

void Jugador::setPosicionesAtaque(float nx,float ny,float nz)
{
    atx = nx;
    aty = ny;
    atz = nz;
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

void Jugador::setVectorOrientacion()
{
    Constantes constantes;
    vectorOrientacion.vX = sin(constantes.PI * rotFutura.y / constantes.PI_RADIAN);
    vectorOrientacion.vY = 0.0f;
    vectorOrientacion.vZ = cos(constantes.PI * rotFutura.y / constantes.PI_RADIAN);
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
    struct
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    }
    velocidad, posiciones;
    Constantes constantes;
    if (vid < 0 && !invulnerabilidad) // QuitarVida, aumenta barra ataque especial
    {
        vida += vid;
        ModificarBarraAtEs(abs(vid));
        SetInvulnerabilidad(constantes.TRUE);
        setTimeInvulnerable(constantes.CIEN_PORCIENTO);

        if(porcentajeVelocidad != constantes.UNO)
        {
            porcentajeVelocidad = constantes.UNO;
        }
        velocidad.x = vectorOrientacion.vX* velocidadMaxima * porcentajeVelocidad;
        velocidad.z = vectorOrientacion.vZ* velocidadMaxima * porcentajeVelocidad;

        posiciones.x = posFutura.x - velocidad.x;
        posiciones.z = posFutura.z - velocidad.z;
        setNewPosiciones(posiciones.x, posActual.y, posiciones.z);
        this->ColisionEntornoEne();
    }
    else
    {
        if(vid >= constantes.CERO)
        {
            vida += vid;
        }
    }
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

void Jugador::SetInvulnerabilidad(bool invulnerable)
{
    invulnerabilidad = invulnerable;
}

void Jugador::setAtaque(int ataq)
{
    ataque = ataq;
}

void Jugador::setArma(Recolectable* _armaRec)
{
    // Al dejar el objeto o reiniciar partida, borra el arma puesta
    if (_armaEquipada != nullptr)
    {
        _motor->EraseArma();
        _fisicas->EraseArma();
    }

    // Se comprueba si ha recogido otra arma
    if(_armaRec)
    {
        unsigned short tipoArma = _armaRec->GetTipoObjeto();
        _armaEquipada = new Arma(_armaRec->getAtaque(),
            _armaRec->getAncho(),_armaRec->getLargo(),_armaRec->getAlto(),
            tipoArma);

        //PROVISIONAL
        _armaEquipada->setRotacion(0.0, constantes.PI_RADIAN, 0.0);
        //!PROVISIONAL

        //lo cargamos por primera vez en el motor de graficos
        _motor->CargarArmaJugador(posActual.x, posActual.y, posActual.z,
            _armaEquipada->GetModelo(),_armaEquipada->GetTextura());

        //lo cargamos por primera vez en el motor de fisicas
        _fisicas->crearCuerpo(0,posActual.x/2,posActual.y/2,posActual.z/2,
            2,
            _armaEquipada->getAncho(),_armaEquipada->getLargo(),_armaEquipada->getAlto(),
            9,0,0,false);

        // Cambiamos el dibujo del HUD con el arma equipada
        _interfaz->setArma(tipoArma);
    }
    else
    {
        _interfaz->setArma(constantes.MANO);
        _armaEquipada = nullptr;
    }
}

void Jugador::setArmaEspecial(int ataque)
{
    _armaEspecial = new Arma(ataque,3,3,3,constantes.ARMA);
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

void Jugador::setTimeInvulnerable(float time)
{
    painAtackTime = time;
}

void Jugador::setLastTimeInvulnerable(float time)
{
    lastPainAtackTime = time;
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

const char* Jugador::GetModelo()
{
    return _modelo;
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

Sala* Jugador::GetSala()
{
    return salaActual;
}

void Jugador::SetSala(Sala* sala)
{
    salaActual = sala;
}

bool Jugador::ColisionEntornoEne()
{
    //colisiones con todos los objetos y enemigos que no se traspasan
    if(_fisicas->collideObstacle() ||
        !_fisicas->collidePlatform() ||
        _fisicas->collideParedesRompibles())
    {//colisiona
        setNewPosiciones(posActual.x, posActual.y, posActual.z);
        return true;
    }
    //no colisiona
    return false;
}

void Jugador::Render(float updTime, float drawTime)
{
    moverseEntidad(1 / updTime);
    RotarEntidad(1 / updTime);
    UpdateTimeMove(drawTime);

    //Calculo de la camara
    if(_fisicas->CamaraRotara())
    {
        if(newz < 20.0f)newz += 1.0f;
        if(newy < 10.0f)newy += 0.5f;
    }
    else
    {
        if(newz > 0.0f)newz -= 1.0f;
        if(newy > 0.0f)newy -= 0.5f;
    }

    _motor->mostrarJugador(
        posActual.x, posActual.y, posActual.z,
        rotActual.x, rotActual.y, rotActual.z, newy, newz
    );
}
