#include "EstadoIniciar.hpp"
#include "../Juego.hpp"
#include "../Times.hpp"

EstadoIniciar::EstadoIniciar()
{
    _motor = MotorGrafico::GetInstance();
    _motora = MotorAudioSystem::getInstance();
    slotSeleccionado = 0;
    fase = 0;
    tipo = 0;
    slots[0].RecuperarPartida("saves/slot1");
    slots[1].RecuperarPartida("saves/slot2");
    slots[2].RecuperarPartida("saves/slot3");
    nombrePartida = "";
    tiempoCursor = 0.0f;
}

EstadoIniciar::~EstadoIniciar()
{
    _motor = nullptr;
    _motora = nullptr;
}

void EstadoIniciar::Iniciar()
{
    _motor->CambiarAnchuraTexto( _motor->CrearTexto("Iniciar Nueva partida - ESC para salir", 0, 0, 300, 20),300);
    _motor->CrearImagen("assets/images/pr2.png",150,100,2.2f);
    unsigned short did = _motor->CrearTexto("Seleccione slot de guardado:",180,120,0,0);
    _motor->CambiarAnchuraTexto(did,300);
    _motor->CrearBoton2(205,160,8.0f,170,40,300,GUI_ID_SLOT1,"Slot 1","assets/images/slot.png",true,"assets/images/slotpulsado.png","assets/images/slotencima.png");
    _motor->CrearTexto(slots[0].GetNombre(),205+166,160+60,0,0);
    _motor->CrearBoton2(205,260,8.0f,170,40,300,GUI_ID_SLOT2,"Slot 2","assets/images/slot.png",true,"assets/images/slotpulsado.png","assets/images/slotencima.png");
    _motor->CrearTexto(slots[1].GetNombre(),205+166,260+60,0,0);
    _motor->CrearBoton2(205,360,8.0f,170,40,300,GUI_ID_SLOT3,"Slot 3","assets/images/slot.png",true,"assets/images/slotpulsado.png","assets/images/slotencima.png");
    _motor->CrearTexto(slots[2].GetNombre(),205+166,360+60,0,0);
    _motor->ResetKey(LMOUSE_PRESSED_DOWN);
}

// Actualiza lo que se ve por pantalla
void EstadoIniciar::Render()
{
    _motor->FondoEscena(0,0,0,0); // Borra
    _motor->RenderEscena();               // Vuelve a pintar
}

void EstadoIniciar::Update()
{

}

void EstadoIniciar::ManejarEventos()
{
    if(slotSeleccionado != 0)
    {
        if(fase > 10)
        {
            _motor->BorrarScena();
            _motor->BorrarGui();
            _motora->getEvent("Menu")->stop(); //Detener musica Menu
            Juego::GetInstance()->estado.CambioEstadoJugar(slots[slotSeleccionado-1].GetNivel(),slots[slotSeleccionado-1].GetTipo(),slots[slotSeleccionado-1].GetDinero(),slotSeleccionado);
            _motor->AsignarCargando(_motor->CrearImagen("assets/images/cargando.png",540,330,1.0f),_motor->CrearImagen("assets/images/inputs.png",50,85,0.5f));
            return;
        }

        if(fase == 1)
        {
            //escoger nombre
            _motor->BorrarGui();
            _motor->CambiarAnchuraTexto( _motor->CrearTexto("Escriba el nombre de la partida - ESC para salir", 0, 0, 300, 20),500);
            _motor->CrearImagen("assets/images/pr2.png",150,100,2.2f);
            _motor->CrearBoton2(300,240,2.0f,170,40,300,GUI_ID_CAMPONOMBRE,"Slot 1","assets/images/campoTexto.png",false);//no creamos texto
            idCampoTexto = _motor->CrearTexto("",310,260,0,0);
            _motor->CambiarColorTexto(idCampoTexto,0,0,0);
            _motor->CrearBoton(300,300,0,0,999,L"       Siguiente",L"");
            _motor->CambiarAnchuraTexto(idCampoTexto,180);
            tiempoCursor = 0.0f;
            fase = 2;
            _motor->ResetKey(LMOUSE_PRESSED_DOWN);
            return;
        }

        if(fase == 3)
        {

            char * nombrePartida2 = _motor->DevolverTextoCapturado();

            if(nombrePartida2 != nullptr)
            {
                tiempoCursor = 0.0f;
                cursor = false;
                nombrePartida = nombrePartida2;
            }

            if(_motor->EstaPulsado(KEY_DEL))
            {
                _motor->BorrarUltimaLetra();
                _motor->ResetKey(KEY_DEL);
            }

            Times * tiempo = Times::GetInstance();

            if(tiempoCursor == 0.0f || tiempo->CalcularTiempoPasado(tiempoCursor) > 700.0f)
            {
                if(cursor)
                {
                    //ponemos |
                    cursor = false;
                    _motor->CambiarTexto(idCampoTexto," ");
                }
                else
                {
                    //quitamos |
                    cursor = true;
                    _motor->CambiarTexto(idCampoTexto,nombrePartida);
                }

                tiempoCursor = tiempo->GetTiempo(1);
            }
        }

        if(fase == 2 && _motor->OcurreEvento(GUI_ID_CAMPONOMBRE))
        {
            _motor->ActivarCapturaTexto();
            _motor->InicializarCaptura(nombrePartida);
            cursor = false;
            fase = 3;
        }

        if(fase == 3 && _motor->OcurreEvento(999))
        {
            //cambiamos a escoger personaje ---- aqui detectar si no hay solo espacios
            fase = 4;
            _motor->BorrarGui();
            _motor->CrearImagen("assets/images/pr2.png",150,100,2.2f);
            _motor->CrearBoton2(430,120,0.5f,170,40,300,997,"Slot 1","assets/images/heavyboton1.png",false,"assets/images/heavyboton2.png","assets/images/heavyboton3.png");
            _motor->CrearBoton2(150,120,0.5f,170,40,300,998,"Slot 1","assets/images/bailarinaboton1.png",false,"assets/images/bailarinaboton2.png","assets/images/bailarinaboton3.png");
            _motor->CrearBoton(300,463,0,0,996,L"  Empezar Partida",L"");
            _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        }

        if(fase == 4)//escoger personaje
        {
            if(_motor->OcurreEvento(998))
            {
                tipo = constantes.BAILAORA;
                fase = 5;
            }

            if(_motor->OcurreEvento(997))
            {
                tipo = constantes.HEAVY;
                fase = 5;
            }
        }

        if(fase == 5 && _motor->OcurreEvento(996))//empezar partida
        {
            //guardamos los datos
            slots[slotSeleccionado-1].SetNombre(nombrePartida);
            slots[slotSeleccionado-1].SetTipo(tipo);

            switch(slotSeleccionado)
            {
                case 1:
                    slots[(slotSeleccionado-1)].GuardarPartida("saves/slot1");
                break;
                case 2:
                    slots[(slotSeleccionado-1)].GuardarPartida("saves/slot2");
                break;
                case 3:
                    slots[(slotSeleccionado-1)].GuardarPartida("saves/slot3");
                break;
            }
            _motor->DesactivarCapturaTexto();
            _motor->ResetKey(LMOUSE_PRESSED_DOWN);
            fase = 11;
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
        _motor->DesactivarCapturaTexto();
        atras();
    }

}

// Vuelve al menu principal
void EstadoIniciar::atras()
{
    _motor->BorrarScena();
    _motor->BorrarGui();
    Juego::GetInstance()->estado.SaltarAlMenu();
}
