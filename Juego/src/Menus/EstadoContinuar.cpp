#include "EstadoContinuar.hpp"
#include "../Juego.hpp"

EstadoContinuar::EstadoContinuar()
{
    _motor = MotorGrafico::GetInstance();
    slotSeleccionado = 0;
}

EstadoContinuar::~EstadoContinuar()
{
    _motor = nullptr;
}

void EstadoContinuar::Iniciar()
{
    _motor->CambiarAnchuraTexto(_motor->CrearTexto("Continuar Partida - ESC para salir", 0, 0, 300, 20),300);
    _motor->CrearImagen("assets/images/pr2.png",150,100,10.0f);
    unsigned short did = _motor->CrearTexto("Seleccione slot de guardado:",180,120,0,0);
    _motor->CambiarAnchuraTexto(did,300);
    _motor->CrearBoton2(205,160,8.0f,170,40,300,GUI_ID_SLOT1,L"Slot 1",L"assets/images/slot.png",true,"assets/images/slotpulsado.png","assets/images/slotencima.png");
    _motor->CrearBoton2(205,260,8.0f,170,40,300,GUI_ID_SLOT2,L"Slot 2",L"assets/images/slot.png",true,"assets/images/slotpulsado.png","assets/images/slotencima.png");
    _motor->CrearBoton2(205,360,8.0f,170,40,300,GUI_ID_SLOT3,L"Slot 3",L"assets/images/slot.png",true,"assets/images/slotpulsado.png","assets/images/slotencima.png");
}

// Actualiza lo que se ve por pantalla
void EstadoContinuar::Render()
{
    _motor->FondoEscena(0,0,0,0); // Borra
    _motor->RenderEscena();               // Vuelve a pintar
}

void EstadoContinuar::Update()
{
    
}

void EstadoContinuar::ManejarEventos()
{

    if(_motor->OcurreEvento(GUI_ID_SLOT1))
    {

    }

    if(_motor->OcurreEvento(GUI_ID_SLOT2))
    {

    }

    if(_motor->OcurreEvento(GUI_ID_SLOT3))
    {

    }

    if (_motor->EstaPulsado(KEY_ESC)) {
        _motor->ResetKey(KEY_ESC);
        atras();
    }
}

// Vuelve al menu principal
void EstadoContinuar::atras()
{
    _motor->BorrarScena();
    _motor->BorrarGui();
    Juego::GetInstance()->estado.SaltarAlMenu();
}