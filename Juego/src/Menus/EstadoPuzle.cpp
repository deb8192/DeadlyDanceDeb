#include "EstadoPuzle.hpp"
#include "../Juego.hpp"

EstadoPuzle::EstadoPuzle(int* puzzle)
{
    _motor = MotorGrafico::GetInstance();
    _puzzle = (Puzzle*) puzzle;
}

EstadoPuzle::~EstadoPuzle()
{
    _motor = nullptr;
    _puzzle = nullptr;
}

void EstadoPuzle::Iniciar()
{
    _motor->IniIDPuzzles();
    _motor->FondoEscena(255,0,0,0);
    _motor->CargarFondoPuzzle();
    _motor->ActivarFuenteDefault();

    width = _motor->GetWidth();
    height = _motor->GetHeight();

    _motor->CrearBoton(700,height-80,750,height-50, GUI_ID_ATRAS_PUZ, L"Atrás", L"Salir del puzzle");
    _motor->CrearTextoPuzzles(_puzzle->GetEnunciado(), 60,80,700,110); // Parametros: texto, x1, y1, x2, y2

    tipo = _puzzle->GetTipo();
    opciones = 0;
    solucion = _puzzle->GetSolucion();

    if (tipo == P_ACERTIJO)
    {
        _motor->CrearTextoPuzzles("Acertijo", 40,60,200,80);
        _motor->CrearTextoPuzzles("Ejemplo", (width-200),60,(width-160),80);
        
        // Imagen con la figura de ejemplo
        _motor->CargarIMGPuzzle(width-200, 80, _puzzle->GetImagen(0));

        opciones = _puzzle->GetOpciones();
        short width_aux = 0;

        short height_aux = (height/2)+100;
        short yIMG = height_aux-125;
        short xIMG = 20;
        short anchoBtn = 40;
        short altoBtn = 30;

        if (opciones == 2)
        {
            width_aux = width/4;
            _motor->CrearBoton(width_aux,height_aux,width_aux+anchoBtn,height_aux+altoBtn,
                GUI_ID_OP1, L"A", L"A");

            _motor->CrearBoton(width_aux*3,height_aux,width_aux*3+anchoBtn,height_aux+altoBtn,
                GUI_ID_OP2, L"B", L"B");
            
            _motor->CargarIMGPuzzle(width_aux-xIMG, yIMG, _puzzle->GetImagen(1));
            _motor->CargarIMGPuzzle(width_aux*3-xIMG, yIMG, _puzzle->GetImagen(2));
        }
        else
        {
            width_aux = width/8;
            _motor->CrearBoton(width_aux,height_aux,
                    width_aux+anchoBtn,height_aux+altoBtn,
                GUI_ID_OP1, L"A", L"A");

            _motor->CrearBoton(width_aux*3,height_aux,
                    width_aux*3+anchoBtn,height_aux+altoBtn,
                GUI_ID_OP2, L"B", L"B");

            _motor->CrearBoton(width_aux*5,height_aux,
                    width_aux*5+anchoBtn,height_aux+altoBtn,
                GUI_ID_OP3, L"C", L"C");

            _motor->CrearBoton(width_aux*7,height_aux,
                    width_aux*7+anchoBtn,height_aux+altoBtn,
                GUI_ID_OP4, L"D", L"D");

            _motor->CargarIMGPuzzle(width_aux-xIMG, yIMG, _puzzle->GetImagen(1));
            _motor->CargarIMGPuzzle(width_aux*3-xIMG, yIMG, _puzzle->GetImagen(2));
            _motor->CargarIMGPuzzle(width_aux*5-xIMG, yIMG, _puzzle->GetImagen(3));
            _motor->CargarIMGPuzzle(width_aux*7-xIMG, yIMG, _puzzle->GetImagen(4));
        }

        // TO DO: Tiene que resetearlo, no se porque
        _motor->ResetEvento(GUI_ID_OP1);
    }
    else // Torres de Hanoi
    {
        // Monta la interfaz dependiendo del tipo de puzzle
        /*_motor->PuzzlesGui(GetTipo(), GetEnunciado(), GetOpciones());

        pasos = 0;
        pilaInicial = NO_SELECT; // Para colocar las fichas en pilaIzq
        pilaFinal = NO_SELECT;

        // Rellenamos la pilaIzq
        CrearFichasPila();
        _motor->TextoPasos(pasos);*/
    }
}

// Actualiza lo que se ve por pantalla
void EstadoPuzle::Render()
{
    _motor->FondoEscena(255,0,0,0); // Borra
    _motor->RenderEscena();               // Vuelve a pintar
}

void EstadoPuzle::Update()
{
    //cout << "Paso mas de 1 vez por aqui" <<endl;
    //_motor->update_motorPuzzles(GetTipo());
}

void EstadoPuzle::ManejarEventos()
{
    // Temporal para pruebas
    if (_motor->EstaPulsado(KEY_ESC)) {
        _motor->ResetKey(KEY_ESC);
        atras();
    }

    if (_motor->OcurreEvento(GUI_ID_ATRAS_PUZ))
    {
        _motor->ResetEvento(GUI_ID_ATRAS_PUZ);
        atras();
    }

    if (tipo == P_ACERTIJO)
    {
       comprobarEventosOpciones();
    }
    else
    {
        //ComprobarEventosHanoi();
    }
    
}

// Vuelve al juego
void EstadoPuzle::atras()
{
    _motor->BorrarGuiPuzzle(tipo, opciones);
    Juego::GetInstance()->estado.QuitarPausa();
}

void EstadoPuzle::comprobarEventosOpciones()
{
    if(_motor->OcurreEvento(GUI_ID_OP1))// Boton A
    {
        _motor->ResetEvento(GUI_ID_OP1);
        corregirSolucion(1);
    }
    if(_motor->OcurreEvento(GUI_ID_OP2))// Boton B
    {
        _motor->ResetEvento(GUI_ID_OP2);
        corregirSolucion(2);
    }
    if(_motor->OcurreEvento(GUI_ID_OP3))// Boton C
    {
        _motor->ResetEvento(GUI_ID_OP3);
        corregirSolucion(3);
    }
    if(_motor->OcurreEvento(GUI_ID_OP4))// Boton D
    {
        _motor->ResetEvento(GUI_ID_OP4);
        corregirSolucion(4);
    }
}

void EstadoPuzle::corregirSolucion(unsigned short opcion)
{
     _motor->BorrarGuiPuzzle(tipo, opciones);

    if (opcion == solucion) {
        cout << "Correcto" <<endl;
        Juego::GetInstance()->estado.ReanudarDesdePuzzle(true);
    } else {
        cout << "Has fallado" <<endl;
       Juego::GetInstance()->estado.ReanudarDesdePuzzle(false);
    }
}

/*
void EstadoPuzle::CrearFichasPila()
{
    
    short posY = 0;
    for (int tam=GetOpciones(); tam>0; tam--) {

        short r = rand() % (256 + 100); // +100 para que no salga blanco
        short g = rand() % (256 + 0);
        short b = rand() % (256 + 0);
        _motor->CrearFichas(posY, tam, r, g, b);

        ficha = new PilaFichas(tam, posY);
        pilaIzq.push(ficha);
        posY++;
    }
}

void EstadoPuzle::ComprobarEventosHanoi()
{
    if(_motor->OcurreEvento(GUI_ID_REINICIAR_HANOI))
    {
        _motor->ResetEvento(GUI_ID_REINICIAR_HANOI);
        if (pasos > 0) {
            // Reiniciamos posiciones mallas fichas
            _motor->ReiniciarHanoi();
            ReiniciarPilas();
        }
    }

    if((_motor->PulsadoClicIzq()) && (!_motor->estaPulsado(MOUSE_MOVED)))
    {
        //cout<<"Pulso solo"<<endl;
        pulsado=true;
        if (_motor->SeleccionarNodo()) {
            //cout << "Objeto"<<endl;

            // Obtenemos la zona seleccionada
            pilaInicial = _motor->GetZonaVentana();

            // Comprobamos que la pila no este vacia
            if (!ComprobarPilaVacia(pilaInicial)) {
                // Solo movemos la ficha si es la primera de la pila
                if (!ComprobarTopPila(_motor->GetFichaY()))
                {
                    _motor->DeseleccionarNodo();
                    pilaInicial = NO_SELECT;
                }
            } else {
                //cout << "Pila vacia"<<endl;
                _motor->DeseleccionarNodo();
                pilaInicial = NO_SELECT;
            }

        } else {
            //cout << "Fondo"<<endl;
            pilaInicial = NO_SELECT;
        }
    }

    if((_motor->PulsadoClicIzq()) && (_motor->estaPulsado(MOUSE_MOVED))) {
        //cout<<"X: "<<_motor->GetPosicionRaton().X<<" Y: "<<_motor->GetPosicionRaton().Y<<endl;
        //cout<<"Arrastrar"<<endl;
        _motor->MoverFichas(pilaInicial);
    }

    if ((_motor->SueltoClicIzq()) && (pulsado))
    {
        //cout<<"Soltar"<<endl;
        pulsado=false;
        DeseleccionarNodo();
        _motor->ResetEventoMoveRaton();
    }
    _motor->TextoPasos(pasos);
}

void EstadoPuzle::DeseleccionarNodo()
{
    // No mueve la ficha de zona
    if (pilaInicial != NO_SELECT)
    {
        // Obtenemos la zona donde se suelta la ficha
        pilaFinal = _motor->GetZonaVentana();

        if (pilaInicial == pilaFinal)           // Misma zona
        {
            _motor->RecolocarFicha(RecolocarFicha(), pilaInicial);
        } else {                            // Distinta zona

            if (ComprobarTamanyo()) {
                pasos++;
                SacarFicha();
                _motor->RecolocarFicha(MeterFicha(), pilaFinal);
                ComprobarGanar();

            } else {
                _motor->RecolocarFicha(RecolocarFicha(), pilaInicial);
            }
        }
    }

    // Reiniciamos valores
    pilaInicial = NO_SELECT;
    pilaFinal = NO_SELECT;
}

bool EstadoPuzle::ComprobarPilaVacia(short pila)
{
    switch (pila) {
        case IZQ:
            if (pilaIzq.empty()) {
                return true;
            }
        break;

        case CENTRO:
            if (pilaCentro.empty()) {
                return true;
            }
        break;

        case DER:
            if (pilaDer.empty()) {
                return true;
            }
        break;
    }
    return false;
}

bool EstadoPuzle::ComprobarTopPila(short fichaY)
{
    switch (pilaInicial) {
        case IZQ:
            if (pilaIzq.top()->GetPosY() == fichaY) {
                return true;
            }
        break;

        case CENTRO:
            if (pilaCentro.top()->GetPosY() == fichaY) {
                return true;
            }
        break;

        case DER:
            if (pilaDer.top()->GetPosY() == fichaY) {
                return true;
            }
        break;
    }
    return false;
}

// Si la ficha a mover es mas peque que donde va, se mueve
bool EstadoPuzle::ComprobarTamanyo()
{
    short tamPI = -1;
    short tamPF = -1;
    switch (pilaInicial) {
        case IZQ:
            tamPI = pilaIzq.top()->GetTamayo();
        break;

        case CENTRO:
            tamPI = pilaCentro.top()->GetTamayo();
        break;

        case DER:
            tamPI = pilaDer.top()->GetTamayo();
        break;
    }

    switch (pilaFinal) {
        case IZQ:
            if (!ComprobarPilaVacia(pilaFinal)) {
                tamPF = pilaIzq.top()->GetTamayo();
            }
        break;

        case CENTRO:
            if (!ComprobarPilaVacia(pilaFinal)) {
                tamPF = pilaCentro.top()->GetTamayo();
            }
        break;

        case DER:
            if (!ComprobarPilaVacia(pilaFinal)) {
                tamPF = pilaDer.top()->GetTamayo();
            }
        break;
    }

    // Para que cambie cuando la pilaFinal esta vacia
    if (tamPF == -1) {
        tamPF = tamPI+1;
    }

    // Comprueba si se cambia o no
    if (tamPI < tamPF) {
        return true;
    }
    return false;
}

short EstadoPuzle::RecolocarFicha()
{
    short y = -1;
    switch(pilaInicial)
    {
        case IZQ:
            y = pilaIzq.top()->GetPosY();
            break;

        case CENTRO:
            y = pilaCentro.top()->GetPosY();
            break;

        case DER:
            y = pilaDer.top()->GetPosY();
            break;
    }
    return y;
}

void EstadoPuzle::SacarFicha()
{
    switch(pilaInicial)
    {
        case IZQ:
            ficha = pilaIzq.top();
            pilaIzq.pop();
            break;

        case CENTRO:
            ficha = pilaCentro.top();
            pilaCentro.pop();
            break;

        case DER:
            ficha = pilaDer.top();
            pilaDer.pop();
            break;
    }
}

short EstadoPuzle::MeterFicha()
{
    short y = 0;
    switch(pilaFinal)
    {
        case IZQ:
            if (!pilaIzq.empty()) {
                y = pilaIzq.top()->GetPosY()+1;
            }
            ficha->SetPosY(y);
            pilaIzq.push(ficha);
            break;

        case CENTRO:
            if (!pilaCentro.empty()) {
                y = pilaCentro.top()->GetPosY()+1;
            }
            ficha->SetPosY(y);
            pilaCentro.push(ficha);
            break;

        case DER:
            if (!pilaDer.empty()) {
                y = pilaDer.top()->GetPosY()+1;
            }
            ficha->SetPosY(y);
            pilaDer.push(ficha);
            break;
    }
    return y;
}

void EstadoPuzle::ReiniciarPilas()
{
    // Reiniciamos las variables
    pilaInicial = NO_SELECT;
    pasos = 0;

    // Reiniciamos la pila de fichas
    while (!pilaIzq.empty() )
    {
        ficha = pilaIzq.top();
        delete(ficha);
        pilaIzq.pop();
    }

    while (!pilaCentro.empty() )
    {
        ficha = pilaCentro.top();
        delete(ficha);
        pilaCentro.pop();
    }

    while (!pilaDer.empty() )
    {
        ficha = pilaDer.top();
        delete(ficha);
        pilaDer.pop();
    }

    // Rellenamos la pilaIzq
    short posY = 0;
    for (int tam=GetOpciones(); tam>0; tam--) {
        ficha = new PilaFichas(tam, posY);
        pilaIzq.push(ficha);
        posY++;
    }
}

void EstadoPuzle::ComprobarGanar()
{
    short tam = pilaDer.size();
    if (pasos <= GetSolucion()*2) {
        // Comprobar fin de juego
        if (tam == GetOpciones()) {
            if (pilaDer.top()->GetTamayo() == 1) {
                ficha = pilaDer.top();
                pilaDer.pop();
                if (pilaDer.top()->GetTamayo() == 2) {
                    cout << "Has ganado" << endl;
                }
                pilaDer.push(ficha);
            }
        }
    } else {
        cout << "Salta la araña" << endl;
    }
}*/







// MotorGrafico *************************************************
    /*// Funciones para puzzles
    void PosicionCamaraEnPuzzles();
    void updateMotorPuzzles(short tipo);
    void PuzzlesGui(short tipo, std::string enun, short opciones);
    void TextoPasos(short pasos);
    void CrearFichas(short posY, float tamanyo,
            int r, int g, int b);
    short GetZonaVentana();
    bool SeleccionarNodo();
    void DeseleccionarNodo();
    short GetFichaY();
    void MoverFichas(short pila);
    void RecolocarFicha(short y, short z);
    void ReiniciarHanoi();
	void CrearMeshFicha(float tamanyo, int r, int g, int b);


             // Objetos y funciones para puzzles
                IGUIStaticText* _myTextBox;

                IMesh* _fichaMesh;                         // Malla
                IMeshSceneNode* _ficha;                    // Nodo
                std::vector<IMeshSceneNode*> fichasMesh;  // Lista de nodos (fichas)

                // Para seleccionar nodos
                position2di initialCursorPosition;        // Posicion del clic raton
                position2di initialObjectPosition;        // Posicion del objeto que intersecta con el ray
                ISceneNode* _nodoSeleccionado;

                // Ventana
                short x_linea1, x_linea2;

                enum posZ { IZQ=-9, CENTRO=0, DER=9, NO_SELECT=-1 };*/







/*_myTextBox = nullptr;
_fichaMesh = nullptr;
_ficha = nullptr;
_nodoSeleccionado = nullptr;
_img = nullptr;
_puzParticleTexture = nullptr;
WIDTH_AUX = 0; WIDTH = 0; HEIGHT = 0;
x_linea1 = 0; x_linea2 = 0;*/

/*void MotorGrafico::PosicionCamaraEnPuzzles()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
    #else
        //codigo motor irrlicht
        _camera->setPosition(vector3df(14, 2, 0)); // No cambiar la Y, si nos la seleccion tendra errores
    #endif
}


void MotorGrafico::PuzzlesGui(short tipo, std::string enun, short opciones)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
    #else
        //codigo motor irrlicht
        short height_aux = (HEIGHT/2)+100;
        short yIMG = height_aux-125;
        short xIMG = 20;
        short anchoBtn = 40;
        short altoBtn = 30;

        if (tipo == P_HANOI)
        {
            
                _guienv->addStaticText(L"Torres de Hanoi", rect<s32>(0,0,200,20), false);

                // Reiniciar
                _guienv->addButton(rect<s32>(700,HEIGHT-90,750,HEIGHT-60), 0,
                    GUI_ID_REINICIAR_HANOI,L"Reiniciar", L"Reinicia el juego");

                _myTextBox = _guienv->addStaticText(L"Pasos: ", rect<s32>(60,(WIDTH/2)-10,100,(WIDTH/2)+30), false);

                WIDTH_AUX = (WIDTH-2)/6;
                _guienv->addStaticText(L"IZQ", rect<s32>(WIDTH_AUX,100,WIDTH_AUX+anchoBtn,130), false);
                _guienv->addStaticText(L"CENTRO", rect<s32>(WIDTH_AUX*3,100,WIDTH_AUX*3+anchoBtn,130), false);
                _guienv->addStaticText(L"DER", rect<s32>(WIDTH_AUX*5,100,WIDTH_AUX*5+anchoBtn,130), false);

                // Para la ventana de 800, 600
                // Width = 798, dejamos 1 punto a cada lado
                WIDTH_AUX = (WIDTH-2)/3;    // Dividimos la pantalla en 3 zonas
                x_linea1 = WIDTH_AUX;
                x_linea2 = WIDTH_AUX*2;
        }
    #endif
}

void MotorGrafico::TextoPasos(short pasos)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
    #else
        //codigo motor irrlicht
        stringw str = L"Pasos: ";
        str += pasos;
        _myTextBox->setText(str.c_str());
        _myTextBox = nullptr;
    #endif
}

void MotorGrafico::CrearMeshFicha(float tamanyo, int r, int g, int b)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
    #else
        //codigo motor irrlicht
        //_fichaMesh = _geometryCreator->createCubeMesh(vector3df(tamanyo));
        _fichaMesh = _geometryCreator->createCylinderMesh(
            tamanyo,    //radius
            1,          //length
            50,         //tesselation
            SColor(0, r, g, b));

        // insensible a la iluminacion
        _fichaMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    #endif
}

void MotorGrafico::CrearFichas(short posY, float tamanyo,
    int r, int g, int b)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
    #else
        //codigo motor irrlicht
        CrearMeshFicha(tamanyo, r, g, b);
        _ficha = _smgr->addMeshSceneNode(_fichaMesh);
        _ficha->setPosition(vector3df(0, posY, IZQ));
        _ficha->setID(tamanyo);

        // La anyadimos a la lista
        fichasMesh.push_back(move(_ficha));
        _ficha = nullptr;
    #endif
}

short MotorGrafico::GetZonaVentana()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
    #else
        //codigo motor irrlicht
        short posX = GetPosicionRaton().X;
        if ((posX > 0) && (posX <= WIDTH)) {
            if ((posX > 0) && (posX <= WIDTH_AUX)) {
                return IZQ;
            } else if ((posX > WIDTH_AUX) && (posX <= WIDTH_AUX*2)) {
                return CENTRO;
            } else {
                return DER;
            }
        }
        return NO_SELECT;// Fuera de ventana
    #endif
}

bool MotorGrafico::SeleccionarNodo()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        return false;
    #else
        //codigo motor irrlicht
        // check for a node being selected
        // Posicion, idBitMask (0=deshabilitada), bNoDebugObjects (true=No tiene en cuenta los objetos de depuracion)
        _nodoSeleccionado = _collmgr->getSceneNodeFromScreenCoordinatesBB(
            _device->getCursorControl()->getPosition(),0,true);

        // Si hay un nodo seleccionado
        if(_nodoSeleccionado)
        {
            // Remember where the node and cursor were when it was clicked on
            initialCursorPosition = _device->getCursorControl()->getPosition();
            // Calcula la posición de la pantalla 2d desde una posición 3d.
            initialObjectPosition = _collmgr->getScreenCoordinatesFrom3DPosition(
                _nodoSeleccionado->getAbsolutePosition(), _camera);

            if (_nodoSeleccionado->getID() != -1) { // Comprobamos que no sea el fondo
                return true;
            }
        }
        else
        {
            _nodoSeleccionado = nullptr;
        }
        return false;
    #endif
}

void MotorGrafico::DeseleccionarNodo()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
    #else
        //codigo motor irrlicht
        _nodoSeleccionado = 0;
    #endif
}

short MotorGrafico::GetFichaY()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
    #else
        //codigo motor irrlicht
        return _nodoSeleccionado->getAbsolutePosition().Y;
    #endif
}

void MotorGrafico::MoverFichas(short pila)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
    #else
        //codigo motor irrlicht
        if ((_nodoSeleccionado) && (pila != NO_SELECT))
        {
            plane3df const planeXZ(_nodoSeleccionado->getAbsolutePosition(), vector3df(1.f, 0.f, 0.f));

            position2di currentCursorPosition(_device->getCursorControl()->getPosition());
            position2di effectiveObjectPosition = initialObjectPosition + currentCursorPosition - initialCursorPosition;
            line3df ray(_collmgr->getRayFromScreenCoordinates(effectiveObjectPosition, _camera));
            vector3df intersectWithPlane;

            if(planeXZ.getIntersectionWithLine(ray.start, ray.getVector(), intersectWithPlane))
            {
                _nodoSeleccionado->setPosition(intersectWithPlane);
            }
        }
    #endif
}

void MotorGrafico::RecolocarFicha(short y, short z)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
    #else
        //codigo motor irrlicht
        short x = _nodoSeleccionado->getAbsolutePosition().X;
        _nodoSeleccionado->setPosition(vector3df(x, y, z));
    #endif
}

void MotorGrafico::ReiniciarHanoi()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
    #else
        //codigo motor irrlicht
        short tam = fichasMesh.size();
        short posY=0;
        for (int pos = 0; pos<tam; pos++)
        {
            fichasMesh.at(pos)->setPosition(vector3df(0, posY, IZQ));
            posY++;
        }
    #endif
}

void MotorGrafico::updateMotorPuzzles(short tipo)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
    #else
        //codigo motor irrlicht
        _driver->beginScene(true, true, SColor(255,255,255,255));//fondo blanco
        _smgr->drawAll();
        _guienv->drawAll();

        /* Probando a dibujar objetos 2D
        //Rectangulo
        _driver->draw2DRectangle(SColor(255, 255, 128, 64), rect<s32>(40, 40, 200, 200));

        //Poligono
        _driver->draw2DPolygon(position2d<s32>(100, 300), 50.f, SColor(128, 40, 80, 16), 6);*/

        /*if (tipo == P_HANOI)
        {
		// Lineas para dividir la pantalla
		_driver->draw2DLine(position2d<s32>(x_linea1 , 200),
		    position2d<s32>(x_linea1, 400 ) , SColor(255, 0, 0, 0));
		_driver->draw2DLine(position2d<s32>(x_linea2 , 200),
		    position2d<s32>(x_linea2, 400 ) , SColor(255, 0, 0, 0));
        }

        _driver->endScene();
    #endif
}*/