#include "SenseEventos.hpp"
#include "MotorGrafico.hpp"
#include "MotorFisicas.hpp"

SenseEventos* SenseEventos::_unica_instancia = 0;

SenseEventos::SenseEventos()
{
    tiempoFinal = 0.0;
    tiempoInicio = 0.0;

    /*_motor = MotorGrafico::GetInstance();
    _fisicas = MotorFisicas::getInstance();*/
}

SenseEventos::~SenseEventos()
{
    tiempoInicio = 0.0;
    tiempoInicio = 0.0;

    // Punteros a clases singleton
    /*_motor = nullptr;
    _fisicas = nullptr;*/

    // Liberar memoria
    short tam = sonidos.size();
    for(short i=0; i < tam; i++)
    {
        delete sonidos.at(i);
    }
    sonidos.clear();

    delete _unica_instancia;
}

void SenseEventos::update()
{
    MotorGrafico* _motor = MotorGrafico::GetInstance();

    //nos recorremos los eventos de sonido
    tiempoFinal = clock();
    
    double tiempoPasado = 0.0;
    
    if(tiempoInicio != 0.0)
    {
       tiempoPasado = (double(tiempoFinal-tiempoInicio)/CLOCKS_PER_SEC);
    }

    if(sonidos.size()>0)
    {
        for(std::size_t i=0;i<sonidos.size();i++)
        {
            sonidos[i]->restarTiempo(tiempoPasado);
            if(sonidos[i]->getDuracion() == 0)
            {
                sonidos[i]->~EventoSonido();
                delete sonidos[i];
                sonidos[i] = NULL;
                sonidos.erase(sonidos.begin()+i);
            }
            else
            {
                int* propie = sonidos[i]->getPropiedades();
                float inten = sonidos[i]->getIntensidad();
                
                _motor->dibujarCirculoEventoSonido(propie[2],propie[3],propie[4],inten);
                delete [] propie;
            }
            
        }
    }
    tiempoInicio = clock();
}

void SenseEventos::agregarEvento(EventoSonido* evento)
{
    sonidos.push_back(evento);//se agrega elemento
}

 std::vector<EventoSonido* > SenseEventos::listarSonidos(int x, int z)
 {
    std::vector<EventoSonido* > listaSonidos;
    if(sonidos.size()>0)
    {
        for(std::size_t i=0;i<sonidos.size();i++)
        {
            if(sonidos[i]->getDuracion() != 0)
            {
                int* propie = sonidos[i]->getPropiedades();
                int cx = propie[2];
                int cz = propie[4];
                float inter = sqrt( (pow((cx-x),2)) + (pow((cz-z),2)) );
                float intensi = sonidos[i]->getIntensidad();
                if(inter <= intensi)//&& inter != NAN
                {
                    listaSonidos.push_back(sonidos[i]);
                }
                delete [] propie;
            }
        }
    }

    return listaSonidos;
 }

//para la vista devuelve los objetos que ve
int * SenseEventos::listaObjetos(float x, float y, float z,float rot,float vista, int modo, bool perifericos)
{
    y += 1;
    rot += 90;
    MotorGrafico* _motor = MotorGrafico::GetInstance();
    MotorFisicas* _fisicas = MotorFisicas::getInstance();

    int* perDer = new int[7];
    int* perIzq = new int[7];
    int* recto = new int[21];
    int* vectorRespuestaAuxiliar = _fisicas->colisionRayoUnCuerpo(x,y,z,rot,vista,modo);//mira directa;

    recto[0] = vectorRespuestaAuxiliar[0];

    //Estos valores se corresponden con las componentes del punto de colision con el obstaculo donde colisiona la vision
    recto[1] = vectorRespuestaAuxiliar[1];
    recto[2] = vectorRespuestaAuxiliar[2]; 
    recto[3] = vectorRespuestaAuxiliar[3]; 

    //Estos valores se corresponden con las componentes de la normal de la seccion del obstaculo donde colisiona la vision
    recto[4] = vectorRespuestaAuxiliar[4];
    recto[5] = vectorRespuestaAuxiliar[5]; 
    recto[6] = vectorRespuestaAuxiliar[6]; 
    
    _motor->debugVision(x,y,z,rot,vista);
    _motor->debugVision(x,y,z,rot+30,vista/2);
    _motor->debugVision(x,y,z,rot-30,vista/2);

    if(perifericos)
    {
        perDer = _fisicas->colisionRayoUnCuerpo(x,y,z,(-1*(rot-180))+30,vista/2,modo);//mira periferica derecha
        perIzq = _fisicas->colisionRayoUnCuerpo(x,y,z,(-1*(rot-180))-30,vista/2,modo);//mira periferica izquierda
        
        //Si lo ve por uno de los perifericos lo pone a 1
        if(perDer[0] == 1)
        {
            recto[7] = 1;
            //Estos valores se corresponden con las componentes del punto de colision con el obstaculo donde colisiona la vision
            recto[8] = perDer[1];
            recto[9] = perDer[2]; 
            recto[10] = perDer[3];

            //Estos valores se corresponden con las componentes de la normal de la seccion del obstaculo donde colisiona la vision
            recto[11] = perDer[4];
            recto[12] = perDer[5]; 
            recto[13] = perDer[6];
        }
        else recto[7] = 0;
        if(perIzq[0] == 1)
        {
            recto[14] = 1;
            //Estos valores se corresponden con las componentes del punto de colision con el obstaculo donde colisiona la vision
            recto[15] = perIzq[1];
            recto[16] = perIzq[2]; 
            recto[17] = perIzq[3];

            //Estos valores se corresponden con las componentes de la normal de la seccion del obstaculo donde colisiona la vision
            recto[18] = perIzq[4];
            recto[19] = perIzq[5]; 
            recto[20] = perIzq[6];
        }
        else recto[14] = 0;

        //eliminamos los punteros ya no son necesarios
        delete [] perDer;
        delete [] perIzq;
    }

    //a continuacion devolvemos listado de las cosas que se ven
    return recto;
}