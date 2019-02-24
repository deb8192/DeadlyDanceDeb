#include "TMalla.hpp"

//Uso: Constructor
TMalla::TMalla()
{
    didentidad = 'M'; //para sabe que funcion hace es informativo
    frames_totales = 0;
    mallas_totales = 0;
    frame_inicial = 0;
    frame_final = 0;
    frame_actual = 0;
    velocidad_animacion = 0;
}

//Uso: destructor
TMalla::~TMalla()
{

}

//Uso: Pone el shader local nullptr
//Entradas: ninguna
//Salidas: ninguna 
void TMalla::cargarMalla(unsigned short,unsigned short)
{
    //aqui llamamos a objetos->ObtenerFrame(1); y se carga en memoria para pintarlo
}

// sobrecarga metodos TEntidad
void TMalla::beginDraw()
{
   std::cout << "ads" << std::endl;
   objetos->Draw(shader);
}

void TMalla::endDraw()
{

}

void TMalla::BucleAnimacion(unsigned short,unsigned short)
{

}

void TMalla::SiguienteAnimacion()
{

}

void TMalla::DefinirAnimaciones()
{

}

unsigned short TMalla::getFrameInicio()
{
    return 0;
}

unsigned short TMalla::getFrameFinal()
{
    return 0;
}

unsigned short TMalla::getFrameActual()
{
    return 0;
}

bool TMalla::setTiempoAnimacion(unsigned short)
{
    return false;
}

void TMalla::setRecursoObjeto(RMalla * objeto)
{
    objetos = objeto;
}