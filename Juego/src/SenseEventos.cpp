#include "SenseEventos.hpp"
#include "MotorGrafico.hpp"

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
    double tiempoPasado = (double(tiempoFinal-tiempoInicio)/CLOCKS_PER_SEC);
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