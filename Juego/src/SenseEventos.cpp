#include "SenseEventos.hpp"
#include "MotorGrafico.hpp"
#include "MotorFisicas.hpp"

SenseEventos* SenseEventos::unica_instancia = 0;

SenseEventos::SenseEventos()
{
    tiempoFinal = 0.0;
    tiempoInicio = 0.0;
}

SenseEventos::~SenseEventos(void)
{

}

void SenseEventos::update()
{
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
                sonidos[i]->~eventoSonido();
                delete sonidos[i];
                sonidos[i] = NULL;
                sonidos.erase(sonidos.begin()+i);
            }
            else
            {
                int * propie = sonidos[i]->getPropiedades();
                float inten = sonidos[i]->getIntensidad();
                MotorGrafico * motor = MotorGrafico::getInstance();
                motor->dibujarCirculoEventoSonido(propie[2],propie[3],propie[4],inten);
                delete [] propie;
            }
            
        }
    }
    tiempoInicio = clock();
}

void SenseEventos::agregarEvento(eventoSonido * evento)
{
    sonidos.push_back(evento);//se agrega elemento
}

 std::vector<eventoSonido *> SenseEventos::listarSonidos(int x, int y)
 {
    std::vector<eventoSonido *> listaSonidos;
    if(sonidos.size()>0)
    {
        for(std::size_t i=0;i<sonidos.size();i++)
        {
            if(sonidos[i]->getDuracion() != 0)
            {
                int * propie = sonidos[i]->getPropiedades();
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

    MotorFisicas * fisicas = MotorFisicas::getInstance();
    
    if(perifericos)
    {
        int * perDer = fisicas->colisionRayoUnCuerpo(x,y,z,rot+30,vista/2,modo);//mira periferica derecha
        int * perIzq = fisicas->colisionRayoUnCuerpo(x,y,z,rot-30,vista/2,modo);//mira periferica izquierda
    }
        
    int * recto = fisicas->colisionRayoUnCuerpo(x,y,z,rot,vista,modo);//mira directa

    if(perifericos)
    {
            //se aconseja girar hacia la izquierda para centrar al jugador
            //std::cout << "gira izquierda" << std::endl;

            //se aconseja girar hacia la derecha para centrar al jugador
            //std::cout << "gira derecha" << std::endl;
            
            //por construir
    }

    //a continuacion devolvemos listado de las cosas que se ven
    return recto;
}