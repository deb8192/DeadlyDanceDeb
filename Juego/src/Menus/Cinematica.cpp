#include "Cinematica.hpp"
#include "../Juego.hpp"

// para clases singleton deben tener un indicador de que se ha creado el unico objeto
//Cinematica* Cinematica::_unicaInstancia = 0;
// fin indicador singleton

Cinematica::~Cinematica()
{
    cout << "Borrando cinematica" <<endl;
    delete _motor;
    //delete _unicaInstancia;
}

void Cinematica::Iniciar()
{
    _motor = MotorGrafico::GetInstance();

     // Crear la camara aqui si la necesita
   
    _motor->FondoEscena(255,0,0,0);
}

void Cinematica::Render()
{
    _motor->FondoEscena(255,0,0,0);     // Borra
    _motor->RenderEscena();             // Vuelve a pintar
}

void Cinematica::Update()
{
    
}

void Cinematica::ManejarEventos()
{
    // ESC para saltar la cinematica
    if (_motor->EstaPulsado(KEY_ESC)) {
        
        _motor->ResetKey(KEY_ESC);
        Juego::GetInstance()->estado.CambioEstadoMenu();
    }
}

// Elimina la memoria antes de cargar el menu
void Cinematica::Vaciar()
{
    // TO DO: vaciar memoria
    cout << "Vaciando cinematica" <<endl;
}