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

 std::vector<EventoSonido* > SenseEventos::listarSonidos(int x, int y)
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
                int cy = propie[3];
                float inter = sqrt( (pow((cx-x),2)) + (pow((cy-y),2)) );
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
    rot += 90;
    MotorGrafico* _motor = MotorGrafico::GetInstance();
    MotorFisicas* _fisicas = MotorFisicas::getInstance();

    int* perDer;
    int* perIzq;
    int* recto = _fisicas->colisionRayoUnCuerpo(x,y,z,rot,vista,modo);//mira directa
    _motor->debugVision(x,y,z,rot,vista);
    _motor->debugVision(x,y,z,rot+30,vista/2);
    _motor->debugVision(x,y,z,rot-30,vista/2);

    if(perifericos)
    {
        perDer = _fisicas->colisionRayoUnCuerpo(x,y,z,(-1*(rot-180))+30,vista/2,modo);//mira periferica derecha
        perIzq = _fisicas->colisionRayoUnCuerpo(x,y,z,(-1*(rot-180))-30,vista/2,modo);//mira periferica izquierda
        
        //Si lo ve por uno de los perifericos lo pone a 1
        if(modo == 1)//jugador
        {
            if(recto[0] != 1 && (perDer[0] == 1 || perIzq[0] == 1))
            {
                recto[0] = 1;
            }
        }

        if(modo == 2)//objetos
        {
            //for recorriendose cada valor comparando 
            //indice 0 contiene el numero de valores
        }

        if(modo == 3)//enemigos
        {
                //for recorriendose cada valor comparando 
                //indice 0 contiene el numero de valores
        }

        //eliminamos los punteros ya no son necesarios
        delete [] perDer;
        delete [] perIzq;
    }

    //a continuacion devolvemos listado de las cosas que se ven
    return recto;
}