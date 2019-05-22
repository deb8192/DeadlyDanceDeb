#include "EstadoGanar.hpp"
#include "../Juego.hpp"

EstadoGanar::EstadoGanar()
{
    _motor = MotorGrafico::GetInstance();
    _motora = MotorAudioSystem::getInstance();
    nombreUser = new char [10];
    for(int i = 0; i < 10; i++)
    {
        nombreUser[i] = '\0';
    }
    nombrePass = new char [10];
    campoSeleccion = -1;
}

EstadoGanar::~EstadoGanar()
{
    _motor = nullptr;
    _motora = nullptr;
    delete [] nombreUser;
    delete [] nombrePass;
}

void EstadoGanar::Iniciar()
{
    _motor->FondoEscena(255,0,0,0);
    _motor->ActivarFuenteDefault();
    pintarBotones();
}

// Actualiza lo que se ve por pantalla
void EstadoGanar::Render()
{
    _motor->FondoEscena(255,0,0,0);     // Borra
    _motor->RenderEscena();             // Vuelve a pintar
}

void EstadoGanar::Update()
{
    if(campoSeleccion != -1)
    {
        if(_motor->EstaPulsado(KEY_DEL))
        {
            _motor->BorrarUltimaLetra();
            _motor->ResetKey(KEY_DEL);
        }

        char * nombrePartida2 = _motor->DevolverTextoCapturado();
        //tenemos que coger lo que hay y actualizar
        if(campoSeleccion == GUI_ID_USER)
        {
           
            if(nombrePartida2 != nullptr)
            {
                for(int i = 0; i < 10; i++)
                {
                    nombreUser[i] = nombrePartida2[i];
                }
                _motor->CambiarTexto(campo_user,nombreUser);
            }

            
        }
        else if(campoSeleccion == GUI_ID_PASS)
        {
            if(nombrePartida2 != nullptr)
            {
                for(int i = 0; i < 10; i++)
                {
                    nombrePass[i] = nombrePartida2[i];
                }
                _motor->CambiarTexto(campo_pass,nombrePass);
            }
        }
    }
}

void EstadoGanar::ManejarEventos()
{
    if (_motor->OcurreEvento(GUI_ID_SALIR_BUTTON))
    {
        borrarEscenaResetearEvento(GUI_ID_SALIR_BUTTON);
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        salir();
    }

    if (_motor->OcurreEvento(GUI_ID_CONTINUAR))
    {
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        borrarGUIResetearEvento(GUI_ID_CONTINUAR);
        siguienteNivel();
    }

    if (_motor->OcurreEvento(GUI_ID_MENU_BUTTON))
    {
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        borrarEscenaResetearEvento(GUI_ID_MENU_BUTTON);
        menuPrincipal();
    }

    if (_motor->OcurreEvento(GUI_ID_SEND))
    {
       /**/
       int retu;
       if(strlen(nombreUser) > 0 && strlen(nombrePass) > 0)
       {
            puntuar.setUser(nombreUser);
	        puntuar.setPass(nombrePass);
            puntuar.setPuntuacion(9000);
            puntuar.setTiempo(30);
            puntuar.setNivel(0);
            retu =  puntuar.subirpuntuacion(false);

            	switch(retu)
                {
                    case 0:
                        _motor->CambiarTexto(campo_web,"Puntuacion Subida.");
                    break;
                    case -1:
                        _motor->CambiarTexto(campo_web,"Usuario no valido.");
                    break;
                    case -2:
                        _motor->CambiarTexto(campo_web,"Credenciales no validos.");
                    break;
                    case -3:
                        _motor->CambiarTexto(campo_web,"Servicio no disponible.");
                    break;
                    case -4:
                        _motor->CambiarTexto(campo_web,"No hay internet o la pagina no responde.");
                    break;
                }
       }    
    }

    if(_motor->OcurreEvento(GUI_ID_REGISTERANDSEND))
    {
        /**/
        int retu;
        if(strlen(nombreUser) > 0 && strlen(nombrePass) > 0)
        {
                puntuar.setUser(nombreUser);
                puntuar.setPass(nombrePass);
                puntuar.setPuntuacion(9000);
                puntuar.setTiempo(30);
                puntuar.setNivel(0);
                retu =  puntuar.subirpuntuacion(true);

                switch(retu)
                {
                    case 0:
                        _motor->CambiarTexto(campo_web,"Puntuacion Subida.");
                    break;
                    case -1:
                        _motor->CambiarTexto(campo_web,"Usuario no valido.");
                    break;
                    case -2:
                        _motor->CambiarTexto(campo_web,"Credenciales no validos.");
                    break;
                    case -3:
                        _motor->CambiarTexto(campo_web,"Servicio no disponible.");
                    break;
                    case -4:
                        _motor->CambiarTexto(campo_web,"No hay internet o la pagina no responde.");
                    break;
                }
        } 
    }



    if (_motor->OcurreEvento(GUI_ID_USER) && campoSeleccion != GUI_ID_USER)
    {
       /**/
       if(campoSeleccion == -1)
       {
            campoSeleccion = GUI_ID_USER;
            _motor->ActivarCapturaTexto();
            _motor->InicializarCaptura(nombreUser);
       }
       else
       {
            campoSeleccion = GUI_ID_USER;
           _motor->DesactivarCapturaTexto();
           _motor->ActivarCapturaTexto();
           _motor->InicializarCaptura(nombreUser);
       }
    }

    if(_motor->OcurreEvento(GUI_ID_PASS) && campoSeleccion != GUI_ID_PASS)
    {
        /**/
        if(campoSeleccion == -1)
        {
                campoSeleccion = GUI_ID_PASS;
                _motor->ActivarCapturaTexto();
                _motor->InicializarCaptura(nombrePass);

        }
        else
        {
            campoSeleccion = GUI_ID_PASS;
            _motor->DesactivarCapturaTexto();
            _motor->ActivarCapturaTexto();
            _motor->InicializarCaptura(nombrePass);
        }
    }
}

void EstadoGanar::pintarBotones()
{
    _motor->CrearBoton(300,200,500,230, GUI_ID_SEND, L"Enviar puntuacion", L"Enviar puntuacion a la web.");
    _motor->CrearBoton(300,240,500,230, GUI_ID_REGISTERANDSEND, L"Registrarse y Enviar", L"Registrate y envia la puntuacion.");
    _motor->CrearBoton(300,280,500,230, GUI_ID_CONTINUAR, L"Siguiente nivel", L"Continua al siguiente nivel");
    _motor->CrearBoton(300,320,500,270, GUI_ID_MENU_BUTTON, L"Menu principal", L"M. principal");
    _motor->CrearBoton(300,360,500,310, GUI_ID_SALIR_BUTTON, L"Salir del juego", L"Cierra el juego");
    _motor->CambiarAnchuraTexto( _motor->CrearTexto("Usuario: ", 300, 145, 300, 20),70);
    _motor->CambiarAnchuraTexto( _motor->CrearTexto("Password: ",300, 175, 300, 20),90);
    _motor->CrearBoton2(400,140,1.0f,170,40,300,GUI_ID_USER,L"Pass",L"assets/images/campoTexto.png",false);//no creamos texto
    _motor->CrearBoton2(400,170,1.0f,170,40,300,GUI_ID_PASS,L"User",L"assets/images/campoTexto.png",false);//no creamos texto
    campo_user = _motor->CrearTexto("",402,150,0,0);
    _motor->CambiarColorTexto(campo_user,0,0,0);
    campo_pass = _motor->CrearTexto("",402,180,0,0);
    _motor->CambiarColorTexto(campo_pass,0,0,0);
    campo_web = _motor->CrearTexto(" ------------------------- ", 300,460,0,0);
    _motor->CambiarAnchuraTexto(campo_web,250);
}

// Para Salir y Menu principal, borra GUI y Escena
void EstadoGanar::borrarEscenaResetearEvento(short id)
{
    _motor->ResetEvento(id);
    // Limpiamos el gui y la escena
    _motor->BorrarScena();
    _motor->BorrarGui();
}

// Para Atras y Reiniciar partida, borra solo los botones del GUI
void EstadoGanar::borrarGUIResetearEvento(short id)
{
    _motor->BorrarElemento(GUI_ID_CONTINUAR);
    _motor->BorrarElemento(GUI_ID_MENU_BUTTON);
    _motor->BorrarElemento(GUI_ID_SALIR_BUTTON);
    _motor->BorrarElemento(GUI_ID_SEND);
    _motor->BorrarElemento(GUI_ID_REGISTERANDSEND);
    _motor->BorrarElemento(GUI_ID_USER);
    _motor->BorrarElemento(GUI_ID_PASS);
    _motor->ResetEvento(id);
}

void EstadoGanar::menuPrincipal()
{
    _motora->getEvent("AmbienteLava")->stop(); //Detener ambiente
    _motora->getEvent("AmbienteGritos")->stop(); //Detener musica ambiente
    _motora->getEvent("Nivel1")->stop(); //Detener musica Juego
    _motora->getEvent("Nivel2")->stop(); //Detener musica Juego
    _motor->LimpiarElementosJuego();
    // Elimina todos los estados y anyade el de menu
    Juego::GetInstance()->estado.CambioDeGanarAMenu();
}

void EstadoGanar::siguienteNivel()
{
    // TO DO: hacer el cambio de nivel
    cout << "Cambio nivel sin hacer - Cierra el juego." <<endl;
}

void EstadoGanar::salir()
{
    _motor->CerrarJuego();
}