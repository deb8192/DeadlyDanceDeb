#include "EstadoContinuar.hpp"
#include "../Juego.hpp"

EstadoContinuar::EstadoContinuar()
{
    _motor = MotorGrafico::GetInstance();
    _motora = MotorAudioSystem::getInstance();
    estadoSlot[0] = slots[0].RecuperarPartida("saves/slot1");
    estadoSlot[1] = slots[1].RecuperarPartida("saves/slot2");
    estadoSlot[2] = slots[2].RecuperarPartida("saves/slot3");
    slotSeleccionado = 0;
    fase = 0;
    id = 0;
}

EstadoContinuar::~EstadoContinuar()
{
    _motor = nullptr;
}

void EstadoContinuar::Iniciar()
{
    _motor->CambiarAnchuraTexto( _motor->CrearTexto("Iniciar Nueva partida - ESC para salir", 0, 0, 300, 20),300);
    _motor->CrearImagen("assets/images/pr2.png",150,100,2.2f);
    unsigned short did = _motor->CrearTexto("Seleccione slot de guardado:",180,120,0,0);
    _motor->CambiarAnchuraTexto(did,300);
    _motor->CrearBoton2(205,160,8.0f,170,40,300,GUI_ID_SLOT1,L"Slot 1",L"assets/images/slot.png",true,"assets/images/slotpulsado.png","assets/images/slotencima.png");
    _motor->CrearTexto(slots[0].GetNombre(),205+166,160+60,0,0);
    _motor->CrearBoton2(205,260,8.0f,170,40,300,GUI_ID_SLOT2,L"Slot 2",L"assets/images/slot.png",true,"assets/images/slotpulsado.png","assets/images/slotencima.png");
    _motor->CrearTexto(slots[1].GetNombre(),205+166,260+60,0,0);
    _motor->CrearBoton2(205,360,8.0f,170,40,300,GUI_ID_SLOT3,L"Slot 3",L"assets/images/slot.png",true,"assets/images/slotpulsado.png","assets/images/slotencima.png");
    _motor->CrearTexto(slots[2].GetNombre(),205+166,360+60,0,0);
    _motor->ResetKey(LMOUSE_PRESSED_DOWN);
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
    if(slotSeleccionado != 0)
    {
        if(fase == 1)//se ha escogido partida
        {
            if(estadoSlot[slotSeleccionado-1])
            {
                if(id != 0)
                {
                    _motor->BorrarElementoPorIdReal(id);
                }

                _motor->CrearBoton(300,500,0,0,999,L"   Cargar Partida",L"");
                fase = 2;
            }
            else
            {
                if(id == 0)
                {
                    id = _motor->CrearTexto("La partida seleccionada no existe.", 250, 500, 300, 20);
                    _motor->CambiarAnchuraTexto(id,300);
                    _motor->CambiarColorTexto(id,255,0,0);
                }
                _motor->CambiarColorTexto(id,200,0,0);
                slotSeleccionado = 0;
                fase = 0;
            }

        }

        if(fase == 2 && _motor->OcurreEvento(999))
        {
            GestorInterfaces * _ges = GestorInterfaces::GetInstance();
            _motor->ResetKey(LMOUSE_PRESSED_DOWN);
            _motor->BorrarScena();
            _motor->BorrarGui();
            _motora->getEvent("Menu")->stop(); //Detener musica Menu
            Juego::GetInstance()->estado.CambioEstadoJugar(slots[slotSeleccionado-1].GetNivel(),slots[slotSeleccionado-1].GetTipo(),slots[slotSeleccionado-1].GetDinero(),slotSeleccionado);
            _motor->AsignarCargando(_motor->CrearImagen("assets/images/cargando.png",540,330,1.0f),_motor->CrearImagen("assets/images/inputs.png",50,85,0.5f));
            return;
        }
    }

    if(slotSeleccionado == 0 && _motor->OcurreEvento(GUI_ID_SLOT1))
    {
        slotSeleccionado = 1;
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        _motor->ResetEvento(GUI_ID_SLOT1);
        fase = 1;
    }

    if(slotSeleccionado == 0 && _motor->OcurreEvento(GUI_ID_SLOT2))
    {
        slotSeleccionado = 2;
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        _motor->ResetEvento(GUI_ID_SLOT2);
        fase = 1;
    }

    if(slotSeleccionado == 0 && _motor->OcurreEvento(GUI_ID_SLOT3))
    {
        slotSeleccionado = 3;
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        _motor->ResetEvento(GUI_ID_SLOT3);
        fase = 1;
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
