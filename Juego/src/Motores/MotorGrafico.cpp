#include "MotorGrafico.hpp" //se llama a su cabecera para bos las dependencias

//para clases singleton deben tener un indicador de que se ha creado el unico objeto
MotorGrafico* MotorGrafico::_unica_instancia = 0;
//fin indicador singleton

/*Tipo 1(640x480), Tipo 2(800x600), Tipo 3(1280x1024), Default(1024x768)
Esta clase define que tipo de pantalla quieres
*/

MotorGrafico::MotorGrafico()
{
    #ifdef WEMOTOR
        //codigo motor catopengl

        _interfaz = nullptr;
        Plataformas_Scena.reserve(200);//salas reservadas
        Luces_Scena.reserve(60);//luces reservadas
        Salas_luz.reserve(20);
        Sprites_Scena.reserve(20);
        Enemigos_Scena.reserve(50);//enemigos reservados
        Textos_Scena.reserve(18);//textos estaticos en la escena o gui
        RecoArmas_Scena.reserve(50);
        RecoArmasAni_Scena.reserve(50);
        Llaves_Scena.reserve(50);
        LlavesAni_Scena.reserve(50);
        Cofres_Scena.reserve(50);
        CofresAni_Scena.reserve(50);
        Objetos_Scena.reserve(100);
        ObjetosAni_Scena.reserve(100);//contiene las logicas de animaciones
        PowerUP_Scena.reserve(50);
        PowerUPAni_Scena.reserve(50);
        Paredes_Scena.reserve(50);
        ParedesAni_Scena.reserve(50);
        Objetos_Debug.reserve(500);
        Objetos_Debug2.reserve(500);
        BoardsArmas_Scena.reserve(500);
        BoardsEnem_Scena.reserve(50);
        BoardsPuertas.reserve(50);
        Particulas_Scena.reserve(100);
        Particulas_Llave.reserve(50);

        camara = 0;
        _jugEscena = 0;
        _aniJugEscena = nullptr;
        debugGrafico = false;
        _armaEnEscena = 0;
        _armaProyectil = 0;
        camx = 0;
        camz = 30;
        cams = -1;
        altura = 0;
        camara1 = true;
        existearmaexp = false;
        _salaActual = 0;

        idCargando = 0;

        tiempo = 0;//tiempo de actualizacion botones

        //para las animaciones
        EnemigosAni_Scena.reserve(50);

    #else
        //codigo motor irrlicht
        input.setDevice(_device);//lo  utilizamos para que los eventos puedan llamar a funciones de
        debugGrafico = false;
        _actual = nullptr;
        _actualTexture = nullptr;

        _aniJugEscena = nullptr;
        frame_actual = 0;
        camx = 0;
        camz = 30;
        cams = -1;
    #endif
}

MotorGrafico::~MotorGrafico()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(_interfaz)
        {
            delete _interfaz;
            _interfaz = nullptr;
        }
    #else
        //codigo motor irrlicht
        //Inputs input
        //position2di initialCursorPosition;        // Posicion del clic raton
        //position2di initialObjectPosition;        // Posicion del objeto que intersecta con el ray

        // Punteros sin new
        _device = nullptr;
        _driver = nullptr;
        _smgr   = nullptr;
        _guienv = nullptr;
        _geometryCreator = nullptr;
        _collmgr = nullptr;
        _camera  = nullptr;
        _font    = nullptr;
        _skin    = nullptr;

        LimpiarElementosJuego();
    #endif
}

void MotorGrafico::LimpiarElementosJuego()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        _interfaz->LimpiarEscena();
        _interfaz->LimpiarGui();
        Plataformas_Scena.clear();
        Enemigos_Scena.clear();
        Textos_Scena.clear();
        RecoArmas_Scena.clear();
        Llaves_Scena.clear();
        Objetos_Scena.clear();
        PowerUP_Scena.clear();
        Paredes_Scena.clear();
        Cofres_Scena.clear();
        Objetos_Debug.clear();
        Objetos_Debug2.clear();
        Particulas_Scena.clear();
        Particulas_Accion.clear();
        Luces_Scena.clear();
        Salas_luz.clear();
        Sprites_Scena.clear();
        BoardsArmas_Scena.clear();
        BoardsEnem_Scena.clear();
        Particulas_Llave.clear();
        BoardsPuertas.clear();

        // TO DO: revisar error munmap_chunk(): invalid pointer
        /*if(_aniJugEscena != nullptr)
        {
            delete _aniJugEscena;
            _aniJugEscena = nullptr;
        }*/

        // TO DO: revisar error de punteros
        int tam = ObjetosAni_Scena.size();
        /*for(int i=0; i < tam; i++)
        {
            if( ObjetosAni_Scena.at(i) != nullptr)
            {
                delete ObjetosAni_Scena.at(i);
            }
        }
        ObjetosAni_Scena.clear();

        tam = ParedesAni_Scena.size();
        for(int i=0; i < tam; i++)
        {
            if( ParedesAni_Scena.at(i) != nullptr)
            {
                delete ParedesAni_Scena.at(i);
            }
        }
        ParedesAni_Scena.clear();*/

        tam = RecoArmasAni_Scena.size();
        for(int i=0; i < tam; i++)
        {
            if( RecoArmasAni_Scena.at(i) != nullptr)
            {
                delete RecoArmasAni_Scena.at(i);
            }
        }
        RecoArmasAni_Scena.clear();

        tam = LlavesAni_Scena.size();
        for(int i=0; i < tam; i++)
        {
            if( LlavesAni_Scena.at(i) != nullptr)
            {
                delete LlavesAni_Scena.at(i);
            }
        }
        LlavesAni_Scena.clear();

        tam = PowerUPAni_Scena.size();
        for(int i=0; i < tam; i++)
        {
            if( PowerUPAni_Scena.at(i) != nullptr)
            {
                delete PowerUPAni_Scena.at(i);
            }
        }
        PowerUPAni_Scena.clear();

        tam = CofresAni_Scena.size();
        for(int i=0; i < tam; i++)
        {
            if( CofresAni_Scena.at(i) != nullptr)
            {
                delete CofresAni_Scena.at(i);
            }
        }
        CofresAni_Scena.clear();

        camara = 0;
        _jugEscena = 0;
        debugGrafico = false;
        _armaEnEscena = 0;
        _armaProyectil = 0;
        camx = 0;
        camz = 30;
        cams = -1;
        altura = 0;
        camara1 = true;
        existearmaexp = false;
        _salaActual = 0;
        _luzDireccional = 0;
        _luzFoco = 0;

        idCargando = 0;

        tiempo = 0;

    #else
        //codigo motor irrlicht
        _armaEnEscena = nullptr;
        _armaProyectil = nullptr;
        _armaEsp = nullptr;
        _armaEspJugador = nullptr;
        _jugEscena = nullptr;
        _linea = nullptr;
        _caja = nullptr;
        _tmpObjEscena = nullptr;

        // Texturas
        vidaI = nullptr;
        energiaI = nullptr;
        dineroI = nullptr;
        armaI = nullptr;
        BarraVidaI = nullptr;
        BarraEnergiaI = nullptr;
        manosI = nullptr;
        llaveI = nullptr;
        espadaI = nullptr;
        dagaI = nullptr;
        moneyI = nullptr;
        vida_textura = nullptr;
        energia_textura = nullptr;
        dinero_textura = nullptr;
        arma_textura = nullptr;
        barraVida_textura = nullptr;
        barraEnergia_textura = nullptr;
        manos_textura = nullptr;
        llave_textura = nullptr;
        espada_textura = nullptr;
        daga_textura = nullptr;

        // Cinematicas
        _actual = nullptr;
        _actualTexture = nullptr;
        frame_actual = 0;
        tiempoUltimoFrame = 0;

        debugGrafico = false;
        pathfinding = false;

        // Liberar memoria
        int tam = Enemigos_Scena.size();
        for(int i=0; i < tam; i++)
        {
            Enemigos_Scena.at(i) = nullptr;
        }
        Enemigos_Scena.clear();

        tam = Objetos_Scena.size();
        for(int i=0; i < tam; i++)
        {
            Objetos_Scena.at(i) = nullptr;
        }
        Objetos_Scena.clear();

        /*tam = Plataformas_Scena.size();
        for(int i=0; i < tam; i++)
        {
            if (Plataformas_Scena.at(i))
                delete Plataformas_Scena.at(i);
        }
        Plataformas_Scena.clear();
        tam = RecoArmas_Scena.size();
        for(int i=0; i < tam; i++)
        {
            delete RecoArmas_Scena.at(i);
        }
        RecoArmas_Scena.clear();
        tam = Llaves_Scena.size();
        for(int i=0; i < tam; i++)
        {
            delete Llaves_Scena.at(i);
        }
        Llaves_Scena.clear();
        tam = PowerUP_Scena.size();
        for(int i=0; i < tam; i++)
        {
            delete PowerUP_Scena.at(i);
        }
        PowerUP_Scena.clear();
        tam = Paredes_Scena.size();
        for(int i=0; i < tam; i++)
        {
            delete Paredes_Scena.at(i);
        }
        Paredes_Scena.clear();
        tam = Luces_Scena.size();
        for(int i=0; i < tam; i++)
        {
            delete Luces_Scena.at(i);
        }
        Luces_Scena.clear();
        tam = Objetos_Debug.size();
        for(int i=0; i < tam; i++)
        {
            delete Objetos_Debug.at(i);
        }
        Objetos_Debug.clear();
        tam = Objetos_Debug2.size();
        for(int i=0; i < tam; i++)
        {
            delete Objetos_Debug2.at(i);
        }
        Objetos_Debug2.clear();*/

        /*tam = fichasMesh.size();
        for(int i=0; i < tam; i++)
        {
            delete fichasMesh.at(i);
        }
        fichasMesh.clear();*/

        //TO DO: Pendiente de utilizar en puzzles
        /*tam = imagenes.size();
        for(int i=0; i < tam; i++)
        {
            delete imagenes.at(i);
        }
        imagenes.clear();*/
    #endif
}

// TO DO: mirar de quitar porque no se usa
void MotorGrafico::LimpiarMotorGrafico()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
    #else
        //codigo motor irrlicht
        //hay que tener  cuidado porque si se borra previamente los objetos apuntan a objetos con memoria no accesible

        if(_jugEscena)
        {
            _jugEscena = nullptr;
        }

        if(Enemigos_Scena.size() > 0)
        {
            for(std::size_t i=0;i<Enemigos_Scena.size();i++)
            {
                Enemigos_Scena[i] = nullptr;
            }

            Enemigos_Scena.resize(0);
        }

        if(Plataformas_Scena.size() > 0)
        {
            for(std::size_t i=0;i < Plataformas_Scena.size();i++)
            {
                Plataformas_Scena[i] = nullptr;
            }

            Plataformas_Scena.resize(0);
        }

        if(Objetos_Scena.size() > 0)
        {
            for(std::size_t i=0;i < Objetos_Scena.size();i++)
            {
                Objetos_Scena[i] = nullptr;
            }

            Objetos_Scena.resize(0);
        }

        if(RecoArmas_Scena.size() > 0)
        {
            for(std::size_t i=0;i < RecoArmas_Scena.size();i++)
            {
                RecoArmas_Scena[i] = nullptr;
            }

            RecoArmas_Scena.resize(0);
        }

        if(Llaves_Scena.size() > 0)
        {
            for(std::size_t i=0;i < Llaves_Scena.size();i++)
            {
                Llaves_Scena[i] = nullptr;
            }

            Llaves_Scena.resize(0);
        }

        if(PowerUP_Scena.size() > 0)
        {
            for(std::size_t i=0;i < PowerUP_Scena.size();i++)
            {
                PowerUP_Scena[i] = nullptr;
            }

            PowerUP_Scena.resize(0);
        }

        if(Paredes_Scena.size() > 0)
        {
            for(std::size_t i=0;i < Paredes_Scena.size();i++)
            {
                Paredes_Scena[i] = nullptr;
            }

            Paredes_Scena.resize(0);
        }

        if(Cofres_Scena.size() > 0)
        {
            for(std::size_t i=0;i < Cofres_Scena.size();i++)
            {
                Cofres_Scena[i] = nullptr;
            }

            Cofres_Scena.resize(0);
        {

        if(Particulas_Scena.size() > 0)
        {
            for(std::size_t i=0;i < Particulas_Scena.size();i++)
            {
                Particulas_Scena[i] = nullptr;
            }

            Particulas_Scena.resize(0);
        }

        if(Salas_luz.size() > 0)
        {
            for(std::size_t i=0;i < Salas_luz.size();i++)
            {
                if(Salas_luz[i].luz.size() > 0)
                {
                    for(std::size_t j=0;j < Salas_luz[i].luz.size();j++)
                    {
                        Salas_luz[i].luz[j] = nullptr;
                    }

                    Salas_luz[i].luz.resize(0);
                }

                Salas_luz[i] = nullptr;
            }

            Salas_luz.resize(0);
        }

        if(Luces_Scena.size() > 0)
        {
            for(std::size_t i=0;i < Luces_Scena.size();i++)
            {
                Luces_Scena[i] = nullptr;
            }

            Luces_Scena.resize(0);
        }

        if(BoardsArmas_Scena.size() > 0)
        {
            for(std::size_t i=0;i < BoardsArmas_Scena.size();i++)
            {
                BoardsArmas_Scena[i] = nullptr;
            }

            BoardsArmas_Scena.resize(0);
        }

        if(BoardsEnem_Scena.size() > 0)
        {
            for(std::size_t i=0;i < BoardsEnem_Scena.size();i++)
            {
                BoardsEnem_Scena[i] = nullptr;
            }

            BoardsEnem_Scena.resize(0);
        }

        _armaEnEscena = nullptr;
        _armaProyectil = nullptr;
        _armaEsp = nullptr;

        /*for (std::vector<Enemigos_Scena*>::iterator it = Enemigos_Scena.begin(); it!=Enemigos_Scena.end(); ++it){
            delete *it;
        }
        Enemigos_Scena.clear();*/

    #endif
}

bool MotorGrafico::CrearVentana(short tipo)
{
    #ifdef WEMOTOR
            //codigo motor catopengl

            if(_interfaz == nullptr)
            {
                _interfaz = new Interfaz();
                CrearCamara();
            }

            configuracion.CargarConfiguracion("config.global");

            GestorInterfaces * _gestori = GestorInterfaces::GetInstance();

            _gestori->UpdateDimensionesVentana(configuracion.GetWidth(),configuracion.GetHeight());

            _gestori->ActualizarParametros();

            std::string titulo = "DeadlyDance Game";
            _interfaz->DefinirVentana(configuracion.GetWidth(),configuracion.GetHeight(),titulo.c_str(),configuracion.GetAllScreen());

            return true;
    #else
        //codigo motor irrlicht
        std::string titulo = "";
        switch(tipo)
        {
            case 1:
                width=640; height=480;
                titulo = "DeadlyDance LowResolution";
                break;

            case 2:
                width=800; height=600;
                titulo = "DeadlyDance MediumResolution";
                break;

            case 3:
                width=1280; height=1024;
                titulo = "DeadlyDance HightResolution";
                break;

            default:
                width=1024; height=768;
                titulo = "DeadlyDance NormalResolution";
                break;
        }
        _device = createDevice( video::EDT_SOFTWARE, dimension2d<u32>(width, height), 16,false, false, false, &input);

        std::wstring widestr = std::wstring(titulo.begin(), titulo.end());
        _device->setWindowCaption(widestr.c_str());

        _device->setResizable(false);
        propiedadesDevice();
        return true;
    #endif
}

bool MotorGrafico::VentanaAbierta()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(_interfaz != nullptr)
        {
            return _interfaz->VentanaEstaAbierta();
        }
        return false;
    #else
        //codigo motor irrlicht
        return _device->run();
    #endif
}

void MotorGrafico::CerrarJuego()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(_interfaz != nullptr)
        {
            _interfaz->CerrarVentana();
        }
    #else
        //codigo motor irrlicht
        _device->closeDevice();
    #endif
}

/* Una vez que hayamos terminado con el bucle de procesamiento, debemos eliminar
 * el dispositivo creado antes con createDevice()
 */
void MotorGrafico::LimpiarDevice()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(_interfaz != nullptr)
        {
            delete _interfaz;
            _interfaz = nullptr;
        }
    #else
        //codigo motor irrlicht
        _device->drop();
    #endif
}

void MotorGrafico::propiedadesDevice()
{
    #ifdef WEMOTOR
        //codigo motor catopengl

        _interfaz = new Interfaz;
        //esto solo con la interfaz, no tenemos accesos por separados a la interfaz del motor esta unificada

    #else
        //codigo motor irrlicht
        //cout << "\e[32m Aplicando propiedades a _device \e[0m" << endl;
        _driver = _device->getVideoDriver();
        _smgr = _device->getSceneManager();
        _guienv = _device->getGUIEnvironment();
        _geometryCreator = _smgr->getGeometryCreator();
        _collmgr = _smgr->getSceneCollisionManager();

        //cout << "\e[32m Propiedades aplicadas \e[0m" << endl;
    #endif
}

void MotorGrafico::ActivarFuenteDefault()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        //no se carga
    #else
        //codigo motor irrlicht
        _skin = _guienv->getSkin();
        _font = _guienv->getFont("assets/fonts/default.bmp");
        if (_font)
        {
            _skin->setFont(_font);
            //cout << "\e[36m Se encuentra fuente \e[0m" << endl;
        }
        _skin->setFont(_guienv->getBuiltInFont(), EGDF_TOOLTIP);
    #endif
}

// Se puede dibujar cualquier cosa entre una llamada beginScene() y una llamada endScene()
void MotorGrafico::FondoEscena(int a, int r, int g, int b)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        _interfaz->CambiarFondo(r,g,b,a);
    #else
        //codigo motor irrlicht
        //Borra la pantalla con un color
        _driver->beginScene(true, true, SColor(a,r,g,b));
    #endif
}

void MotorGrafico::FondoEscena(float a, float r, float g, float b)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        _interfaz->CambiarFondo(r,g,b,a);
    #else
        //codigo motor irrlicht
        //Borra la pantalla con un color
        _driver->beginScene(true, true, SColor(a,r,g,b));
    #endif
}

void MotorGrafico::RenderEscena()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(_interfaz != nullptr)
        {
            _interfaz->Draw();//pintamos la escena
            updateTeclas();//actualiza los estados de los botones
            //std::cout << GetPosicionRaton()[0] << " " << GetPosicionRaton()[1] << std::endl;
            for(unsigned int i = 0; i < ObjetosAni_Scena.size();i++)
            {
                if(ObjetosAni_Scena[i] != nullptr)//solo esta objetos luego seran todos los objetos
                {
                    ActualizarAnimacionMotor(ObjetosAni_Scena[i]);
                }
            }
            for(unsigned int i = 0; i < EnemigosAni_Scena.size();i++)
            {
                if(EnemigosAni_Scena[i] != nullptr)//solo esta objetos luego seran todos los objetos
                {
                    ActualizarAnimacionMotor(EnemigosAni_Scena[i]);
                }
            }
            for(unsigned int i = 0; i < CofresAni_Scena.size();i++)
            {
                if(CofresAni_Scena[i] != nullptr)//solo esta objetos luego seran todos los objetos
                {
                    ActualizarAnimacionMotor(CofresAni_Scena[i]);
                }
            }
            Times * tiempo = Times::GetInstance();
            unsigned int fps = tiempo->GetFramesPorSegundo();

            //if(debugGrafico)
            //{
                //_interfaz->DefinirVentana(800,600,std::to_string(fps).c_str());
            //}

        }
    #else
        //codigo motor irrlicht
        // Antes de dibujar el contenido, se llama a FondoEscena en los renders de estado
        _smgr->drawAll();
        _guienv->drawAll();
        _driver->endScene(); // Termina y saca por pantalla
    #endif
}

void MotorGrafico::BorrarScena()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(_interfaz != nullptr)
        {
            _interfaz->LimpiarEscena();
        }
    #else
        //codigo motor irrlicht
        _smgr->clear();
    #endif
}

void MotorGrafico::BorrarGui()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(_interfaz != nullptr)
        {
            _interfaz->LimpiarGui();
        }
    #else
        //codigo motor irrlicht
        _guienv->clear();
    #endif
}

unsigned int MotorGrafico::CrearTexto(std::string texto, short x1, short y1, short x2, short y2)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        unsigned short num = _interfaz->CrearTexto(texto,x1,y1,255.0f,255.0f,255.0f);//crea el texto en pantalla con los valores por defecto
        Textos_Scena.push_back(num);//lo introducimos en la matriz de objetos
        return (unsigned int)num;
    #else
        //codigo motor irrlicht
        std::wstring widestr = std::wstring(texto.begin(), texto.end());
        // Parametro false, indica que no pinte el recuadro alrededor del texto
        _guienv->addStaticText(widestr.c_str(), rect<s32>(x1, y1, x2, y2), false);
    #endif
}

void MotorGrafico::CrearBoton(short x, short y, short x2, short y2, signed int id,
    const wchar_t* texto, const wchar_t* texto2)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        unsigned short num = _interfaz->AddImagen("assets/images/boton3.png",x,y,1.0f,"assets/images/boton3p.png","assets/images/boton3e.png");
        if(num != 0)
        {
            _interfaz->DeclararBoton(num,id);
            _interfaz->DefinirIdPersonalizado(num,id);
            wstring ws(texto);
            string str(ws.begin(),ws.end());
            unsigned short num2 = _interfaz->CrearTexto(str,(x+25),(y+20),255.0f,255.0f,255.0f);
            _interfaz->DefinirTextoBoton(num,num2);
        }
    #else
        //codigo motor irrlicht
        _guienv->addButton(rect<s32>(x,y,x2,y2), 0, id, texto, texto2);
    #endif
}

bool MotorGrafico::OcurreEvento(short event)
{
    #ifdef WEMOTOR

        //codigo motor catopengl
        if(_interfaz != nullptr && _interfaz->DetectarPulsacion(event))
        {
            if(EstaPulsado(idsEventos::Enum::LMOUSE_PRESSED_DOWN))
            {
                //si esta pulsado entonces cambiar estado 2 PRESIONADO
                _interfaz->CambiarEstadoImagen(event,2);
                //std::cout << "pulsado " << event << std::endl;
                return true;
            }
            else
            {
                //si esta encima cambiar estado 3 ENCIMA
                _interfaz->CambiarEstadoImagen(event,3);
                //std::cout << "encima " << event << std::endl;
                return false;
            }
        }
        else
        {
            //esto es que no ocurre le decimos que actualice con estado 1 (que es el normal) NORMAL
            _interfaz->CambiarEstadoImagen(event,1);
            //std::cout << "normal " << event << std::endl;
            return false;
        }

    #else
        //codigo motor irrlicht
        return input.IsEventOn(event);
    #endif
}

void MotorGrafico::ResetEvento(short event)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        //de momento nada
    #else
        //codigo motor irrlicht
        input.ResetEvento(event);
    #endif
}

bool MotorGrafico::EstaPulsado(short boton)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        switch(boton)
        {
            case idsEventos::Enum::KEY_A:
                return estadoteclas[GLFW_KEY_A];

            case idsEventos::Enum::KEY_S:
                return estadoteclas[GLFW_KEY_S];

            case idsEventos::Enum::KEY_D:
                return estadoteclas[GLFW_KEY_D];

            case idsEventos::Enum::KEY_W:
                return estadoteclas[GLFW_KEY_W];

            case idsEventos::Enum::KEY_ESC:
                return estadoteclas[GLFW_KEY_ESCAPE];

            case idsEventos::Enum::KEY_ESPACIO:
                return estadoteclas[GLFW_KEY_SPACE];

            case idsEventos::Enum::KEY_ACEPTAR:
                return estadoteclas[GLFW_KEY_ENTER];

            case idsEventos::Enum::KEY_G_DEBUG:
                return estadoteclas[GLFW_KEY_G];//para modo debug

            case idsEventos::Enum::KEY_1:
                return estadoteclas[GLFW_KEY_1];

            case idsEventos::Enum::KEY_2:
                return estadoteclas[GLFW_KEY_2];

            case idsEventos::Enum::KEY_U:
                return estadoteclas[GLFW_KEY_U];//para desactivar colisiones jugador

            case idsEventos::Enum::KEY_P:
                return estadoteclas[GLFW_KEY_P];

            case idsEventos::Enum::KEY_K:
                return estadoteclas[GLFW_KEY_K];

            case idsEventos::Enum::KEY_C:
                return estadoteclas[GLFW_KEY_C];//activa pathdinding

            case idsEventos::Enum::KEY_B:
                return estadoteclas[GLFW_KEY_B];

            case idsEventos::Enum::RMOUSE_PRESSED_DOWN:
                return estadoteclas[GLFW_MOUSE_BUTTON_RIGHT];

            case idsEventos::Enum::LMOUSE_PRESSED_DOWN:
                return estadoteclas[GLFW_MOUSE_BUTTON_LEFT];

            case idsEventos::Enum::MOUSE_MOVED:
                return estadoteclas[GLFW_MOUSE_MOVE];

            case idsEventos::Enum::KEY_Q:
                return estadoteclas[GLFW_KEY_Q];

            case idsEventos::Enum::KEY_H:
                return estadoteclas[GLFW_KEY_H];

            case idsEventos::Enum::KEY_I:
                return estadoteclas[GLFW_KEY_I];

            case idsEventos::Enum::KEY_J:
                return estadoteclas[GLFW_KEY_J];//Para matar al jugador (16)

            case idsEventos::Enum::KEY_Z:
                return estadoteclas[GLFW_KEY_Z];//Para abrir 1 puzzle

            case idsEventos::Enum::KEY_E:
                return estadoteclas[GLFW_KEY_E];//actua una sola vez aunque se mantenga pulsado

            case idsEventos::Enum::KEY_DEL:
                return estadoteclas[GLFW_KEY_BACKSPACE];
        }

        return false;
    #else
        //codigo motor irrlicht
        switch(boton)
        {
            case KEY_A:
                return input.IsKeyDown(irr::KEY_KEY_A);

            case KEY_S:
                return input.IsKeyDown(irr::KEY_KEY_S);

            case KEY_D:
                return input.IsKeyDown(irr::KEY_KEY_D);

            case KEY_W:
                return input.IsKeyDown(irr::KEY_KEY_W);

            case KEY_ESC:
                return input.IsKeyDown(irr::KEY_ESCAPE);

            case KEY_ESPACIO:
                return input.IsKeyDown(irr::KEY_SPACE);

            case KEY_ACEPTAR:
                return input.IsKeyDown(irr::KEY_ACCEPT);

            case KEY_G_DEBUG:
                return input.IsKeyDown(irr::KEY_KEY_G);//para modo debug

            case KEY_1:
                return input.IsKeyDown(irr::KEY_KEY_1);

            case KEY_2:
                return input.IsKeyDown(irr::KEY_KEY_2);
            case KEY_P:
                return input.IsKeyDown(irr::KEY_KEY_P);

            case KEY_K:
                return input.IsKeyDown(irr::KEY_KEY_K);

            case KEY_C:
                return input.IsKeyDown(irr::KEY_KEY_C);//activa pathdinding

            case KEY_B:
                return input.IsKeyDown(irr::KEY_KEY_B);

            case RMOUSE_PRESSED_DOWN:
                return input.IsMouseClick(irr::EMIE_RMOUSE_PRESSED_DOWN);

            case LMOUSE_PRESSED_DOWN:
                return input.IsMouseClick(irr::EMIE_LMOUSE_PRESSED_DOWN);

            case MOUSE_MOVED:
                return input.IsMouseClick(irr::EMIE_MOUSE_MOVED);

            case KEY_Q:
                return input.IsKeyDown(irr::KEY_KEY_Q);

            case KEY_H:
                return input.IsKeyDown(irr::KEY_KEY_H);

            case KEY_I:
                return input.IsKeyDown(irr::KEY_KEY_I);

            case KEY_J:
                return input.IsKeyDown(irr::KEY_KEY_J);//Para matar al jugador (16)

            case KEY_Z:
                return input.IsKeyDown(irr::KEY_KEY_Z);// Para abrir 1 puzzle

            case KEY_E:
                return input.IsKeyPressed(irr::KEY_KEY_E);//actua una sola vez aunque se mantenga pulsado
        }
        return false;
    #endif
}

void MotorGrafico::ResetKey(short event)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        switch(event)
        {
            case idsEventos::Enum::KEY_A:
                estadoteclas[GLFW_KEY_A] = false;
            break;
            case idsEventos::Enum::KEY_S:
                estadoteclas[GLFW_KEY_S] = false;
            break;
            case idsEventos::Enum::KEY_D:
                estadoteclas[GLFW_KEY_D] = false;
            break;
            case idsEventos::Enum::KEY_W:
                estadoteclas[GLFW_KEY_W]  = false;
            break;
            case idsEventos::Enum::KEY_ESC:
                estadoteclas[GLFW_KEY_ESCAPE] = false;
            break;
            case idsEventos::Enum::KEY_ESPACIO:
                estadoteclas[GLFW_KEY_SPACE] = false;
            break;
            case idsEventos::Enum::KEY_ACEPTAR:
                estadoteclas[GLFW_KEY_ENTER] = false;
            break;
            case idsEventos::Enum::KEY_G_DEBUG:
                estadoteclas[GLFW_KEY_G] = false;//para modo debug
            break;
            case idsEventos::Enum::KEY_1:
                estadoteclas[GLFW_KEY_1] = false;
            break;
            case idsEventos::Enum::KEY_2:
                estadoteclas[GLFW_KEY_2] = false;
            break;
            case idsEventos::Enum::KEY_U:
                estadoteclas[GLFW_KEY_U] = false;//para desactivar colisiones jugador
            break;
            case idsEventos::Enum::KEY_P:
                estadoteclas[GLFW_KEY_P] = false;
            break;
            case idsEventos::Enum::KEY_K:
                estadoteclas[GLFW_KEY_K] = false;
            break;
            case idsEventos::Enum::KEY_C:
                estadoteclas[GLFW_KEY_C] = false;//activa pathdinding
            break;
            case idsEventos::Enum::KEY_B:
                estadoteclas[GLFW_KEY_B] = false;
            break;
            case idsEventos::Enum::RMOUSE_PRESSED_DOWN:
                estadoteclas[GLFW_MOUSE_BUTTON_RIGHT] = false;
            break;
            case idsEventos::Enum::LMOUSE_PRESSED_DOWN:
                estadoteclas[GLFW_MOUSE_BUTTON_LEFT] = false;
            break;
            case idsEventos::Enum::MOUSE_MOVED:
                estadoteclas[GLFW_MOUSE_MOVE] = false;
            break;
            case idsEventos::Enum::KEY_Q:
                estadoteclas[GLFW_KEY_Q] = false;
            break;
            case idsEventos::Enum::KEY_H:
                estadoteclas[GLFW_KEY_H] = false;
            break;
            case idsEventos::Enum::KEY_I:
                estadoteclas[GLFW_KEY_I] = false;
            break;
            case idsEventos::Enum::KEY_J:
                estadoteclas[GLFW_KEY_J] = false;//Para matar al jugador (16)
            break;
            case idsEventos::Enum::KEY_Z:
                estadoteclas[GLFW_KEY_Z] = false;//Para abrir 1 puzzle
            break;
            case idsEventos::Enum::KEY_E:
                estadoteclas[GLFW_KEY_E] = false;//actua una sola vez aunque se mantenga pulsado
            break;
            case idsEventos::Enum::KEY_DEL:
                estadoteclas[GLFW_KEY_BACKSPACE] = false;
            break;
        }
    #else
        //codigo motor irrlicht
        switch(event)
        {
            case KEY_A:
                input.ResetKey(irr::KEY_KEY_A);
            break;
            case KEY_S:
                input.ResetKey(irr::KEY_KEY_S);
            break;
            case KEY_D:
                input.ResetKey(irr::KEY_KEY_D);
            break;
            case KEY_W:
                input.ResetKey(irr::KEY_KEY_W);
            break;
            case KEY_ESC:
                input.ResetKey(irr::KEY_ESCAPE);
            break;
            case KEY_ESPACIO:
                input.ResetKey(irr::KEY_SPACE);
            break;
            case KEY_ACEPTAR:
                input.ResetKey(irr::KEY_ACCEPT);
            break;
            case KEY_G_DEBUG:
                input.ResetKey(irr::KEY_KEY_G);//para modo debug
            break;
            case KEY_1:
                input.ResetKey(irr::KEY_KEY_1);
            break;
            case KEY_2:
                input.ResetKey(irr::KEY_KEY_2);
            break;
            case KEY_U:
                input.ResetKey(irr::KEY_KEY_U);//para modo debug
            break;
            case KEY_P:
                input.ResetKey(irr::KEY_KEY_P);
            break;
            case KEY_K:
                input.ResetKey(irr::KEY_KEY_K);
            break;
            case KEY_C:
                input.ResetKey(irr::KEY_KEY_C);
            break;
            case KEY_B:
                input.ResetKey(irr::KEY_KEY_B);
            break;
            case KEY_Q:
                input.ResetKey(irr::KEY_KEY_Q);
            break;
            case KEY_H:
                input.IsKeyDown(irr::KEY_KEY_H);
            break;
            case KEY_I:
                input.IsKeyDown(irr::KEY_KEY_I);
            break;
            case KEY_J:
                input.IsKeyDown(irr::KEY_KEY_J);//Para matar al jugador (16)
            break;
            case KEY_Z:
                input.IsKeyDown(irr::KEY_KEY_Z);
            break;
            case KEY_E:
                input.ResetKey(irr::KEY_KEY_E);
            break;
        }
    #endif
}

bool MotorGrafico::PulsadoClicDer()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        return estadoteclas[GLFW_MOUSE_BUTTON_RIGHT];
    #else
        //codigo motor irrlicht
        return input.PulsadoClicDer();
    #endif
}

bool MotorGrafico::PulsadoClicIzq()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        return estadoteclas[GLFW_MOUSE_BUTTON_LEFT];
    #else
        //codigo motor irrlicht
        return input.PulsadoClicIzq();
    #endif
}

bool MotorGrafico::SueltoClicDer()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
       return estadoteclas[GLFW_MOUSE_BUTTON_RIGHT];
    #else
        //codigo motor irrlicht
        return input.SueltoClicDer();
    #endif
}

bool MotorGrafico::SueltoClicIzq()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        return estadoteclas[GLFW_MOUSE_BUTTON_LEFT];
    #else
        //codigo motor irrlicht
        return input.SueltoClicIzq();
    #endif
}

void MotorGrafico::ResetEventoMoveRaton()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        estadoteclas[GLFW_MOUSE_MOVE] = false;
    #else
        //codigo motor irrlicht
        input.ResetEventoRaton(irr::EMIE_MOUSE_MOVED);
    #endif
}

#ifdef WEMOTOR
    //codigo motor catopengl
    double * MotorGrafico::GetPosicionRaton()
    {
        return _interfaz->GetPosicionRaton();
    }
#else
    //codigo motor irrlicht
    position2di MotorGrafico::GetPosicionRaton()
    {
        return input.GetMouseState().Position;
    }
#endif

void MotorGrafico::CrearCamara()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        camara = _interfaz->AddCamara();//creamos la camara
        if(camara != 0)
        {
            _interfaz->Trasladar(camara,0,20,-20);//movemos la camara
            _interfaz->ChangeTargetCamara(camara,0,0,0);//enfocamos la camara al centro
        }
    #else
        //codigo motor irrlicht
        //primer vector traslacion, segundo rotacion
        //  _smgr->addCameraSceneNode(0, vector3df(0,0,90), vector3df(0,0,0));
        _camera = _smgr->addCameraSceneNode(0, vector3df(0,20,-20), vector3df(0,0,0));
        //camera->setNearValue(0.5f);
        //camera->setFarValue(100.0f);
    #endif
}

bool MotorGrafico::GetDebugActivado()
{
        return debugGrafico;
}


// ------------------------------------ Revisar

int MotorGrafico::CargarPlataformas(int rp, int x,int y,int z, int ancho, int largo, int alto, const char *ruta_objeto,const char *ruta_textura)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        unsigned short objeto = _interfaz->AddMalla(ruta_objeto,1,0);//instanciamos el objeto y lo agregamos a la escena
        _interfaz->SetTexture(objeto,ruta_textura);
        if(objeto != 0)
        {
            //cout << "colocar plataforma en: " << x << y << z << endl;
            _interfaz->Trasladar(objeto,(float)x,(float)y,(float)z);//movemos el objeto
            _interfaz->Rotar(objeto,(float)0,(float)rp,(float)0);//giramos el objeto
            Plataformas_Scena.push_back(objeto);//lo introducimos en la matriz de objetos
            return (Plataformas_Scena.size()-1);//devolvemos el valor
        }
        else
        {
            return -1;
        }


    #else
        //codigo motor irrlicht
        IAnimatedMesh* objeto = _smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
        if (!objeto)
        {
            //error
            return -1;//no se ha podido crear esta sala
        }
        else
        {
            IAnimatedMeshSceneNode* _objetoEnEscena = _smgr->addAnimatedMeshSceneNode(objeto); //metemos el objeto en el escenario para eso lo pasamos al escenario
            _objetoEnEscena->setPosition(core::vector3df(x,y,z));
            _objetoEnEscena->setRotation(core::vector3df(0,rp,0));
            _objetoEnEscena->setMaterialTexture(0, _driver->getTexture(ruta_textura));
            Plataformas_Scena.push_back(_objetoEnEscena);
            return (Plataformas_Scena.size()-1);
        }
    #endif
}

void MotorGrafico::CargarLuces(int x,int y,int z,int r,int g,int b,int tipo,float dist,int anim)
{
    #ifdef WEMOTOR

        //codigo motor catopengl
        unsigned short luz = _interfaz->AddLuz(tipo,anim);//instanciamos el objeto y lo agregamos a la escena
        if(luz != 0 && tipo == 1)
        {
            _interfaz->Trasladar(luz,(float)x,(float)y,(float)z);//movemos el objeto
            _interfaz->DistanciaLuz(luz,dist);
            _interfaz->DeshabilitarObjeto(luz);
            Luces_Scena.push_back(luz);//agregamos la luz
        }
        else if(luz != 0 && tipo == 0)
        {
            _luzDireccional = luz;
        }
        else if(luz != 0 && tipo == 2)
        {
            _luzFoco = luz;
        }

        _interfaz->ColorAmbiental(luz,(float)r,(float)g,(float)b);
        _interfaz->ColorDifusa(luz,(float)r,(float)g,(float)b);
        _interfaz->ColorSpecular(luz,(float)r,(float)g,(float)b);

    #else
        //codigo motor irrlicht
        // add light 1 (more green)
        scene::ILightSceneNode* light1 =
        _smgr->addLightSceneNode(0, core::vector3df(x,y,z),video::SColorf(0.5f, 1.0f, 0.5f, 0.0f), 100.0f);

        light1->setDebugDataVisible ( scene::EDS_BBOX );


        // add fly circle animator to light 1
        scene::ISceneNodeAnimator* anim = _smgr->createFlyCircleAnimator (core::vector3df(x,y,z),0.0f, -0.003f);
        light1->addAnimator(anim);
        anim->drop();

        Luces_Scena.push_back(light1);
        // attach billboard to the light
        scene::IBillboardSceneNode* bill =
            _smgr->addBillboardSceneNode(light1, core::dimension2d<f32>(10, 10));

        bill->setMaterialFlag(video::EMF_LIGHTING, false);
        bill->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
        bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
        bill->setMaterialTexture(0, _driver->getTexture("assets/models/particlegreen.jpg"));
    #endif
}

void MotorGrafico::CargarParticulas(int x, int y, int z, int velocidadx, int velocidady, int velocidadz, float escala, unsigned int nparticulas, float localz, float tvida, const char* ruta_textura)
{
    //Crea el sistema de particulas
    unsigned short particulas = _interfaz->AddParticles((float)velocidadx,(float)velocidady,(float)velocidadz,nparticulas,localz,tvida,ruta_textura);
    _interfaz->Escalar(particulas,escala,escala,escala);
    _interfaz->Trasladar(particulas,(float)x,(float)y,(float)z);
    _interfaz->DeshabilitarObjeto(particulas);
    Particulas_Scena.push_back(particulas);
}

void MotorGrafico::CargarParticulasAccion(int x, int y, int z, int velocidadx, int velocidady, int velocidadz, float escala, unsigned int nparticulas, float localz, float tvida, const char* ruta_textura)
{
    //Crea el sistema de particulas
    unsigned short particulas = _interfaz->AddParticles((float)velocidadx,(float)velocidady,(float)velocidadz,nparticulas,localz,tvida,ruta_textura);
    _interfaz->Escalar(particulas,escala,escala,escala);
    _interfaz->Trasladar(particulas,(float)x,(float)y,(float)z);
    _interfaz->DetenerSistema(particulas);
    Particulas_Accion.push_back(particulas);
}

void MotorGrafico::IniciarParticulasAccion(unsigned short i, float x, float y, float z, float time)
{
    _interfaz->Trasladar(Particulas_Accion[i],x,y+5.0f,z);
    _interfaz->IniciarSistema(Particulas_Accion[i],time);
}

void MotorGrafico::CargarSalaLuz(int sala,int minz,int maxz,int minx,int maxx)
{
    SalasLuz luzsala;
    luzsala.sala = sala;
    luzsala.minz = minz;
    luzsala.maxz = maxz;
    luzsala.minx = minx;
    luzsala.maxx = maxx;
    Salas_luz.push_back(luzsala);
}

void MotorGrafico::CargarLuzEnSala(int sala,int x,int y,int z)
{
    glm::vec3 posluz = glm::vec3(x,y,z);
    Salas_luz[sala - 1].luz.push_back(posluz);
}


int MotorGrafico::CargarEnemigos(int x,int y,int z, const char* ruta_objeto, const char* ruta_textura, bool boss, const char * anima, unsigned int fps,float distanciaboard)
{
    #ifdef WEMOTOR

        //codigo motor catopengl

        unsigned short enemigo = _interfaz->AddMalla(ruta_objeto,fps,0);
        _interfaz->SetTexture(enemigo,ruta_textura);

        if(enemigo != 0)
        {
            _interfaz->Trasladar(enemigo,(float)x,(float)y,(float)z);
            if(boss)
            {
                Enemigos_Scena.insert(Enemigos_Scena.begin(), enemigo);
            }
            else
            {
                Enemigos_Scena.push_back(move(enemigo));
            }

            if(anima && anima != nullptr)
            {

                Animaciones * _ani = new Animaciones(anima);//cargamos las animaciones
                _ani->AsignarID(enemigo);
                
                if(boss)
                {
                    EnemigosAni_Scena.insert(EnemigosAni_Scena.begin(),_ani);
                }
                else
                {
                    EnemigosAni_Scena.push_back(_ani);
                }

                //std::cout << ruta_objeto << " "  << fps << " " << anima << " " << EnemigosAni_Scena.size()-1 << "\n";
            }
            else
            {
                EnemigosAni_Scena.push_back(nullptr);
            }

            //Crear billboard
            unsigned short _board = _interfaz->AddBoard(0,0,0, -1.0f, 0, "assets/images/4.png", 0.01f);
            _interfaz->Trasladar(_board,(float)x+4.0f,(float)y+10.0f+distanciaboard,(float)z);
            _interfaz->Escalar(_board,2.0f,0.15f,1.75f);
            _interfaz->DeshabilitarObjeto(_board);
            if(boss)
            {
                _interfaz->Trasladar(_board,(float)x+4.0f,(float)y+40.0f,(float)z);
                BoardsEnem_Scena.insert(BoardsEnem_Scena.begin(), _board);
            }
            else
            {
                BoardsEnem_Scena.push_back(move(_board));
            }
        
        if(boss)
        {
            return 0;
        }
        else
        {
            return (Enemigos_Scena.size()-1);
        }

        }

    return -1;
    #else

        //codigo motor irrlicht
        IAnimatedMesh* enemigo = _smgr->getMesh(ruta_objeto); //creamos el objeto en memoria

        if (enemigo)
        {
            IAnimatedMeshSceneNode* enemigo_en_scena = _smgr->addAnimatedMeshSceneNode(enemigo); //metemos el objeto en el escenario para eso lo pasamos al escenario
            enemigo_en_scena->setPosition(core::vector3df(x,y,z));
            Enemigos_Scena.push_back(move(enemigo_en_scena));
        }

        return -1;
    #endif
}

/******----------------Cargar Jugador------------------******
 * Metodo que sirve para generar la malla 3D de un jugador
 * al iniciar estado Juego.
 * Entradas:
 *      ruta_objeto: string con la direccion del modelo 3D
 *      ruta_textura: string con la ruta de la textura
 * Salida:
 *
 */
void MotorGrafico::CargarJugador(int x,int y,int z, int ancho, int largo, int alto, const char* ruta_objeto)
{
    #ifdef WEMOTOR
        //codigo motor catopengl

        _jugEscena = _interfaz->AddMalla(ruta_objeto,128,0);
        //_interfaz->SetColor(_jugEscena,250,50,50,255); //color RGBA

        if(_jugEscena != 0)
        {
            _interfaz->SetTexture(_jugEscena,"assets/models/rockero/HeavyTex.png");
            _interfaz->Trasladar(_jugEscena,(float)x,(float)y,(float)z);
            _interfaz->Escalar(_jugEscena,(float)1.75,(float)1.75,(float)1.75);
            _aniJugEscena = new Animaciones("assets/animaciones/rockero.xml");//cargamos las animaciones
            _aniJugEscena->AsignarID(_jugEscena);//definimos el id para cuando luego se actualice sepa que id tiene
            //cout << _jugEscena << " INICIALMENTE: " << x << " " << y << " " << z << endl;
        }

    #else
        //codigo motor irrlicht
        IAnimatedMesh* jugador = _smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
        // Si se ha podido crear el objeto, se mete en escena
        if (jugador)
        {
            _jugEscena = _smgr->addAnimatedMeshSceneNode(jugador); //metemos el objeto en el escenario para eso lo pasamos al escenario
            //cout << x << " " << y << " " << z << " " << endl;
            _jugEscena->setPosition(core::vector3df(x,y,z));
            _jugEscena->setScale(core::vector3df(1.75,1.75,1.75));
            _jugEscena->setFrameLoop(30, 44);
            _jugEscena->setAnimationSpeed(10);
            colorearJugador(255, 255, 255, 255);
            //const SColor COLOR  = SColor(255,0,0,255);
            //smgr->getMeshManipulator()->setVertexColors(_jugEscena->getMesh(),COLOR);
        }
        //jugador = nullptr;
    #endif
}

int MotorGrafico::CargarObjetos(int accion, int rp, int x,int y,int z, int ancho, int largo, int alto,
    const char *ruta_objeto, const char *ruta_textura, const char * anima, int frame, bool afectaluz)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        unsigned short _objetoEnEscena;
        if(afectaluz == true){
            _objetoEnEscena = _interfaz->AddMalla(ruta_objeto,frame,0);
        }else{
            _objetoEnEscena = _interfaz->AddMalla(ruta_objeto,frame,1);
        }

        //cout << "colocar objeto en: " << x << y << z << endl;
        if(_objetoEnEscena != 0)
        {
            _interfaz->SetTexture(_objetoEnEscena,ruta_textura);
            _interfaz->Trasladar(_objetoEnEscena,(float)x,(float)y,(float)z);
            _interfaz->Rotar(_objetoEnEscena,0.0f,(float)rp,0.0f);

            Animaciones * logicaAnim = nullptr;

            if(anima != nullptr)
            {
                logicaAnim = new Animaciones(anima);
                logicaAnim->AsignarID(_objetoEnEscena);
                ObjetosAni_Scena.push_back(logicaAnim);
            }

            if(accion == 9) // Lagunas, cristales y cosas transparentes
            {
                Objetos_Scena.push_back(_objetoEnEscena);
                ObjetosAni_Scena.push_back(logicaAnim);
                mallaTransparente(_objetoEnEscena, 0.4);
                return Objetos_Scena.size() - 1;
            }

            if(accion == 8)
            {
                Llaves_Scena.push_back(_objetoEnEscena);
                LlavesAni_Scena.push_back(logicaAnim);

                //Crear particulas
                unsigned short particulas = _interfaz->AddParticles(0.0f,6.0f,0.0f,20,5.0f,3.5f,"assets/images/ParticulaLlave.png");
                _interfaz->Trasladar(particulas,(float)x+1.0f,(float)y+2.0f,(float)z);
                _interfaz->Escalar(particulas,0.5f,0.5f,0.5f);
                Particulas_Llave.push_back(particulas);

                return Llaves_Scena.size() - 1;
            }

            if(accion == 5)
            {
                Paredes_Scena.push_back(_objetoEnEscena);
                ParedesAni_Scena.push_back(logicaAnim);
                return Paredes_Scena.size() - 1;
            }

            if(accion == 4)
            {
                PowerUP_Scena.push_back(_objetoEnEscena);
                PowerUPAni_Scena.push_back(logicaAnim);
                return PowerUP_Scena.size() - 1;
            }

            //RecoArmas_Scena solo tiene armas
            if(accion == 2)
            {
                //crear y guardar bill boards armas
                unsigned short _board1 = _interfaz->AddBoard(0,0,0, -1.0f, 0, "assets/images/masA.png", 0.01f);
                _interfaz->Trasladar(_board1,(float)x,(float)y+4,(float)z);
                _interfaz->Escalar(_board1,1.75f,1.25f,1.75f);
                _interfaz->DeshabilitarObjeto(_board1);
                unsigned short _board2 = _interfaz->AddBoard(0,0,0, 1.0f, 0, "assets/images/masD.png", 0.01f);
                _interfaz->Trasladar(_board2,(float)x,(float)y+4,(float)z);
                _interfaz->Escalar(_board2,1.75f,1.25f,1.75f);
                _interfaz->DeshabilitarObjeto(_board2);
                unsigned short _board3 = _interfaz->AddBoard(0,0,0, -1.0f, 0, "assets/images/igualA.png", 0.01f);
                _interfaz->Trasladar(_board3,(float)x,(float)y+4,(float)z);
                _interfaz->Escalar(_board3,1.75f,1.25f,1.75f);
                _interfaz->DeshabilitarObjeto(_board3);
                unsigned short _board4 = _interfaz->AddBoard(0,0,0, 1.0f, 0, "assets/images/igualD.png", 0.01f);
                _interfaz->Trasladar(_board4,(float)x,(float)y+4,(float)z);
                _interfaz->Escalar(_board4,1.75f,1.25f,1.75f);
                _interfaz->DeshabilitarObjeto(_board4);
                unsigned short _board5 = _interfaz->AddBoard(0,0,0, -1.0f, 0, "assets/images/menosA.png", 0.01f);
                _interfaz->Trasladar(_board5,(float)x,(float)y+4,(float)z);
                _interfaz->Escalar(_board5,1.75f,1.25f,1.75f);
                _interfaz->DeshabilitarObjeto(_board5);
                unsigned short _board6 = _interfaz->AddBoard(0,0,0, 1.0f, 0, "assets/images/menosD.png", 0.01f);
                _interfaz->Trasladar(_board6,(float)x,(float)y+4,(float)z);
                _interfaz->Escalar(_board6,1.75f,1.25f,1.75f);
                _interfaz->DeshabilitarObjeto(_board6);

                BoardsArmas_Scena.push_back(_board1);
                BoardsArmas_Scena.push_back(_board2);
                BoardsArmas_Scena.push_back(_board3);
                BoardsArmas_Scena.push_back(_board4);
                BoardsArmas_Scena.push_back(_board5);
                BoardsArmas_Scena.push_back(_board6);

                RecoArmas_Scena.push_back(_objetoEnEscena);
                RecoArmasAni_Scena.push_back(logicaAnim);
                return RecoArmas_Scena.size() - 1;
            }
            else
            {
                Objetos_Scena.push_back(_objetoEnEscena);
                ObjetosAni_Scena.push_back(logicaAnim);
                return Objetos_Scena.size() - 1;
            }
        }

    #else
        //codigo motor irrlicht
        IAnimatedMesh* objeto = _smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
        if (objeto)
        {
            IAnimatedMeshSceneNode* _objetoEnEscena = _smgr->addAnimatedMeshSceneNode(objeto); //metemos el objeto en el escenario para eso lo pasamos al escenario
            _objetoEnEscena->setPosition(core::vector3df(x,y,z));
            _objetoEnEscena->setRotation(core::vector3df(0,rp,0));
            //if(accion != 3)_objetoEnEscena->setMaterialTexture(0, _driver->getTexture(ruta_textura));

            if(accion == 8)
            {
                Llaves_Scena.push_back(_objetoEnEscena);
                return Llaves_Scena.size() - 1;
            }

            if(accion == 5)
            {
                Paredes_Scena.push_back(_objetoEnEscena);
                return Paredes_Scena.size() - 1;
            }

            if(accion == 4)
            {
                PowerUP_Scena.push_back(move(_objetoEnEscena));
                return PowerUP_Scena.size() - 1;
            }

            // RecoArmas_Scena solo tiene armas
            if(accion == 2)
            {
                RecoArmas_Scena.push_back(move(_objetoEnEscena));
                return RecoArmas_Scena.size() - 1;
            }
            else
            {
                Objetos_Scena.push_back(move(_objetoEnEscena));
                return Objetos_Scena.size() - 1;
            }
        }

    #endif

    return -1;
}

void MotorGrafico::CargarCofre(int pos, int rp, int x,int y,int z,
    const char* ruta_objeto, const char* ruta_textura, const char* anima, int frame, bool afectaluz)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        unsigned short _objetoEnEscena = _interfaz->AddMalla(ruta_objeto,frame,0);

        if(_objetoEnEscena != 0)
        {
            _interfaz->SetTexture(_objetoEnEscena,ruta_textura);
            _interfaz->Trasladar(_objetoEnEscena,(float)x,(float)y,(float)z);
            _interfaz->Rotar(_objetoEnEscena,0.0f,(float)rp,0.0f);

            Animaciones* logicaAnim = nullptr;

            if(anima != nullptr)
            {
                logicaAnim = new Animaciones(anima);
                logicaAnim->AsignarID(_objetoEnEscena);
            }

            // Cofre existente
            if (pos >= 0)
            {
                Cofres_Scena.at(pos) = move(_objetoEnEscena);
                CofresAni_Scena.at(pos) = move(logicaAnim);
                _interfaz->HabilitarObjeto(Cofres_Scena[pos]);
            }
            else // Cofre nuevo
            {
                Cofres_Scena.push_back(move(_objetoEnEscena));
                CofresAni_Scena.push_back(move(logicaAnim));
            }
        }
    #else
        //codigo motor irrlicht
        IAnimatedMesh* objeto = _smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
        if (objeto)
        {
            IAnimatedMeshSceneNode* _objetoEnEscena = _smgr->addAnimatedMeshSceneNode(objeto); //metemos el objeto en el escenario para eso lo pasamos al escenario
            _objetoEnEscena->setPosition(core::vector3df(x,y,z));
            _objetoEnEscena->setRotation(core::vector3df(0,rp,0));

            // Cofre existente
            if (pos >= 0)
            {
                Cofres_Scena.at(pos) = move(_objetoEnEscena);
            }
            else // Cofre nuevo
            {
                Cofres_Scena.push_back(move(_objetoEnEscena));
            }
        }
    #endif
}

void MotorGrafico::CargarArmaJugador(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura)
{
    #ifdef WEMOTOR

        //codigo motor catopengl
        unsigned short _arma = _interfaz->AddMalla(ruta_objeto,1,0);
        _interfaz->SetTexture(_arma,ruta_textura);

        if(_arma != 0)
        {
            _armaEnEscena = _arma;
            _interfaz->Trasladar(_armaEnEscena,(float)x,(float)y,(float)z);
        }

    #else
        //codigo motor irrlicht
        IAnimatedMesh* _arma = _smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
        if (_arma)
        {
            _armaEnEscena = _smgr->addAnimatedMeshSceneNode(_arma); //metemos el objeto en el escenario para eso lo pasamos al escenario
            _armaEnEscena->setPosition(core::vector3df(x,y,z));
        }
        _arma = nullptr;
    #endif

}

void MotorGrafico::CargarProyectil(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura)
{
    #ifdef WEMOTOR

        //codigo motor catopengl
        unsigned short _arma = _interfaz->AddMalla(ruta_objeto,1,0);
        _interfaz->SetTexture(_arma,ruta_textura);

        if(_arma != 0)
        {
            _armaProyectil = _arma;
            _interfaz->Trasladar(_armaProyectil,(float)x,(float)y,(float)z);
        }

    #else
        //codigo motor irrlicht
        IAnimatedMesh* _arma = _smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
        if (_arma)
        {
            _armaProyectil = _smgr->addAnimatedMeshSceneNode(_arma); //metemos el objeto en el escenario para eso lo pasamos al escenario
            _armaProyectil->setPosition(core::vector3df(x,y,z));
        }
        _arma = nullptr;
    #endif

}

void MotorGrafico::CargarArmaEspecial(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura)
{
    #ifdef WEMOTOR
        //codigo motor catopengl

        _armaEsp = _interfaz->AddMalla(ruta_objeto,1,0);
        _interfaz->SetTexture(_armaEsp,ruta_textura);
        if(_armaEsp != 0)
        {
            _interfaz->DeshabilitarObjeto(_armaEsp);
        }

    #else

        //codigo motor irrlicht
        _armaEsp = _smgr->getMesh(ruta_objeto); //creamos el objeto en memoria

    #endif
}

void MotorGrafico::CargarRecolectable(int id, int x,int y,int z, const char *ruta_objeto, const char *ruta_textura)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        unsigned short recol = _interfaz->AddMalla(ruta_objeto,1,0);
        _interfaz->SetTexture(recol,ruta_textura);

        if(recol != 0)
        {
            _interfaz->Trasladar(recol,(float)x,(float)y,(float)z);
            RecoArmas_Scena.push_back(recol);
        }

    #else
        //codigo motor irrlicht
        IAnimatedMesh* recol = _smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
        if (recol)
        {
            IAnimatedMeshSceneNode* recol_en_scena = _smgr->addAnimatedMeshSceneNode(recol); //metemos el objeto en el escenario para eso lo pasamos al escenario
            recol_en_scena->setPosition(core::vector3df(x,y,z));
            RecoArmas_Scena.push_back(recol_en_scena);
        }
    #endif
}

void MotorGrafico::CargarSprite(int id, std::vector<const char *> ruta_sprite)
{
    //crear animacion
    AnimacionSprite sprites;
    sprites.id = id;
    sprites.posx = 0.0f;
    sprites.posy = 0.0f;
    sprites.posz = 0.0f;

    //crear boards
    for(unsigned int i=0; i<ruta_sprite.size(); i++)
    {
        unsigned short _newboard = _interfaz->AddBoard(0,0,0, -1.0f, 0, ruta_sprite[i], 0.01f);
        _interfaz->Trasladar(_newboard,0.0f,0.0f,0.0f);
        _interfaz->Escalar(_newboard,2.0f,2.0f,2.0f);
        _interfaz->DeshabilitarObjeto(_newboard);
        sprites.sprite_board.push_back(_newboard);
    }

    //Guardar la animacion
    Sprites_Scena.push_back(sprites);
}

void MotorGrafico::startAnimaSprite(int id, bool start, float posx, float posy, float posz)
{
    //Buscar Anima Sprite
    for(unsigned int i=0; i<Sprites_Scena.size(); i++)
    {
        //Si el sprite coincide
        if(Sprites_Scena[i].id == id)
        {
            Sprites_Scena[i].start = start;
            if(posx == 0.0f && posy == 0.0f && posz == 0.0f)
            {
                posx = center_x + 2.0f;
                posy = center_y;
                posz = center_z - 1.0f;
            }
            Sprites_Scena[i].posx = posx;
            Sprites_Scena[i].posy = posy + 4.0f;
            Sprites_Scena[i].posz = posz;
        }
    }
}

void MotorGrafico::updateAnimaSprite()
{
    for(unsigned int i=0; i < Sprites_Scena.size(); i++)
    {
        if(Sprites_Scena[i].start == true)
        {
            //si el sprite actual
            if(Sprites_Scena[i].actualsprite != 0)
            {
                _interfaz->DeshabilitarObjeto(Sprites_Scena[i].sprite_board[Sprites_Scena[i].actualsprite-1]);
            }
            _interfaz->Trasladar(Sprites_Scena[i].sprite_board[Sprites_Scena[i].actualsprite],Sprites_Scena[i].posx,Sprites_Scena[i].posy,Sprites_Scena[i].posz);
            //std::cout << Sprites_Scena[i].sprite_board[Sprites_Scena[i].actualsprite] << std::endl;
            _interfaz->HabilitarObjeto(Sprites_Scena[i].sprite_board[Sprites_Scena[i].actualsprite]);
            Sprites_Scena[i].actualsprite++;
            if(Sprites_Scena[i].actualsprite == Sprites_Scena[i].sprite_board.size())
            {
                Sprites_Scena[i].actualsprite = 0;
                _interfaz->DeshabilitarObjeto(Sprites_Scena[i].sprite_board[Sprites_Scena[i].sprite_board.size()-1]);
                Sprites_Scena[i].start = false;
            }
        }
    }
}

void MotorGrafico::llevarObjeto(float x, float y, float z, float rx, float ry, float rz)
{
    #ifdef WEMOTOR

        //codigo motor catopengl
        if(_armaEnEscena != 0)
        {
            _interfaz->Trasladar(_armaEnEscena,x,y,z);
            _interfaz->Rotar(_armaEnEscena,rx,ry,rz);
        }

    #else
        //codigo motor irrlicht
        if(_armaEnEscena)
        {
            _armaEnEscena->setPosition(core::vector3df(x,y,z));
            _armaEnEscena->setRotation(core::vector3df(rx,ry,rz));
        }
    #endif
}

void MotorGrafico::dispararProyectil(float x, float y, float z, float rx, float ry, float rz, float es)
{
    #ifdef WEMOTOR

        //codigo motor catopengl
        if(_armaProyectil != 0)
        {
            _interfaz->Trasladar(_armaProyectil,x,y+2,z);
            _interfaz->Rotar(_armaProyectil,rx,ry-180,rz);
            _interfaz->Escalar(_armaProyectil,es,es,es);
        }

    #else
        //codigo motor irrlicht
        if(_armaProyectil != 0)
        {
            _armaProyectil->setPosition(core::vector3df(x,y,z));
            _armaProyectil->setRotation(core::vector3df(rx,ry,rz));
            _armaProyectil->setScale(core::vector3df(es,es,es));
        }
    #endif
}

void MotorGrafico::girarCamara()
{
        if(camx == 0)
        {
            cams *= -1;
            camx = 30;
            camz = 0;
        }
        else
        {
            camx = 0;
            camz = 30;
        }
}


int MotorGrafico::getCamx()
{
        return camx;
}
int MotorGrafico::getCamz()
{
        return camz;
}
int MotorGrafico::getCams()
{
        return cams;
}

void MotorGrafico::mostrarJugador(float x, float y, float z, float rx, float ry, float rz, float newy, float newz)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        float * nodeCamPosition = _interfaz->GetPosicion(camara);
        float * nodeCamTarget = _interfaz->GetTarget(camara);

        if(nodeCamPosition != nullptr && nodeCamTarget != nullptr)
        {
            // Centrar la camara
            nodeCamPosition[0] = x+(camx*cams);
            nodeCamPosition[1] = y+30+newy+altura;
            nodeCamPosition[2] = z+newz+(camz*cams);
            nodeCamTarget[0] = x;
            nodeCamTarget[1] = y;
            nodeCamTarget[2] = -z;

            _interfaz->Trasladar(camara,nodeCamPosition[0],nodeCamPosition[1],nodeCamPosition[2]);
            _interfaz->ChangeTargetCamara(camara,nodeCamTarget[0],nodeCamTarget[1],nodeCamTarget[2]);

            _interfaz->Trasladar(_jugEscena,x,y,z);
            _interfaz->Rotar(_jugEscena,rx,ry-180,rx);
            // std::cout << x << " " << y << " " << z << std::endl;

            center_x = x;
            center_y = y;
            center_z = z;

            UpdateLights(x,y,z);

            delete nodeCamPosition;

            delete nodeCamTarget;
        }

        ActualizarAnimacionMotor(_aniJugEscena);//para actualizar estado de la animacion

    #else
        //codigo motor irrlicht
        // Variables de la camara
        core::vector3df nodeCamPosition = _camera->getPosition();
        core::vector3df nodeCamTarget = _camera->getTarget();

        // Centrar la camara
        nodeCamPosition.X = x+(camx*cams);
        nodeCamPosition.Y = y+30+altura;
        nodeCamPosition.Z = z+(camz*cams);
        nodeCamTarget.X = x;
        nodeCamTarget.Y = y;
        nodeCamTarget.Z = z;

        _camera->setPosition(nodeCamPosition);
        _camera->setTarget(nodeCamTarget);

        _jugEscena->setPosition(core::vector3df(x,y,z));
        _jugEscena->setRotation(core::vector3df(rx,ry-180,rz));
    #endif
}

void MotorGrafico::mostrarEnemigos(float x, float y, float z, float rx, float ry, float rz, unsigned int i)
{
    #ifdef WEMOTOR

        //codigo motor catopengl
        if(Enemigos_Scena.size() > 0 && Enemigos_Scena.size() > i && Enemigos_Scena[i] != 0)
        {
            _interfaz->Trasladar(Enemigos_Scena[i],x,y,z);
            _interfaz->Rotar(Enemigos_Scena[i],rx,ry-180,rz);
        }

        if(BoardsEnem_Scena.size() > 0 && BoardsEnem_Scena.size() > i && BoardsEnem_Scena[i] != 0)
        {
            _interfaz->Trasladar(BoardsEnem_Scena[i],x+2.0f,y+10.0f,z);

            //Habilitar si esta cerca del pesonaje
            float distx = center_x - x;
            float disty = center_y - y;
            float distz = center_z - z;
            if(distx > -40.0f && distx < 40.0f && disty > -40.0f && disty < 40.0f && distz > -40.0f && distz < 40.0f)
            {
                _interfaz->HabilitarObjeto(BoardsEnem_Scena[i]);
            }else{
                _interfaz->DeshabilitarObjeto(BoardsEnem_Scena[i]);
            }

            //Actualizar board dependiendo de la vida

        }

    #else
        //codigo motor irrlicht
        if(Enemigos_Scena.size()>0 && Enemigos_Scena.size()>i && Enemigos_Scena[i] != nullptr)
        {
            Enemigos_Scena.at(i)->setPosition(core::vector3df(x,y,z));
            Enemigos_Scena.at(i)->setRotation(core::vector3df(rx,ry,rz));
        }
    #endif
}

void MotorGrafico::mostrarObjetos(float x, float y, float z, float rx, float ry, float rz, unsigned int i)
{
    #ifdef WEMOTOR
        //codigo motor catopengl

        if(Objetos_Scena.size() > 0 && Objetos_Scena.size() > i && Objetos_Scena[i] != 0)
        {
            _interfaz->Trasladar(Objetos_Scena[i],x,y,z);
            _interfaz->Rotar(Objetos_Scena[i],rx,ry-180,rz);
        }
    #else
        //codigo motor irrlicht
        Objetos_Scena.at(i)->setPosition(core::vector3df(x,y,z));
        Objetos_Scena.at(i)->setRotation(core::vector3df(rx,ry,rz));
    #endif
}

void MotorGrafico::mostrarCofres(float x, float y, float z, float rx, float ry, float rz, unsigned int i)
{
    #ifdef WEMOTOR
        //codigo motor catopengl

        if(Cofres_Scena.size() > 0 && Cofres_Scena.size() > i && Cofres_Scena[i] != 0)
        {
            _interfaz->Trasladar(Cofres_Scena[i],x,y,z);
            _interfaz->Rotar(Cofres_Scena[i],rx,ry-180,rz);
        }
    #else
        //codigo motor irrlicht
        Cofres_Scena.at(i)->setPosition(core::vector3df(x,y,z));
        Cofres_Scena.at(i)->setRotation(core::vector3df(rx,ry,rz));
    #endif
}

void MotorGrafico::mostrarArmaEspecial(float x, float y, float z, float rx, float ry, float rz)
{
    #ifdef WEMOTOR
        //codigo motor catopengl

        if (_armaEsp != 0)
        {
            existearmaexp = true;
            // cout << " x: " << x + 5*(sin(constantes.DEG_TO_RAD*ry)) << " y: " << y + 5 << " z: " << z + 5*(cos(constantes.DEG_TO_RAD*ry)) << endl;
            _interfaz->HabilitarObjeto(_armaEsp);//para verlo en escena y que se procese
            _interfaz->Trasladar(_armaEsp,x + 5*(sin(constantes.DEG_TO_RAD*ry)),y+1,z + 5*(cos(constantes.DEG_TO_RAD*ry)));//trasladamos
            _interfaz->Rotar(_armaEsp,rx,ry-180,rz);//rotamo
        }


    #else
        //codigo motor irrlicht
        if (_armaEsp)
        {
            if(_armaEspJugador)
            {
                this->borrarArmaEspecial();
            }
            // cout << " x: " << x + 5*(sin(constantes.DEG_TO_RAD*ry)) << " y: " << y + 5 << " z: " << z + 5*(cos(constantes.DEG_TO_RAD*ry)) << endl;
            _armaEspJugador = _smgr->addAnimatedMeshSceneNode(_armaEsp); //metemos el objeto en el escenario para eso lo pasamos al escenario
            _armaEspJugador->setPosition(core::vector3df(x + 5*(sin(constantes.DEG_TO_RAD*ry)),y,z + 5*(cos(constantes.DEG_TO_RAD*ry))));
            _armaEspJugador->setRotation(core::vector3df(rx,ry,rz));
            _smgr->getMeshManipulator()->setVertexColors(_armaEspJugador->getMesh(),SColor(255, 125, 150, 160));
        }
    #endif
}

void MotorGrafico::animacionTextura(unsigned int objeto,float velocidad, std::string ruta_textura1, std::string ruta_textura2, std::string ruta_textura3)
{
    _interfaz->SetAnimationTexture(Objetos_Scena[objeto],ruta_textura1,ruta_textura2,ruta_textura3,velocidad);
}

void MotorGrafico::cambiarTextura(unsigned int objeto, const char *ruta_textura)
{
    _interfaz->SetTexture(objeto,ruta_textura);
}

void MotorGrafico::crearBillBoardFijos()
{
    unsigned short _newboard = _interfaz->AddBoard(0,0,0, -1.0f, 0, "assets/images/LlaveBoca.png", 0.01f);
    _interfaz->Trasladar(_newboard,-4.0f,0.0f,0.0f);
    _interfaz->Escalar(_newboard,2.25f,2.25f,2.25f);
    _interfaz->DeshabilitarObjeto(_newboard);
    BoardsPuertas.push_back(_newboard);

    unsigned short _newboard2 = _interfaz->AddBoard(0,0,0, -1.0f, 0, "assets/images/LlavePalancaBoca.png", 0.01f);
    _interfaz->Trasladar(_newboard2,0.0f,0.0f,0.0f);
    _interfaz->Escalar(_newboard2,2.25f,2.25f,2.25f);
    _interfaz->DeshabilitarObjeto(_newboard2);
    BoardsPuertas.push_back(_newboard2);

    unsigned short _newboard3 = _interfaz->AddBoard(0,0,0, -1.0f, 0, "assets/images/LlaveBossBoca.png", 0.01f);
    _interfaz->Trasladar(_newboard3,2.0f,0.0f,0.0f);
    _interfaz->Escalar(_newboard3,2.25f,2.25f,2.25f);
    _interfaz->DeshabilitarObjeto(_newboard3);
    BoardsPuertas.push_back(_newboard3);

    unsigned short _boardguard = _interfaz->AddBoard(0,0,0, -1.0f, 0, "assets/images/LlaveBossBoca2.png", 0.01f);
    _interfaz->Trasladar(_boardguard,0.0f,0.0f,0.0f);
    _interfaz->Escalar(_boardguard,1.5f,1.7f,1.5f);
    _boardguardianllave = _boardguard;
}

void MotorGrafico::mostrarBoardPuerta(short tipo)
{
    if(tipo == 0)
    {
        _interfaz->Trasladar(BoardsPuertas[0],center_x+2.0f,center_y+13.0f,center_z);
        _interfaz->HabilitarObjeto(BoardsPuertas[0]);
    }
    else if(tipo == 1)
    {
        _interfaz->Trasladar(BoardsPuertas[1],center_x+2.0f,center_y+13.0f,center_z);
        _interfaz->HabilitarObjeto(BoardsPuertas[1]);
    }
    else if(tipo == 2)
    {
        _interfaz->Trasladar(BoardsPuertas[2],center_x+2.0f,center_y+13.0f,center_z);
        _interfaz->HabilitarObjeto(BoardsPuertas[2]);
    }
}

void MotorGrafico::mostrarBoardGuardian(float x,float y,float z)
{
    if(_boardguardianllave != 0)
        _interfaz->Trasladar(_boardguardianllave,x,y,z);
}

void MotorGrafico::borrarBoardGuardian()
{
    _interfaz->RemoveObject(_boardguardianllave);
    _boardguardianllave = 0;
}

void MotorGrafico::desactivarBoardPuertas()
{
    _interfaz->DeshabilitarObjeto(BoardsPuertas[0]);
    _interfaz->DeshabilitarObjeto(BoardsPuertas[1]);
    _interfaz->DeshabilitarObjeto(BoardsPuertas[2]);
}

void MotorGrafico::mostrarBoardArma(int danyoequipada, int danyosuelo, int tipoequipada, int tiposuelo, unsigned int i)
{
    #ifdef WEMOTOR
        int pos = i*6;

        //DANYO
        if(danyoequipada < danyosuelo)
        {
            _interfaz->HabilitarObjeto(BoardsArmas_Scena[pos]);
            _interfaz->DeshabilitarObjeto(BoardsArmas_Scena[pos+2]);
            _interfaz->DeshabilitarObjeto(BoardsArmas_Scena[pos+4]);
        }else if(danyoequipada == danyosuelo)
        {
            _interfaz->DeshabilitarObjeto(BoardsArmas_Scena[pos]);
            _interfaz->HabilitarObjeto(BoardsArmas_Scena[pos+2]);
            _interfaz->DeshabilitarObjeto(BoardsArmas_Scena[pos+4]);
        }else if(danyoequipada > danyosuelo)
        {
            _interfaz->DeshabilitarObjeto(BoardsArmas_Scena[pos]);
            _interfaz->DeshabilitarObjeto(BoardsArmas_Scena[pos+2]);
            _interfaz->HabilitarObjeto(BoardsArmas_Scena[pos+4]);
        }

        //DISTANCIA
        if(tipoequipada == 7)tipoequipada = 2;
        if(tipoequipada == 8)tipoequipada = 0;
        if(tipoequipada == 9)tipoequipada = 1;
        if(tiposuelo == 7)tiposuelo = 2;
        if(tiposuelo == 8)tiposuelo = 0;
        if(tiposuelo == 9)tiposuelo = 1;
        if(tipoequipada < tiposuelo)
        {
            _interfaz->HabilitarObjeto(BoardsArmas_Scena[pos+1]);
            _interfaz->DeshabilitarObjeto(BoardsArmas_Scena[pos+3]);
            _interfaz->DeshabilitarObjeto(BoardsArmas_Scena[pos+5]);
        }else if(tipoequipada == tiposuelo)
        {
            _interfaz->DeshabilitarObjeto(BoardsArmas_Scena[pos+1]);
            _interfaz->HabilitarObjeto(BoardsArmas_Scena[pos+3]);
            _interfaz->DeshabilitarObjeto(BoardsArmas_Scena[pos+5]);
        }else if(tipoequipada > tiposuelo)
        {
            _interfaz->DeshabilitarObjeto(BoardsArmas_Scena[pos+1]);
            _interfaz->DeshabilitarObjeto(BoardsArmas_Scena[pos+3]);
            _interfaz->HabilitarObjeto(BoardsArmas_Scena[pos+5]);
        }
    #endif
}

void MotorGrafico::UpdateLights(float x,float y,float z)
{
    if(Salas_luz.size()>0)
    {
        for(unsigned int i=0; i<Salas_luz.size(); i++)
        {
            //es la SAla actual
            if(_salaActual != Salas_luz[i].sala)
            {
                //En rango de otra sala
                if(z > Salas_luz[i].minz && z < Salas_luz[i].maxz && x > Salas_luz[i].minx && x < Salas_luz[i].maxx)
                {
                    if(Luces_Scena.size()>0)
                    {
                        //Habilitar y trasladar luces necesarios
                        for(unsigned int j=0; j<Luces_Scena.size(); j++)
                        {
                            if(j < Salas_luz[i].luz.size())
                            {
                                _interfaz->HabilitarObjeto(Luces_Scena[j]);
                                _interfaz->Trasladar(Luces_Scena[j],Salas_luz[i].luz[j].x,Salas_luz[i].luz[j].y,Salas_luz[i].luz[j].z);
                                //Particulas
                                if(Particulas_Scena.size()>0)
                                {
                                    if(j < Particulas_Scena.size())
                                    {
                                        _interfaz->HabilitarObjeto(Particulas_Scena[j]);
                                        _interfaz->Trasladar(Particulas_Scena[j],Salas_luz[i].luz[j].x,Salas_luz[i].luz[j].y,Salas_luz[i].luz[j].z);
                                    }
                                }
                            }
                            else
                            {
                                _interfaz->DeshabilitarObjeto(Luces_Scena[j]);
                                if(Particulas_Scena.size()>0)
                                {
                                    if(j < Particulas_Scena.size())_interfaz->DeshabilitarObjeto(Particulas_Scena[j]);
                                }
                            }
                        }
                        _salaActual = Salas_luz[i].sala;
                    }
                }
            }
        }
    }
}

void MotorGrafico::UpdateBoards(std::vector<unsigned short> boardvect, float x, float y, float z, float d)
{
    //Comprueba que el billboard esta dentro del rango del personaje
    if(boardvect.size()>0)
    {
        for(unsigned int i=0; i<boardvect.size(); i++)
        {
            float distx = center_x - x;
            float disty = center_y - y;
            float distz = center_z - z;
            if(distx > -d && distx < d && disty > -d && disty < d && distz > -d && distz < d)
            {
                _interfaz->HabilitarObjeto(boardvect[i]);
            }else{
                _interfaz->DeshabilitarObjeto(boardvect[i]);
            }
        }
    }
}

void MotorGrafico::UpdateBoardsVidaEne(int enem, int vida, int vidamax)
{
    if(BoardsEnem_Scena.size()>0)
    {
        if(BoardsEnem_Scena[enem])
        {
            float v = ((float)vida * 2.0f)/vidamax;
            _interfaz->Escalar(BoardsEnem_Scena[enem],v,0.15f,1.75f);
        }
    }
}

void MotorGrafico::borrarArmaEspecial()
{
    #ifdef WEMOTOR

        //codigo motor catopengl
        _interfaz->DeshabilitarObjeto(_armaEsp);
        existearmaexp = false;
        // _interfaz->RemoveObject(_armaEsp);//borramos el elemento que se le pasa
        //_armaEsp = 0;//lo ponemos a cero para decirle que es nulo

    #else
        //codigo motor irrlicht
        _armaEspJugador->remove();
        _armaEspJugador = nullptr;
    #endif
}

void MotorGrafico::mallaTransparente(unsigned int id, float t)
{
    #ifdef WEMOTOR
        _interfaz->SetTransparencia(id,t);
    #endif
}

void MotorGrafico::activarDebugGrafico()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(debugGrafico)
        {
            debugGrafico = false;
            if(Objetos_Debug.size()>0)
            {
                for(std::size_t i=0;i<Objetos_Debug.size();i++)
                {
                    _interfaz->RemoveObject(Objetos_Debug[i]);
                    Objetos_Debug[i] = 0;
                }
                Objetos_Debug.resize(0);
            }
        }
        else
        {
            debugGrafico = true;
        }
    #else
        //codigo motor irrlicht
        if(debugGrafico)
        {
            debugGrafico = false;
            if(Objetos_Debug.size()>0)
            {
                for(std::size_t i=0;i<Objetos_Debug.size();i++)
                {
                    Objetos_Debug[i]->remove();
                    Objetos_Debug[i] = NULL;
                    delete Objetos_Debug[i];
                }
                Objetos_Debug.resize(0);
            }
        }
        else
        {
            debugGrafico = true;
        }
    #endif

}

void MotorGrafico::activarPathfinding()
{
        if(pathfinding)
        {
            pathfinding = false;
            //cout << "\e[38m Pathfinding Desactivado \e[0m" << endl;
        }
        else
        {
            pathfinding = true;
            //cout << "\e[38m Pathfinding Activado \e[0m" << endl;
        }
}

void MotorGrafico::clearDebug()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(Objetos_Debug.size()>0)
        {
            //std::cout << Objetos_Debug.size() << std::endl;
            for(std::size_t i=0;i<Objetos_Debug.size();i++)
            {
                _interfaz->RemoveObject(Objetos_Debug[i]);
                //std::cout << "borrado" << Objetos_Debug[i] << std::endl;
                Objetos_Debug[i] = 0;
            }
            Objetos_Debug.resize(0);
        }
    #else
        //codigo motor irrlicht
        if(Objetos_Debug.size()>0)
        {
            for(std::size_t i=0;i<Objetos_Debug.size();i++)
            {
                Objetos_Debug[i]->remove();
                Objetos_Debug[i] = NULL;
                delete Objetos_Debug[i];
            }
            Objetos_Debug.resize(0);
        }
    #endif
}

void MotorGrafico::clearDebug2()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(Objetos_Debug2.size()>0)
        {
            for(std::size_t i=0;i<Objetos_Debug2.size();i++)
            {
                _interfaz->RemoveObject(Objetos_Debug2[i]);
                Objetos_Debug2[i] = 0;
            }
            Objetos_Debug2.resize(0);
        }
    #else
        //codigo motor irrlicht
        if(Objetos_Debug2.size()>0)
        {
            for(std::size_t i=0;i<Objetos_Debug2.size();i++)
            {
                Objetos_Debug2[i]->remove();
                Objetos_Debug2[i] = NULL;
                delete Objetos_Debug2[i];
            }
            Objetos_Debug2.resize(0);
        }
    #endif
}

void MotorGrafico::dibujarCirculoEventoSonido(int x, int y, int z, float intensidad)
{
    #ifdef WEMOTOR

        //codigo motor catopengl
        if(debugGrafico)
        {
            unsigned short circulo = _interfaz->AddMalla("assets/models/circuloDebugSonido.obj",1,0);
            if(circulo != 0)
            {
                //vamos a cargar el circulo en su posicion con su intensidad
                _interfaz->Trasladar(circulo,(float)x,(float)y,(float)z);
                _interfaz->Escalar(circulo,intensidad,1,intensidad);
                Objetos_Debug.push_back(circulo);
            }
        }

    #else
        //codigo motor irrlicht
        if(debugGrafico)
        {
            IAnimatedMesh* circulo = _smgr->getMesh("assets/models/circuloDebugSonido.obj");
            if(!circulo)
            {
                //no se ha podido cargar
            }
            else
            {
                //vamos a cargar el circulo en su posicion con su intensidad
                //cout << "\e[36m Generamos Circulo \e[0m" << endl;
                IAnimatedMeshSceneNode* _objetoEnEscena = _smgr->addAnimatedMeshSceneNode(circulo); //metemos el objeto en el escenario para eso lo pasamos al escenario
                SColor COLOR  = SColor(127, 255, 0, 0);
                _smgr->getMeshManipulator()->setVertexColors(_objetoEnEscena->getMesh(),COLOR);
                _objetoEnEscena->setPosition(core::vector3df(x,y,z));
                _objetoEnEscena->setScale(core::vector3df(intensidad,1,intensidad));
                Objetos_Debug.push_back(move(_objetoEnEscena));
            }
        }
    #endif
}

void MotorGrafico::dibujarZona(int x, int y, int z, float ancho, float alto, float profund)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(debugGrafico)
        {
            unsigned short tmpObjEscena = _interfaz->AddMalla("assets/models/zona.obj",1,0);
            if(tmpObjEscena != 0)
            {
                _interfaz->Trasladar(tmpObjEscena,(float)x,(float)y,(float)z);
                _interfaz->Escalar(tmpObjEscena,ancho,1.0f,profund);
                Objetos_Debug.push_back(tmpObjEscena);
            }
        }
    #else
        //codigo motor irrlicht
        if(debugGrafico)
        {
            IAnimatedMesh* tmpobjt = _smgr->getMesh("assets/models/zona.obj");
            _tmpObjEscena = _smgr->addAnimatedMeshSceneNode(tmpobjt);
            _tmpObjEscena->setPosition(core::vector3df(x,y,z));
            _tmpObjEscena->setScale(core::vector3df(ancho,1.0f,profund));
            SColor COLOR  = SColor(255,255,255,0);
            _smgr->getMeshManipulator()->setVertexColors(_tmpObjEscena->getMesh(),COLOR);
            Objetos_Debug.push_back(_tmpObjEscena);
            _tmpObjEscena = nullptr;
        }
    #endif
}

void MotorGrafico::dibujarObjetoTemporal(int x, int y, int z, int rx, int ry, int rz ,int ancho, int alto, int profund, int tipo)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(debugGrafico)
        {
            //Crear objetos debug
            unsigned short tmpobjt = 0;
            if(tipo == 1)
            {
                tmpobjt = _interfaz->AddMalla("assets/models/sphere.obj",1,0);
            }
            else if(tipo == 2)
            {
                tmpobjt = _interfaz->AddMalla("assets/models/cube.obj",1,0);
            }
            else if(tipo == 3)
            {
                tmpobjt = _interfaz->AddMalla("assets/models/capsule.otmpobjtj",1,0);
            }

            if(tmpobjt != 0)
            {
                _interfaz->Trasladar(tmpobjt,(float)x,(float)y,(float)z);
                _interfaz->Rotar(tmpobjt,(float)rx,(float)ry,(float)rz);
                _interfaz->Escalar(tmpobjt,(float)ancho,(float)alto,(float)profund);
                Objetos_Debug2.push_back(tmpobjt);
            }
        }
    #else
        //codigo motor irrlicht
        if(debugGrafico)
        {
            //Crear objetos debug
            IAnimatedMesh* tmpobjt;
            if(tipo == 1)
            {
                tmpobjt = _smgr->getMesh("assets/models/sphere.obj");
            }
            else if(tipo == 2)
            {
                tmpobjt = _smgr->getMesh("assets/models/cube.obj");
            }
            else if(tipo == 3)
            {
                tmpobjt = _smgr->getMesh("assets/models/capsule.obj");
            }
            _tmpObjEscena = _smgr->addAnimatedMeshSceneNode(tmpobjt);
            _tmpObjEscena->setPosition(core::vector3df(x,y,z));
            _tmpObjEscena->setRotation(core::vector3df(rx,ry,rz));
            _tmpObjEscena->setScale(core::vector3df(ancho,alto,profund));
            SColor COLOR  = SColor(255,255,0,255);
            _smgr->getMeshManipulator()->setVertexColors(_tmpObjEscena->getMesh(),COLOR);
            Objetos_Debug2.push_back(_tmpObjEscena);
            _tmpObjEscena = nullptr;
        }
    #endif
}

bool MotorGrafico::colisionRayo(int x,int y, int z, int rx, int ry, int rz ,int dimension)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        return true;
    #else
        //codigo motor irrlicht
        return true;
    #endif
}

/*void MotorGrafico::dibujarRayo(int x,int y, int z, int rx, int ry, int rz ,int dimension)
{
    if(debugGrafico)
    {
        if(!_linea)
        {
            _linea = _smgr->getMesh("assets/models/linea.obj");
        }
        else
        {
            // TO DO:objeto_en_scena -> _objetoEnEscena
            IAnimatedMeshSceneNode* _objetoEnEscena = _smgr->addAnimatedMeshSceneNode(_linea);
            _objetoEnEscena->setPosition(core::vector3df(x,y,z));
            _objetoEnEscena->setRotation(core::vector3df(rx,ry,rz));
            _objetoEnEscena->setScale(core::vector3df(dimension,0.2,0.5));
            Objetos_Debug.push_back(_objetoEnEscena);
        }
    }
}*/

void MotorGrafico::colorearJugador(int a, int r, int g, int b)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        //colorear jugador no existe adios
    #else
        //codigo motor irrlicht
        SColor COLOR  = SColor(a, r, g, b);
        _smgr->getMeshManipulator()->setVertexColors(_jugEscena->getMesh(),COLOR);
    #endif
}

void MotorGrafico::colorearEnemigo(int a, int r, int g, int b, int enem)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        //colorear jugador no existe adios
    #else
        //codigo motor irrlicht
        SColor COLOR  = SColor(a, r, g, b);
        long unsigned int valor = enem;
        if(Enemigos_Scena.size() > 0 && valor < Enemigos_Scena.size())//para no salirnos si no existe en motorgrafico
        {
            _smgr->getMeshManipulator()->setVertexColors(Enemigos_Scena[enem]->getMesh(),COLOR);
        }
    #endif
}

void MotorGrafico::SombrasDelNivel(unsigned int tipo)
{
    _interfaz->TipoDeSombras(tipo);
}

/*void MotorGrafico::colorearObjeto(int a, int r, int g, int b, int obj)
{
  SColor COLOR  = SColor(a, r, g, b);
  long unsigned int valor = obj;
  if(Objetos_Scena.size() > 0 && valor < Objetos_Scena.size())//para no salirnos si no existe en motorgrafico
  _smgr->getMeshManipulator()->setVertexColors(Objetos_Scena[obj]->getMesh(),COLOR);
}*/

#ifdef WEMOTOR
    //codigo motor catopengl
    bool MotorGrafico::getArmaEspecial()
    {
        if(existearmaexp)
        {
            if(_armaEsp != 0)
            {
                return true;
            }
        }

        return false;
    }
#else
    //codigo motor irrlicht
    IAnimatedMeshSceneNode* MotorGrafico::getArmaEspecial()
    {
        return _armaEspJugador;
    }
#endif

void MotorGrafico::EraseRecoArma(long unsigned int idx)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(RecoArmas_Scena[idx] && idx < RecoArmas_Scena.size())
        {
            int boardpos = idx*6;
            _interfaz->RemoveObject(BoardsArmas_Scena[boardpos]);
            BoardsArmas_Scena.erase(BoardsArmas_Scena.begin() + boardpos);
            _interfaz->RemoveObject(BoardsArmas_Scena[boardpos]);
            BoardsArmas_Scena.erase(BoardsArmas_Scena.begin() + boardpos);
            _interfaz->RemoveObject(BoardsArmas_Scena[boardpos]);
            BoardsArmas_Scena.erase(BoardsArmas_Scena.begin() + boardpos);
            _interfaz->RemoveObject(BoardsArmas_Scena[boardpos]);
            BoardsArmas_Scena.erase(BoardsArmas_Scena.begin() + boardpos);
            _interfaz->RemoveObject(BoardsArmas_Scena[boardpos]);
            BoardsArmas_Scena.erase(BoardsArmas_Scena.begin() + boardpos);
            _interfaz->RemoveObject(BoardsArmas_Scena[boardpos]);
            BoardsArmas_Scena.erase(BoardsArmas_Scena.begin() + boardpos);

            _interfaz->RemoveObject(RecoArmas_Scena[idx]);
            RecoArmas_Scena.erase(RecoArmas_Scena.begin() + idx);
            RecoArmasAni_Scena.erase(RecoArmasAni_Scena.begin() + idx);
        }
    #else
        //codigo motor irrlicht
        if(RecoArmas_Scena[idx] && idx < RecoArmas_Scena.size())
        {
            RecoArmas_Scena[idx]->setVisible(false);
            RecoArmas_Scena[idx]->remove();
            RecoArmas_Scena.erase(RecoArmas_Scena.begin() + idx);
        }
    #endif
}

void MotorGrafico::EraseLlave(long unsigned int idx)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(Llaves_Scena[idx] && idx < Llaves_Scena.size())
        {
            _interfaz->RemoveObject(Llaves_Scena[idx]);
            _interfaz->RemoveObject(Particulas_Llave[idx]);
            Llaves_Scena.erase(Llaves_Scena.begin() + idx);
            LlavesAni_Scena.erase(LlavesAni_Scena.begin() + idx);
            Particulas_Llave.erase(Particulas_Llave.begin() + idx);
        }
    #else
        //codigo motor irrlicht
        if(Llaves_Scena[idx] && idx < Llaves_Scena.size())
        {
            Llaves_Scena[idx]->setVisible(false);
            Llaves_Scena[idx]->remove();
            Llaves_Scena.erase(Llaves_Scena.begin() + idx);
        }
    #endif
}

void MotorGrafico::ErasePared(long unsigned int idx)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(Paredes_Scena[idx] && idx < Paredes_Scena.size())
        {
            // TO DO: No utilizo esto de la interfaz porque da problemas
            //_interfaz->RemoveObject(Paredes_Scena[idx]);
            Paredes_Scena.erase(Paredes_Scena.begin() + idx);
            ParedesAni_Scena.erase(ParedesAni_Scena.begin() + idx);
        }
    #else
        //codigo motor irrlicht
        if(Paredes_Scena[idx] && idx < Paredes_Scena.size())
        {
            Paredes_Scena[idx]->setVisible(false);
            Paredes_Scena[idx]->remove();
            Paredes_Scena.erase(Paredes_Scena.begin() + idx);
        }
    #endif
}

void MotorGrafico::ErasePowerUP(long unsigned int idx)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(PowerUP_Scena[idx] && idx < PowerUP_Scena.size())
        {
            _interfaz->RemoveObject(PowerUP_Scena[idx]);
            PowerUP_Scena.erase(PowerUP_Scena.begin() + idx);
        }
    #else
        //codigo motor irrlicht
        if(PowerUP_Scena[idx] && idx < PowerUP_Scena.size())
        {
            PowerUP_Scena[idx]->setVisible(false);
            PowerUP_Scena[idx]->remove();
            PowerUP_Scena.erase(PowerUP_Scena.begin() + idx);
        }
    #endif
}

// Para cuando el jugador rompe la pared
/*void MotorGrafico::DibujarPared(long unsigned int idx, bool dibujar)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(Objetos_Scena[idx] != 0 && idx < Objetos_Scena.size())
        {
            if(dibujar)
            {
                _interfaz->HabilitarObjeto(Objetos_Scena[idx]);
            }
            else
            {
                _interfaz->DeshabilitarObjeto(Objetos_Scena[idx]);
            }
        }
    #else
        //codigo motor irrlicht
        if(Objetos_Scena[idx] && idx < Objetos_Scena.size())
        {
            Objetos_Scena[idx]->setVisible(dibujar);
        }
    #endif
}*/

void MotorGrafico::EraseCofre(unsigned short idx)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        _interfaz->DeshabilitarObjeto(Cofres_Scena[idx]);
        if(idx < CofresAni_Scena.size())
        {
                if(CofresAni_Scena[idx])
                {
                    delete CofresAni_Scena[idx];
                }
                CofresAni_Scena.erase(CofresAni_Scena.begin() + idx);
        }
    #else
        //codigo motor irrlicht
        Cofres_Scena[idx]->setVisible(false);
    #endif
}

//Cuando enemigo muere lo borramos
void MotorGrafico::EraseEnemigo(std::size_t i)
{
    #ifdef WEMOTOR
        //codigo motor catopengl

        long unsigned int valor = i;

        if(valor >= 0 && valor < Enemigos_Scena.size())
        {
            _interfaz->RemoveObject(Enemigos_Scena[i]);
            Enemigos_Scena.erase(Enemigos_Scena.begin() + i);
            if(valor < EnemigosAni_Scena.size())
            {
                if(EnemigosAni_Scena[i])
                {
                     delete EnemigosAni_Scena[i];
                }
                EnemigosAni_Scena.erase(EnemigosAni_Scena.begin() + i);
            }
        }



        if(valor >= 0 && valor < BoardsEnem_Scena.size())
        {
            _interfaz->RemoveObject(BoardsEnem_Scena[i]);
            BoardsEnem_Scena.erase(BoardsEnem_Scena.begin() + i);
        }
    #else
        //codigo motor irrlicht
        long unsigned int valor = i;
        if(valor >= 0 && valor < Enemigos_Scena.size())
        {
            Enemigos_Scena[i]->setVisible(false);
            Enemigos_Scena[i]->remove();
            Enemigos_Scena.erase(Enemigos_Scena.begin() + i);
        }
    #endif
}

//Cuando se activa el boss se vacia el vector de enemigos del motor grafico
void MotorGrafico::EraseTodosEnemigos()
{
    Constantes constantes;
    unsigned int valor = 0;
    #ifdef WEMOTOR
        //codigo motor catopengl

        if(valor >= 0 && valor < Enemigos_Scena.size())
        {
            _interfaz->RemoveObject(Enemigos_Scena[valor]);
            Enemigos_Scena.erase(Enemigos_Scena.begin());
        }

        if(valor >= 0 && valor < BoardsEnem_Scena.size())
        {
            _interfaz->RemoveObject(BoardsEnem_Scena[valor]);
            BoardsEnem_Scena.erase(BoardsEnem_Scena.begin());
        }

    #else
        //codigo motor irrlicht
        if(valor >= 0 && valor < Enemigos_Scena.size())
        {
            Enemigos_Scena[valor]->setVisible(false);
            Enemigos_Scena[valor]->remove();
            Enemigos_Scena.erase(Enemigos_Scena.begin() + i);
        }
    #endif
}

//Cuando jugador muere lo borramos
void MotorGrafico::EraseJugador()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        _interfaz->RemoveObject(_jugEscena);
    #else
        //codigo motor irrlicht
        _jugEscena->setVisible(false);
        _jugEscena->remove();
    #endif
}

void MotorGrafico::EraseArma()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        _interfaz->RemoveObject(_armaEnEscena);
    #else
        //codigo motor irrlicht
        _armaEnEscena->setVisible(false);
        _armaEnEscena->remove();
    #endif
}

void MotorGrafico::EraseProyectil()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        _interfaz->RemoveObject(_armaProyectil);
    #else
        //codigo motor irrlicht
        _armaProyectil->setVisible(false);
        _armaProyectil->remove();
    #endif
}

//Devolver cantidad de enemigos en escena para recorrerlos en metodo muerteEnemigo
/*int MotorGrafico::getEnemigos_Scena(){
    return Enemigos_Scena.size();
}*/

//Devolver cantidad de objetos en escena para recorrerlos en metodo muerteEnemigo
/*int MotorGrafico::getObjetos_Scena(){
    return Objetos_Scena.size();
}*/

//esta funcion es para ver la caja del bounding box creada en motor fisicas
//abra que pasarle el numero de caja
void MotorGrafico::debugBox(int x,int y, int z,int ancho, int alto, int largo)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        //SI es necesario se implementara
    #else
        //codigo motor irrlicht
        if(debugGrafico)
        {
            //cout << x << y << z << ancho << largo << alto << endl;
            if(_caja)
            {
                _caja->setMaterialFlag(video::EMF_LIGHTING, false);
                //_caja->setPosition(core::vector3df(x,y,z));
                //_caja->setScale(core::vector3df(ancho/5,alto/5,largo/5));
                _caja->setPosition(core::vector3df(0,0,20));
                _caja->setScale(core::vector3df(4,1,0.2));
            }
            else
            {
                _caja = _smgr->addCubeSceneNode();
            }
        }
    #endif
}

void MotorGrafico::debugVision(float x, float y, float z, float rotacion, float longitud)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(debugGrafico)
        {
            unsigned short _conoVision = _interfaz->AddMalla("assets/models/conoVision.obj",1,0);
            if(_conoVision != 0)
            {
                _interfaz->Trasladar(_conoVision,x,y,z);
                _interfaz->Rotar(_conoVision,0,rotacion-180,0);
                _interfaz->Escalar(_conoVision,longitud/2,1.0f,0.01f);
                Objetos_Debug.push_back(_conoVision);
            }
        }
    #else
        //codigo motor irrlicht
        if(debugGrafico)
        {
            if(!_conoVision)
            {
                _conoVision = _smgr->getMesh("assets/models/conoVision.obj");
            }

            if(_conoVision) // Si se ha cargado
            {
                IAnimatedMeshSceneNode* _objetoEnEscena = _smgr->addAnimatedMeshSceneNode(_conoVision); //metemos el objeto en el escenario para eso lo pasamos al escenario
                _objetoEnEscena->setPosition(core::vector3df(x/*-(2*(sin(constantes.PI * rotacion / constantes.PI_RADIAN)))*/,y+2,z/*-(2*(cos(constantes.PI * rotacion / constantes.PI_RADIAN)))*/));
                SColor COLOR  = SColor(0, 255, 0, 0);
                _smgr->getMeshManipulator()->setVertexColors(_objetoEnEscena->getMesh(),COLOR);

                core::vector3df rotation = _objetoEnEscena->getRotation();
                _objetoEnEscena->setRotation(core::vector3df(rotation.X,rotacion,rotation.Z));

                rotation = _objetoEnEscena->getRotation();

                _objetoEnEscena->setScale(core::vector3df(longitud/2,1.0f,0.01f));
                Objetos_Debug.push_back(_objetoEnEscena);
            }
        }
    #endif
}

void MotorGrafico::CargarInterfaz()
{
    #ifdef WEMOTOR
        //codigo motor catopengl

        //cargamos y mostramos la interfaz
        vida_textura = _interfaz->AddImagen("assets/images/51.png",10,10,1);
        energia_textura = _interfaz->AddImagen("assets/images/21.png",10,58,1);
        dinero_textura = _interfaz->AddImagen("assets/images/61.png",680,10,1);
        arma_textura =_interfaz->AddImagen("assets/images/11.png",730,530,1);
        barraVida_textura = _interfaz->AddImagen("assets/images/4.png",50,18,1);
        barraEnergia_textura = _interfaz->AddImagen("assets/images/3.png",48,67,1);
        manos_textura = _interfaz->AddImagen("assets/images/manos.png",738,534,1);
        llave_textura = _interfaz->AddImagen("assets/images/llave.png",738,534,1);
        espada_textura = _interfaz->AddImagen("assets/images/espada.png",738,534,1);
        daga_textura = _interfaz->AddImagen("assets/images/daga.png",738,534,1);

        //calcular vida y energia

        //monedas y color de letra
        moneyI = _interfaz->CrearTexto("0 M",710,25,255.0f,255.0f,255.0f);

    #else
        //codigo motor irrlicht
        //creamos texturas
        vida_textura = _driver->getTexture("assets/images/51.png");
        energia_textura = _driver->getTexture("assets/images/21.png");
        dinero_textura = _driver->getTexture("assets/images/61.png");
        arma_textura = _driver->getTexture("assets/images/11.png");
        barraVida_textura = _driver->getTexture("assets/images/4.png");
        barraEnergia_textura = _driver->getTexture("assets/images/3.png");
        manos_textura = _driver->getTexture("assets/images/manos.png");
        llave_textura = _driver->getTexture("assets/images/llave.png");
        espada_textura = _driver->getTexture("assets/images/espada.png");
        daga_textura = _driver->getTexture("assets/images/daga.png");
        //aplicamos texturas
        vidaI = _guienv->addImage(vida_textura,position2d<int>(10,10));
        energiaI = _guienv->addImage(energia_textura,position2d<int>(10,58));
        dineroI = _guienv->addImage(dinero_textura,position2d<int>(680,10));
        armaI = _guienv->addImage(arma_textura,position2d<int>(730,530));
        BarraVidaI = _guienv->addImage(barraVida_textura,position2d<int>(50,15));
        BarraEnergiaI = _guienv->addImage(barraEnergia_textura,position2d<int>(48,65));

        //imagenes tipo objeto que se lleva por defecto manos
        manosI = _guienv->addImage(manos_textura,position2d<int>(738,534));
        llaveI = _guienv->addImage(llave_textura,position2d<int>(738,534));
        espadaI = _guienv->addImage(espada_textura,position2d<int>(738,534));
        dagaI = _guienv->addImage(daga_textura,position2d<int>(738,534));

        BarraVidaI->setMaxSize(dimension2du(121,29));//maximo 121/100 y esto multiplicado por la cantidad de vida
        BarraEnergiaI->setMaxSize(dimension2du(63,27));//maximo 63/100 y esto multiplicado por la cantidad de energia
        font2 = _guienv->getFont("assets/fonts/myfont.xml");

        //moneyI = _guienv->addStaticText(L"1000 M",rect<s32>(710,21,750,40),false); //falta ver los cambios de fuente y ponerlo correctamente
        moneyI = _guienv->addStaticText(L"0 M",rect<s32>(710,21,750,40),false); //falta ver los cambios de fuente y ponerlo correctamente

        SColor COLOR  = SColor(255, 255, 255, 0);
        moneyI->enableOverrideColor(true);
        moneyI->setOverrideColor(COLOR);
        if(font2)
        {
            moneyI->setOverrideFont(font2);
        }
    #endif
}

void MotorGrafico::DestruirInterfaz()
{
    #ifdef WEMOTOR
        //codigo motor catopengl

        if(moneyI != 0)
        {
            _interfaz->RemoveObject(moneyI);
            moneyI = 0;
        }

        if(vida_textura != 0)
        {
            _interfaz->RemoveObject(vida_textura);
            vida_textura = 0;
        }

        if(energia_textura != 0)
        {
            _interfaz->RemoveObject(energia_textura);
            energia_textura = 0;
        }

        if(dinero_textura != 0)
        {
            _interfaz->RemoveObject(dinero_textura);
            dinero_textura = 0;
        }

        if(arma_textura != 0)
        {
            _interfaz->RemoveObject(arma_textura);
            arma_textura = 0;
        }

        if(barraVida_textura != 0)
        {
            _interfaz->RemoveObject(barraVida_textura);
            barraVida_textura = 0;
        }

        if(barraEnergia_textura != 0)
        {
            _interfaz->RemoveObject(barraEnergia_textura);
            barraEnergia_textura = 0;
        }

        if(manos_textura != 0)
        {
            _interfaz->RemoveObject(manos_textura);
            manos_textura = 0;
        }

        if(llave_textura != 0)
        {
            _interfaz->RemoveObject(llave_textura);
            llave_textura = 0;
        }

        if(espada_textura != 0)
        {
            _interfaz->RemoveObject(espada_textura);
            espada_textura = 0;
        }

        if(daga_textura != 0)
        {
            _interfaz->RemoveObject(daga_textura);
            daga_textura= 0;
        }

    #else
        //codigo motor irrlicht
        if(vidaI)
        {
            vidaI->remove();
        }

        if(energiaI)
        {
            energiaI->remove();
        }

        if(dineroI)
        {
            dineroI->remove();
        }

        if(armaI)
        {
            armaI->remove();
        }

        if(manosI)
            manosI->remove();

        if(dagaI)
            dagaI->remove();

        if(espadaI)
            espadaI->remove();

        if(llaveI)
            llaveI->remove();

        if(BarraEnergiaI)
            BarraEnergiaI->remove();

        if(BarraVidaI)
            BarraVidaI->remove();

        if(moneyI)
            moneyI->remove();

        _driver->removeTexture(vida_textura);
        _driver->removeTexture(energia_textura);
        _driver->removeTexture(dinero_textura);
        _driver->removeTexture(arma_textura);
        _driver->removeTexture(barraVida_textura);
        _driver->removeTexture(barraEnergia_textura);
        _driver->removeTexture(manos_textura);
        _driver->removeTexture(llave_textura);
        _driver->removeTexture(espada_textura);
        _driver->removeTexture(daga_textura);
    #endif
}

void MotorGrafico::SetVida(int vida)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(barraVida_textura != 0)
        {
            float unidad = ((float)121/100);
            float unidad_min = 0.0030f;

            float resultado = (unidad*(float)vida)*unidad_min;

            if(resultado <= 0)
            {
                _interfaz->EscalarImagen(barraVida_textura,0.01f,0.48f,true,true);
            }
            else
            {
                _interfaz->EscalarImagen(barraVida_textura,resultado,0.48f,true,true);
            }
        }

    #else
        //codigo motor irrlicht
        if(BarraVidaI)
        {
            float unidad = ((float)121/100);
            float resultado = unidad*(float)vida;

            if(resultado <= 0)
            {
                BarraVidaI->setMaxSize(dimension2du(1,29));//maximo 121/100 y esto multiplicado por la cantidad de vida
            }
            else
            {
                BarraVidaI->setMaxSize(dimension2du(resultado,29));//maximo 121/100 y esto multiplicado por la cantidad de vida
            }
        }
    #endif

}

void MotorGrafico::SetBarraEnergia(int barra)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(barraEnergia_textura != 0)
        {
            float unidad = ((float)63/100);
            float unidad_min = 0.0030f;

            float resultado = (unidad*(float)barra)*unidad_min;


            if(resultado <= 0)
            {
                _interfaz->EscalarImagen(barraEnergia_textura,0.01f,0.48f,true,true);
            }
            else
            {
                _interfaz->EscalarImagen(barraEnergia_textura,resultado,0.48f,true,true);
            }
        }
    #else
        //codigo motor irrlicht
        if(BarraEnergiaI)
        {
            float unidad = ((float)63/100);
            float resultado = unidad*(float)barra;
            //cout << barra << " " << unidad << " " << resultado << endl ;
            if(resultado <= 0)
            {
                BarraEnergiaI->setMaxSize(dimension2du(1,27));//maximo 121/100 y esto multiplicado por la cantidad de vida
            }
            else
            {
                BarraEnergiaI->setMaxSize(dimension2du(resultado,27));//maximo 121/100 y esto multiplicado por la cantidad de vida
            }
        }
    #endif
}

void MotorGrafico::SetDinero(int dinero)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(moneyI != 0)
        {
            string str = std::to_string(dinero);
            //std::cout << "recoges tantas: " << str << std::endl;
            _interfaz->CambiarTexto(moneyI,str);
        }
    #else
        //codigo motor irrlicht
        if(moneyI)
        {
            stringw str = L"";
            str += dinero;
            moneyI->setText(str.c_str());
        }
    #endif

}

void MotorGrafico::SetArma(int arma)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        switch(arma)
        {
            case 1: //es una llave
                _interfaz->HabilitarObjeto(llave_textura);
                _interfaz->DeshabilitarObjeto(manos_textura);
                _interfaz->DeshabilitarObjeto(daga_textura);
                _interfaz->DeshabilitarObjeto(espada_textura);
                break;

            case 2: //objeto ataque directo
                _interfaz->DeshabilitarObjeto(llave_textura);
                _interfaz->DeshabilitarObjeto(manos_textura);
                _interfaz->DeshabilitarObjeto(daga_textura);
                _interfaz->HabilitarObjeto(espada_textura);
                break;

            case 3: //objeto ataque a distancia
                _interfaz->DeshabilitarObjeto(llave_textura);
                _interfaz->DeshabilitarObjeto(manos_textura);
                _interfaz->HabilitarObjeto(daga_textura);
                _interfaz->DeshabilitarObjeto(espada_textura);
                break;

            default: //son las manos
                _interfaz->DeshabilitarObjeto(llave_textura);
                _interfaz->HabilitarObjeto(manos_textura);
                _interfaz->DeshabilitarObjeto(daga_textura);
                _interfaz->DeshabilitarObjeto(espada_textura);
                break;
        }
    #else
        //codigo motor irrlicht
        switch(arma)
        {
            case 1: //es una llave
                manosI->setVisible(false);
                dagaI->setVisible(false);
                espadaI->setVisible(false);
                llaveI->setVisible(true);
                break;

            case 2: //objeto ataque directo
                manosI->setVisible(false);
                dagaI->setVisible(false);
                espadaI->setVisible(true);
                llaveI->setVisible(false);
                break;

            case 3: //objeto ataque a distancia
                manosI->setVisible(false);
                dagaI->setVisible(true);
                espadaI->setVisible(false);
                llaveI->setVisible(false);
                break;

            default: //son las manos
                manosI->setVisible(true);
                dagaI->setVisible(false);
                espadaI->setVisible(false);
                llaveI->setVisible(false);
                break;
        }
    #endif
}

void MotorGrafico::RenderInterfaz(bool activada)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if (activada)
        {

            if(vida_textura != 0)
            {
                _interfaz->HabilitarObjeto(vida_textura);
            }

            if(energia_textura != 0)
            {
                _interfaz->HabilitarObjeto(energia_textura);
            }

            if(dinero_textura != 0)
            {
                _interfaz->HabilitarObjeto(dinero_textura);
            }

            if(arma_textura != 0)
            {
                _interfaz->HabilitarObjeto(arma_textura);
            }

            if(barraEnergia_textura != 0)
            {
                _interfaz->HabilitarObjeto(barraEnergia_textura);
            }

            if(barraVida_textura != 0)
            {
                _interfaz->HabilitarObjeto(barraVida_textura);
            }

            if(dinero_textura != 0)
            {
                _interfaz->HabilitarObjeto(dinero_textura);
            }

        }
        else
        {
            if(vida_textura != 0)
            {
                _interfaz->DeshabilitarObjeto(vida_textura);
            }

            if(energia_textura != 0)
            {
                _interfaz->DeshabilitarObjeto(energia_textura);
            }

            if(dinero_textura != 0)
            {
                _interfaz->DeshabilitarObjeto(dinero_textura);
            }

            if(arma_textura != 0)
            {
                _interfaz->DeshabilitarObjeto(arma_textura);
            }

            if(barraEnergia_textura != 0)
            {
                _interfaz->DeshabilitarObjeto(barraEnergia_textura);
            }

            if(barraVida_textura != 0)
            {
                _interfaz->DeshabilitarObjeto(barraVida_textura);
            }

            if(dinero_textura != 0)
            {
                _interfaz->DeshabilitarObjeto(dinero_textura);
            }

            if(espada_textura != 0)
            {
                _interfaz->DeshabilitarObjeto(dinero_textura);
            }

            if(llave_textura != 0)
            {
                _interfaz->DeshabilitarObjeto(dinero_textura);
            }

        }

    #else
        //codigo motor irrlicht
        if (activada)
        {
            if(vidaI)
                vidaI->setVisible(true);
            if(energiaI)
                energiaI->setVisible(true);
            if(dineroI)
                dineroI->setVisible(true);
            if(armaI)
                armaI->setVisible(true);
            if(BarraEnergiaI)
                BarraEnergiaI->setVisible(true);
            if(BarraVidaI)
                BarraVidaI->setVisible(true);
            if(moneyI)
                moneyI->setVisible(true);
        }
        else
        {
            if(vidaI)
                vidaI->setVisible(false);
            if(energiaI)
                energiaI->setVisible(false);
            if(dineroI)
                dineroI->setVisible(false);
            if(armaI)
                armaI->setVisible(false);
            if(BarraEnergiaI)
                BarraEnergiaI->setVisible(false);
            if(BarraVidaI)
                BarraVidaI->setVisible(false);
            if(manosI)
                manosI->setVisible(false);
            if(dagaI)
                dagaI->setVisible(false);
            if(espadaI)
                espadaI->setVisible(false);
            if(llaveI)
                llaveI->setVisible(false);
            if(moneyI)
                moneyI->setVisible(false);
        }
    #endif
}

void MotorGrafico::cambiarAnimacionJugador(int estado)
{
    #ifdef WEMOTOR
        //codigo motor catopengl

        int frame = _interfaz->getStartFrame(_jugEscena);
        int frame_actual = _interfaz->getFrameNr(_jugEscena);

        if(_aniJugEscena != nullptr)
        {
            if(_aniJugEscena->ExisteEstado(estado) && _aniJugEscena->SePuedeCambiarEstado(frame_actual))//comprobamos primero que sea posible
            {
                //std::cout << " se llama a cambiar estado " << estado << " " << frame << std::endl;
                _aniJugEscena->CambiarEstado(estado,frame,frame_actual);//si es posible llamamos a cambiarestado
            }
        }

    #else
        //codigo motor irrlicht
        int frame = _jugEscena->getStartFrame();
        int frame_actual = _jugEscena->getFrameNr();
        //animaciones para heavy
        if(estado == 0 && frame != 30 && frame != 120) //esta quieto
        {
            if(_jugEscena)
            {
                _jugEscena->setFrameLoop(30, 44);
                _jugEscena->setAnimationSpeed(10);
            }
        }

        if(estado == 1 && frame != 0 && frame != 120) //se mueve
        {
            if(_jugEscena)
            {
                _jugEscena->setFrameLoop(0, 30);
                _jugEscena->setAnimationSpeed(20);
            }
        }

        if(estado == 2 && frame != 48  && frame != 120) //ataca
        {
            if(_jugEscena)
            {
                _jugEscena->setFrameLoop(48, 70);
                _jugEscena->setAnimationSpeed(15);
            }
        }

        if(estado == 3 && frame != 72  && frame != 120) //ataque especial
        {
            if(_jugEscena)
            {
                _jugEscena->setFrameLoop(72, 98);
                _jugEscena->setAnimationSpeed(10);
            }
        }

        if(estado == 4  && frame != 99  && frame != 120) //coger objeto
        {
            if(_jugEscena)
            {
                _jugEscena->setFrameLoop(99, 112);
                _jugEscena->setAnimationSpeed(10);
            }
        }

        if(estado == 5 && frame != 120) //muere
        {
            if(frame_actual == 119)
            {
                _jugEscena->setFrameLoop(120, 128); //lo dejamos definitivamente muerto
                _jugEscena->setAnimationSpeed(10);
            }
            else
            {
                if(_jugEscena && frame != 112)
                {
                    _jugEscena->setFrameLoop(112, 120);
                    _jugEscena->setAnimationSpeed(10);
                }
            }
        }
    #endif

}

bool MotorGrafico::getPathfindingActivado()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        return false;
    #else
        //codigo motor irrlicht
        return pathfinding;
    #endif
}

void MotorGrafico::RenderMotorCinematica(float marcaTiempo, float tiempoUltimoFrame)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
    #else
        //codigo motor irrlicht
        float mile = 1000.0f;
        float ratio = 30.0f;
        float tiempo_frame = mile/ratio;
        int salto = ceil(tiempoUltimoFrame/tiempo_frame);
        if(frame_actual == 0)
        {
            frame_actual = 1;
        }
        else
        {
            if(tiempoUltimoFrame > tiempo_frame)
            {
                //es mayor (va lento)
                frame_actual = frame_actual+(1+salto);
            }
            else
            {
                //es menor (va mas rapido)
                frame_actual = frame_actual+1;
            }
        }
        if(frame_actual < 498)
        {
            //definimos los strings
            std::string fram = "";
            std::string extension = ".jpg";
            std::string ruta = "assets/cinematicas/frames/";
            fram = std::to_string(frame_actual);
            //creamos la ruta completa
            std::string ruta_completa = ruta+fram+extension;
            char buffer[100];
            strcpy(buffer,ruta_completa.c_str());
            if(_actual != nullptr && _actualTexture != nullptr)
            {
                _actual->remove();//remuevo imagen actual
                _driver->removeTexture(_actualTexture);//borras textura
                _actualTexture = _driver->getTexture(buffer);//creas la textura
                _actual = _guienv->addImage(_actualTexture,position2d<int>(0,0));//creo imagen actual
            }
            else
            {
                _actualTexture = _driver->getTexture(buffer);//creo textura
                _actual = _guienv->addImage(_driver->getTexture(buffer),position2d<int>(0,0));//creo imagen con textura
            }
            //cout << tiempoUltimoFrame << " " << salto << endl;
        }
    #endif
}

bool MotorGrafico::finalCinematica()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        return false;
    #else
        //codigo motor irrlicht
        if(frame_actual >= 498)
        {
            //borramos los datos
            _actual->remove();//remuevo imagen actual
            _driver->removeTexture(_actualTexture);//borras textura
            //borramos los punteros
            _actual = nullptr;
            _actualTexture = nullptr;
            return true;
        }

        return false;
    #endif

}

void MotorGrafico::BorrarElemento(signed int id)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        if(_interfaz)
        {
            //_interfaz->RemoveObject((unsigned short)id);
            _interfaz->RemoveObjectForID(id);
        }
    #else
        //codigo motor irrlicht
        _guienv->getRootGUIElement()->getElementFromId(id)->remove();
    #endif
}

void MotorGrafico::BorrarElementoPorIdReal(unsigned int id)
{
    #ifdef WEMOTOR
        if(_interfaz)
        {
            _interfaz->RemoveObject(id);
        }
    #endif
}

unsigned short MotorGrafico::GetWidth()
{
    return width;
}

unsigned short MotorGrafico::GetHeight()
{
    return height;
}


// ************************* Funciones para Puzzles *******************
void MotorGrafico::IniIDPuzzles()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        IDP = idsEventos::Enum::GUI_ID_PUZZLE;
    #else
        //codigo motor irrlicht
        IDP = GUI_ID_PUZZLE;
    #endif
}

void MotorGrafico::BorrarGuiPuzzle(unsigned short tipo, unsigned short opciones)
{
    #ifdef WEMOTOR
        //codigo motor catopengl

        BorrarElemento(idsEventos::Enum::GUI_ID_ATRAS_PUZ);

        if (tipo == 1)
        {
            unsigned short tam = _imagenesP.size();
            for(unsigned short i=0; i < tam; i++)
            {
                BorrarElemento(_imagenesP.at(i));
            }
            _imagenesP.clear();

            tam = _textosP.size();
            for(unsigned short i=0; i < tam; i++)
            {
                BorrarElemento(_textosP.at(i));
            }
            _textosP.clear();

            BorrarElemento(idsEventos::Enum::GUI_ID_OP1);
            BorrarElemento(idsEventos::Enum::GUI_ID_OP2);

            if (opciones > 2)
            {
                BorrarElemento(idsEventos::Enum::GUI_ID_OP3);
                BorrarElemento(idsEventos::Enum::GUI_ID_OP4);
            }
        }

    #else
        //codigo motor irrlicht

        BorrarElemento(GUI_ID_ATRAS_PUZ);

        if (tipo == 1)
        {
            unsigned short tam = _imagenesP.size();
            for(unsigned short i=0; i < tam; i++)
            {
                BorrarElemento(_imagenesP.at(i)->getID());
            }
            _imagenesP.clear();

            tam = _textosP.size();
            for(unsigned short i=0; i < tam; i++)
            {
                BorrarElemento(_textosP.at(i)->getID());
            }
            _textosP.clear();

            BorrarElemento(GUI_ID_OP1);
            BorrarElemento(GUI_ID_OP2);

            if (opciones > 2)
            {
                BorrarElemento(GUI_ID_OP3);
                BorrarElemento(GUI_ID_OP4);
            }
        }
    #endif
}

void MotorGrafico::CargarFondoPuzzle()
{
    // Depende de la resolucion: 640, 800, 1024, 1280
    std::string fondo = "assets/puzzles/Fondo"+
        std::to_string(width) + ".png";
    const char* cfondo = fondo.c_str();

    #ifdef WEMOTOR
        //codigo motor catopengl
        _imgP = _interfaz->AddImagen(cfondo,0,0,1.0f);
        _interfaz->DefinirIdPersonalizado(_imgP,IDP);
        _imagenesP.push_back(IDP);
        _imgP = 0;
    #else
        //codigo motor irrlicht
        ITexture* _textura = _driver->getTexture(cfondo);
        _imgP = _guienv->addImage(_textura,
            core::position2d<s32>(0, 0));
        _imgP->setID(IDP);
        _imagenesP.push_back(move(_imgP));
        _imgP = nullptr;
        _textura = nullptr;
    #endif
}

void MotorGrafico::CargarIMGPuzzle(unsigned short x, unsigned short y, std::string img)
{
    std::string ruta = "assets/puzzles/"+img;
    const char* cruta = ruta.c_str();

    #ifdef WEMOTOR
        //codigo motor catopengl
        _imgP = _interfaz->AddImagen(cruta,x,y,1.0f);
        unsigned short nue = ++IDP;
        _interfaz->DefinirIdPersonalizado(_imgP,nue);
        _imagenesP.push_back(nue);
        _imgP = 0;
    #else
        //codigo motor irrlicht
        ITexture* _textura = _driver->getTexture(cruta);
        _imgP = _guienv->addImage(_textura,
            core::position2d<s32>(x, y));
        _imgP->setID(++IDP);
        _imagenesP.push_back(move(_imgP));
        _imgP = nullptr;
        _textura = nullptr;
    #endif
}

void MotorGrafico::CrearTextoPuzzles(std::string texto, unsigned short x1,
    unsigned short y1, unsigned short x2, unsigned short y2)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        unsigned short num = _interfaz->CrearTexto(texto,x1,y1,255.0f,255.0f,255.0f);
        unsigned short nue = ++IDP;
        _interfaz -> DefinirIdPersonalizado(num,nue);
        _textosP.push_back(nue);
        _txtP = 0;
    #else
        //codigo motor irrlicht
        std::wstring widestr = std::wstring(texto.begin(), texto.end());
        // Parametro false, indica que no pinte el recuadro alrededor del texto
        _txtP = _guienv->addStaticText(widestr.c_str(), rect<s32>(x1, y1, x2, y2), false);
        _txtP->setID(++IDP);
        _textosP.push_back(move(_txtP));
        _txtP = nullptr;
    #endif
}

unsigned short MotorGrafico::CrearImagen(const char * texto,unsigned int x,unsigned int y,float scale)
{
    #ifdef WEMOTOR
        //const char * nuevo = "nada";
        //nuevo = texto.c_str();
        unsigned short did = _interfaz->AddImagen(texto,x,y,scale);
        //nuevo = "nadaadadada";
        return did;
    #endif
    return 0;
}

void MotorGrafico::AsignarCargando(unsigned short did)
{
    #ifdef WEMOTOR
        idCargando = did;
    #endif
}

void MotorGrafico::BorrarCargando()
{
    #ifdef WEMOTOR
        if(idCargando != 0)
        {
            _interfaz->RemoveObject(idCargando);
        }
    #endif
}

void MotorGrafico::DeshabilitarDinero()
{
    #ifdef WEMOTOR
        if(moneyI != 0)
        {
            _interfaz->DeshabilitarObjeto(moneyI);
        }
    #endif
}

void MotorGrafico::HabilitarDinero()
{
    #ifdef WEMOTOR
        if(moneyI != 0)
        {
            _interfaz->HabilitarObjeto(moneyI);
        }
    #endif
}

void MotorGrafico::cambiarAnimacion(int tipo ,int did ,int estado)//modo,id y estado
{
    #ifdef WEMOTOR
        unsigned short id;//id que tiene el objeto en el motor grafico
        Animaciones * anim = nullptr;//animacion perteneciente al motor grafico

        if(tipo == 0) //animaciones objetos
        {
            anim = ObjetosAni_Scena[did];
        }
        else if(tipo == 1) //animaciones recolectables
        {
            anim = RecoArmasAni_Scena[did];
        }
        else if(tipo == 2) //animaciones powerup
        {
            anim = PowerUPAni_Scena[did];
        }
        else if(tipo == 3) //animaciones llaves
        {
            anim = LlavesAni_Scena[did];
        }
        else if(tipo == 4) //animaciones paredes
        {
            anim = ParedesAni_Scena[did];
        }
        else if(tipo == 5) //enemigos
        {
            //std::cout << did << " " << estado << "\n";
            anim = EnemigosAni_Scena[did];
        }
        else if(tipo == 6) //cofres normales
        {
            anim = CofresAni_Scena[did];
        }

        //aqui mas

        if(anim != nullptr)
        {
            id = anim->GetID();
            if(id != 0)
            {
                int frame = _interfaz->getStartFrame(id);
                int frame_actual = _interfaz->getFrameNr(id);
                if(anim->ExisteEstado(estado) && anim->SePuedeCambiarEstado(frame_actual))
                {
                    anim->CambiarEstado(estado,frame,frame_actual);
                }
            }
        }
    #endif
}

void MotorGrafico::ActualizarAnimacionMotor(Animaciones * anima)
{
    #ifdef WEMOTOR
        if(anima != nullptr)
        {
            int frame_actual = _interfaz->getFrameNr(anima->GetID());
            if(frame_actual != -1)
            {
                anima->ProcesarAnimacion(frame_actual);//mira si debe cambiar de estado porque ha terminado la animacion y tiene salto automatico a otro
                if(anima->SeCambiaEstado())//esto indica si se ha cambiado estado
                {
                    unsigned int * devolucion = anima->Update();
                    //si se cambia aun estado que ya esta no se actualiza por lo que te devuelve un nullptr
                    if(devolucion != nullptr)
                    {
                        _interfaz->setBucle(anima->GetID(),anima->GetEstaEnBucle());
                        _interfaz->setFrameLoop(anima->GetID(),devolucion[0], devolucion[1]);
                        _interfaz->setAnimationSpeed(anima->GetID(),devolucion[2]);
                        delete [] devolucion;
                    }
                }
            }
        }
    #endif
}

void MotorGrafico::CambiarCamara()
{
    #ifdef WEMOTOR
        int lejano = 0;
        camara1 = !camara1;
        if (camara1)
        {
            altura = 0;
            lejano = 120;
            _interfaz->SetLejaniaCamara(camara, lejano);
        }
        else
        {
            altura = 250;
            lejano = 400;
            _interfaz->SetLejaniaCamara(camara, lejano);
        }
    #endif
}

void MotorGrafico::updateTeclas()
{
    #ifdef WEMOTOR
        Times * tempo = Times::GetInstance();

        float tiempoactual = tempo->GetTiempo(1);//tiempo actual en milisegundos

            //std::cout << " Actualizo teclas " << tiempoactual << std::endl;
            for(int i = 0; i <= numeroteclas;i++)
            {
                if(i != GLFW_MOUSE_BUTTON_RIGHT && i != GLFW_MOUSE_BUTTON_LEFT && i != GLFW_MOUSE_MOVE)
                {
                        if((!_interfaz->IsKeyRelease(i)))
                        {
                            if(estadoteclas2[i])//esto significa que no esta pulsado de antes
                            {
                                estadoteclas[i] = _interfaz->IsKeyDown(i);
                                estadoteclas2[i] = false;
                            }
                        }
                        else
                        {
                            estadoteclas2[i] = true;
                            estadoteclas[i]=false;
                        }
                }
                else
                {
                        if((!_interfaz->IsMouseUp(i)))
                        {
                            if(estadoteclas2[i])//esto significa que no esta pulsado de antes
                            {
                                estadoteclas[i] = _interfaz->IsMouseClick(i);
                                estadoteclas2[i] = false;
                            }
                        }
                        else
                        {
                            estadoteclas2[i] = true;
                            estadoteclas[i]=false;
                        }
                }
            }
            tiempo = tiempoactual;

    #endif
}

void MotorGrafico::CambiarAnchuraTexto(unsigned short did,unsigned int nuevoAncho)
{
    #ifdef WEMOTOR
        if(did != 0)
        {
            _interfaz->AnchoTexto(did,nuevoAncho);
        }
    #endif
}

unsigned int MotorGrafico::CrearBoton2(short xImagen, short yImagen, unsigned int escalado, short xTexto, short yTexto, unsigned int anchotexto, signed int id,const wchar_t* texto, const wchar_t* rutaimagen,bool esTexto,const char * rutapulsado,const char * rutaencima)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        wstring ws(rutaimagen);
        string str(ws.begin(),ws.end());
        const char * pru = str.c_str();
        unsigned short num = 0;

        if(rutapulsado != nullptr || rutaencima != nullptr)
        {
            num = _interfaz->AddImagen(pru,xImagen,yImagen ,(float)escalado, rutapulsado , rutaencima );
        }
        else
        {
            num = _interfaz->AddImagen(pru,xImagen,yImagen ,(float)escalado);
        }

        if(num != 0)
        {
            _interfaz->DeclararBoton(num,id);
            _interfaz->DefinirIdPersonalizado(num,id);
            if(esTexto)//si se debe crear texto con el boton
            {
                wstring ws(texto);
                string str(ws.begin(),ws.end());
                unsigned short num2 = _interfaz->CrearTexto(str,xImagen+xTexto,yImagen+yTexto,255.0f,255.0f,255.0f);
                _interfaz->DefinirTextoBoton(num,num2);
            }
        }
        return (unsigned int)num;
    #endif
}

void MotorGrafico::ActivarCapturaTexto()
{
    #ifdef WEMOTOR
        if( _interfaz)
        {
            _interfaz->ActivarCapturaTexto();
        }
    #endif
}

void MotorGrafico::DesactivarCapturaTexto()
{
    #ifdef WEMOTOR
        if( _interfaz)
        {
            _interfaz->DesactivarCapturaTexto();
        }
    #endif
}

char * MotorGrafico::DevolverTextoCapturado()
{
    #ifdef WEMOTOR
        if( _interfaz)
        {
            return _interfaz->DevolverTextoCapturado();
        }
        return nullptr;
    #endif
}

void MotorGrafico::InicializarCaptura(const char * texto)
{
    #ifdef WEMOTOR
        if( _interfaz)
        {
            _interfaz->InicializarCapturaTexto(texto);
        }
    #endif
}

void MotorGrafico::BorrarUltimaLetra()
{
    #ifdef WEMOTOR
        if( _interfaz)
        {
            _interfaz->BorrarUltimaLetra();
        }
    #endif
}

void MotorGrafico::CambiarTexto(unsigned int did, const char * texto)
{
    #ifdef WEMOTOR
        if( _interfaz)
        {
            string str = texto;
            //std::cout << "recoges tantas: " << str << std::endl;
            _interfaz->CambiarTexto(did,str);
        }
    #endif
}

void MotorGrafico::CambiarColorTexto(unsigned int did, float r, float g, float b)
{
    #ifdef WEMOTOR
        if( _interfaz && did != 0)
        {
            _interfaz->CambiarColorTexto(did,r,g,b);
        }
    #endif
}

void MotorGrafico::CambiarPosicionImagen(signed int event, float x, float y)
{
    #ifdef WEMOTOR
        if( _interfaz)
        {
            _interfaz->CambiarPosicionImagen(event,x,y);
        }
    #endif
}


unsigned int MotorGrafico::CrearVideo(const char * _ruta, float x, float y, unsigned int width, unsigned int height)
{
    #ifdef WEMOTOR
        if( _interfaz)
        {
          return _interfaz->CrearVideo(x,y,_ruta,width,height);
        }
    #endif

    return 0;
}

void MotorGrafico::PausarVideo(unsigned int id)
{
    #ifdef WEMOTOR
        if( _interfaz)
        {

        }
    #endif
}

void MotorGrafico::PlayVideo(unsigned int id)
{
    #ifdef WEMOTOR
        if( _interfaz)
        {

        }
    #endif
}

void MotorGrafico::EscalarMalla(unsigned int did, float escalado)
{
    #ifdef WEMOTOR
        if( _interfaz)
        {
            _interfaz->Escalar(did,escalado,escalado,escalado);
        }
    #endif 
}

unsigned int MotorGrafico::ObtenerIDOpengl(unsigned int tipo,unsigned int idVector)
{
    #ifdef WEMOTOR

        unsigned int idOpengl = 0;

        if(tipo == 0) //animaciones objetos
        {
            idOpengl = Objetos_Scena[idVector];
        }
        else if(tipo == 1) //animaciones recolectables
        {
            idOpengl = RecoArmas_Scena[idVector];
        }
        else if(tipo == 2) //animaciones powerup
        {
            idOpengl = PowerUP_Scena[idVector];
        }
        else if(tipo == 3) //animaciones llaves
        {
            idOpengl = Llaves_Scena[idVector];
        }
        else if(tipo == 4) //animaciones paredes
        {
            idOpengl = Paredes_Scena[idVector];
        }
        else if(tipo == 5) //enemigos
        {
            //std::cout << did << " " << estado << "\n";
            idOpengl = Enemigos_Scena[idVector];
        }
        else if(tipo == 6) //cofres normales
        {
            idOpengl = Cofres_Scena[idVector];
        }

    #endif 

        return idOpengl;
}