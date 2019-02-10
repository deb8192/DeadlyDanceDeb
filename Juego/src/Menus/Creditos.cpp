#include "Creditos.hpp"
#include "../Juego.hpp"

// para clases singleton deben tener un indicador de que se ha creado el unico objeto
//Creditos* Creditos::_unicaInstancia = 0;
// fin indicador singleton

Creditos::~Creditos()
{
    delete _motor;
    //delete _unicaInstancia;
}

void Creditos::Iniciar()
{
    _motor = MotorGrafico::GetInstance();
   
    _motor->FondoEscena(255,200,200,200);
    _motor->ActivarFuenteDefault();
    _motor->CrearTexto("Creditos - ESC para salir", 0, 0, 300, 20); // Parametros: texto, x1, y1, x2, y2
}

// Actualiza lo que se ve por pantalla
void Creditos::Render()
{
    _motor->FondoEscena(255,200,200,200); // Borra
    _motor->RenderEscena();               // Vuelve a pintar
}

void Creditos::Update()
{
    
}

void Creditos::ManejarEventos()
{
    if (_motor->EstaPulsado(KEY_ESC)) {
        _motor->ResetKey(KEY_ESC);
        atras();
    }
}

// Vuelve al menu principal
void Creditos::atras()
{
    _motor->BorrarScena();
    _motor->BorrarGui();
    Juego::GetInstance()->estado.SaltarAlMenu();
}

// Elimina la memoria antes de volver al menu
void Creditos::Vaciar()
{
    cout << "Vaciando creditos" <<endl;
}