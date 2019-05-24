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
    pulsado=false;
}

void EstadoPuzle::Iniciar()
{
    _motor->IniIDPuzzles();
    _motor->FondoEscena(255,0,0,0);
    _motor->CargarFondoPuzzle();
    _motor->ActivarFuenteDefault();

    #ifdef WEMOTOR
        //codigo motor catopengl
        // No es necesario
    #else
        //codigo motor irrlicht
        _motor->PosicionCamaraEnPuzzles();
    #endif
    
    width = _motor->GetWidth();
    height = _motor->GetHeight();
    tipo = _puzzle->GetTipo();
    opciones = 0;
    solucion = _puzzle->GetSolucion();
    opciones = _puzzle->GetOpciones();

    width_aux = 0;
    height_aux = (height/2)+100;
    x_linea1 = 0;
    x_linea2 = 0;

    int yIMG = height_aux-125;
    int xIMG = 20;
    int anchoBtn = 40;
    int altoBtn = 30;

    _motor->CrearBoton(560,height-115,720,height-50, GUI_ID_ATRAS_PUZ,
        L"           Atras", L"Salir del puzzle");

    if (tipo == P_ACERTIJO)
    {
        _motor->CrearTextoPuzzles("Acertijo", 40,60,200,80);
        _motor->CrearTextoPuzzles(_puzzle->GetEnunciado(), 60,80,700,110); // Parametros: texto, x1, y1, x2, y2
        _motor->CrearTextoPuzzles("Ejemplo", (width-200),60,(width-160),80);
        
        // Imagen con la figura de ejemplo
        _motor->CargarIMGPuzzle(width-200, 80, _puzzle->GetImagen(0));

        if (opciones == 2)
        {
            width_aux = (width/4);
            _motor->CrearBoton(width_aux,height_aux,width_aux+anchoBtn,height_aux+altoBtn,
                GUI_ID_OP1, L"A", L"A");

            _motor->CrearBoton(width_aux*3,height_aux,width_aux*3+anchoBtn,height_aux+altoBtn,
                GUI_ID_OP2, L"B", L"B");
            
            _motor->CargarIMGPuzzle(width_aux-xIMG, yIMG, _puzzle->GetImagen(1));
            _motor->CargarIMGPuzzle(width_aux*3-xIMG, yIMG, _puzzle->GetImagen(2));
        }
        else
        {
            int altura = 160;
            width_aux = (width/8)-20;
            _motor->CrearBoton(width_aux*2,height_aux-altura,
                    width_aux+anchoBtn,(height_aux-altura)+altoBtn,
                GUI_ID_OP1, L"               A", L"A");

            _motor->CrearBoton(width_aux*5,height_aux-altura,
                    width_aux*3+anchoBtn,(height_aux-altura)+altoBtn,
                GUI_ID_OP2, L"               B", L"B");

            _motor->CargarIMGPuzzle(width_aux*3-23, yIMG-altura+30, _puzzle->GetImagen(1));
            _motor->CargarIMGPuzzle(width_aux*6-23, yIMG-altura+30, _puzzle->GetImagen(2));


            _motor->CrearBoton(width_aux*2,height_aux,
                    width_aux*5+anchoBtn,height_aux+altoBtn,
                GUI_ID_OP3, L"               C", L"C");

            _motor->CrearBoton(width_aux*5,height_aux,
                    width_aux*7+anchoBtn,height_aux+altoBtn,
                GUI_ID_OP4, L"               D", L"D");

            _motor->CargarIMGPuzzle(width_aux*3-23, yIMG+30, _puzzle->GetImagen(3));
            _motor->CargarIMGPuzzle(width_aux*6-23, yIMG+30, _puzzle->GetImagen(4));
            _motor->DeshabilitarDinero();
        }
    }
    else // Torres de Hanoi
    {
        pasos = 0;
        pulsado=false;
        pilaInicial = NO_SELECT; // Para colocar las fichas en pilaIzq
        pilaFinal = NO_SELECT;
        fichaMover = 0;

        // Monta la interfaz dependiendo del tipo de puzzle
        _motor->CrearTextoPuzzles("Torres de hanoi", 40,60,200,80);
        _motor->CrearEnunciadoHanoi(_puzzle->GetEnunciado(), 60,80,700,110); // Parametros: texto, x1, y1, x2, y2
        _motor->CrearTextoPasos(50, 530, 100, 50);
        _motor->CrearBoton(560,height-160,720,height-50, GUI_ID_REINICIAR_HANOI,
            L"        Reiniciar", L"Reiniciar puzzle");

        width_aux = (width-2)/6;
        _motor->CrearTextoPuzzles("IZQ", width_aux,420,width_aux+anchoBtn,130);
        _motor->CrearTextoPuzzles("CENTRO", width_aux*3,420,width_aux*3+anchoBtn,130);
        _motor->CrearTextoPuzzles("DER", width_aux*5,420,width_aux*5+anchoBtn,130);

        // Para la ventana de 800, 600
        // width = 798, dejamos 1 punto a cada lado
        width_aux = (width-2)/3;    // Dividimos la pantalla en 3 zonas
        x_linea1 = width_aux;
        x_linea2 = width_aux*2;

        // Rellenamos la pilaIzq
        crearFichasPila();
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
    _motor->UpdateMotorPuzzles(tipo, x_linea1, x_linea2);
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
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        _motor->ResetEvento(GUI_ID_ATRAS_PUZ);
        atras();
    }

    if (tipo == P_ACERTIJO)
    {
       comprobarEventosOpciones();
    }
    else
    {
        comprobarEventosHanoi();
    }
}

// Vuelve al juego
void EstadoPuzle::atras()
{
    _motor->BorrarGuiPuzzle(tipo, opciones);
    _motor->HabilitarDinero();
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

void EstadoPuzle::comprobarEventosHanoi()
{
    if(_motor->OcurreEvento(GUI_ID_REINICIAR_HANOI))
    {
        _motor->ResetEvento(GUI_ID_REINICIAR_HANOI);
        if (pasos > 0) {
            // Reiniciamos posiciones mallas fichas
            _motor->ReiniciarHanoi();
            reiniciarPilas();
        }
    }

    _motor->ActualizarTextoPasos(pasos);

    /*if((_motor->PulsadoClicIzq()) && (!_motor->EstaPulsado(MOUSE_MOVED)))
    {
        cout<<"Pulso solo"<<endl;
        //pulsado=true;
        std::vector<unsigned short> * vectorFichas = _motor->GetVectorFichas();
        unsigned int cont = 0;
        while ((!pulsado) && (cont < 3))
        {
            if(_motor->OcurreEvento((*vectorFichas)[cont]))
            {
                pulsado=true;
                fichaMover = cont;
            }
            cont++;
        }
        cont = 0;*/
        
        /*if (pulsado)
        {
            //cout << "Objeto"<<endl;
            // Obtenemos la zona seleccionada
            pilaInicial = getZonaVentana();
            // Comprobamos que la pila no este vacia
            if (!comprobarPilaVacia(pilaInicial)) {
                // Solo movemos la ficha si es la primera de la pila
                if (!comprobarTopPila(_motor->GetFichaY()))
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
            pilaInicial = NO_SELECT;se quedar
        }*/
    //}

    /*if((_motor->PulsadoClicIzq()) &&se quedarsado(MOUSE_MOVED))) {
        //cout<<"X: "<<_motor->GetPosicionRaton().X<<" Y: "<<_motor->GetPosicionRaton().Y<<endl;
        cout<<"Arrastrar"<<endl;

        if (pulsado)
        {
            _motor->CambiarPosicionImagen(fichaMover, _motor->GetPosicionRaton()[0], _motor->GetPosicionRaton()[1]);
        }
    }

    if ((_motor->SueltoClicIzq()) && (pulsado))
    {
        //cout<<"Soltar"<<endl;
        pulsado=false;
        deseleccionarNodo();
        _motor->ResetEventoMoveRaton();
    }*/
}

void EstadoPuzle::corregirSolucion(int opcion)
{
    _motor->ResetKey(LMOUSE_PRESSED_DOWN);
    _motor->BorrarGuiPuzzle(tipo, opciones);

    if (opcion == solucion) {
        Juego::GetInstance()->estado.ReanudarDesdePuzzle(true);
    } else {
       Juego::GetInstance()->estado.ReanudarDesdePuzzle(false);
    }
}

void EstadoPuzle::comprobarGanar()
{
    int tam = pilaDer.size();
    if (pasos <= solucion*2) {
        // Comprobar fin de juego
        if (tam == opciones) {
            if (pilaDer.top()->GetTamayo() == 1) {
                ficha = pilaDer.top();
                pilaDer.pop();
                if (pilaDer.top()->GetTamayo() == 2) {

                    cout << "Has ganado" << endl;
                    Juego::GetInstance()->estado.ReanudarDesdePuzzle(true);
                }
                pilaDer.push(ficha);
            }
        }
    } else {

        cout << "Salta la araña" << endl;
        Juego::GetInstance()->estado.ReanudarDesdePuzzle(false);
    }
}

void EstadoPuzle::crearFichasPila()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        int img = 0;
        int posY_OpenGL = 400;
        for (int tam=opciones; tam>0; tam--) 
        {
            img = _motor->CrearFichas(100, posY_OpenGL, tam); //X, Y, tamanyo
            ficha = new PilaFichas(tam, posY_OpenGL);
            ficha->SetIMG(img);
            pilaIzq.push(ficha);
            posY_OpenGL-=80;
        }
    #else
        //codigo motor irrlicht
        int posY_irr = 0;
        for (int tam=opciones; tam>0; tam--)
        {
            int r = rand() % (256 + 100); // +100 para que no salga blanco
            int g = rand() % (256 + 0);
            int b = rand() % (256 + 0);
            _motor->CrearFichas(IZQ, posY_irr, tam, r, g, b);
            ficha = new PilaFichas(tam, posY_irr);
            pilaIzq.push(ficha);
            posY_irr++;
        }
    #endif
}

bool EstadoPuzle::comprobarPilaVacia(int pila)
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

bool EstadoPuzle::comprobarTopPila(int fichaY)
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
bool EstadoPuzle::comprobarTamanyo()
{
    int tamPI = -1;
    int tamPF = -1;
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
            if (!comprobarPilaVacia(pilaFinal)) {
                tamPF = pilaIzq.top()->GetTamayo();
            }
        break;

        case CENTRO:
            if (!comprobarPilaVacia(pilaFinal)) {
                tamPF = pilaCentro.top()->GetTamayo();
            }
        break;

        case DER:
            if (!comprobarPilaVacia(pilaFinal)) {
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

int EstadoPuzle::recolocarFicha()
{
    int y = -1;
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

void EstadoPuzle::sacarFicha()
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

int EstadoPuzle::meterFicha()
{
    int y = 0;
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

void EstadoPuzle::reiniciarPilas()
{
    // Reiniciamos las variables
    pilaInicial = NO_SELECT;
    pasos = 0;
    pulsado=false;
    fichaMover = 0;

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
    int posY = 0;
    for (int tam=opciones; tam>0; tam--) {
        ficha = new PilaFichas(tam, posY);
        pilaIzq.push(ficha);
        posY++;
    }
}

void EstadoPuzle::deseleccionarNodo()
{
    // No mueve la ficha de zona
    if (pilaInicial != NO_SELECT)
    {
        // Obtenemos la zona donde se suelta la ficha
        pilaFinal = getZonaVentana();

        if (pilaInicial == pilaFinal) // Misma zona
        {
            //_motor->RecolocarFicha(recolocarFicha(), pilaInicial);
        }
        else // Distinta zona
        {
            if (comprobarTamanyo())
            {
                pasos++;
                sacarFicha();
                //_motor->RecolocarFicha(meterFicha(), pilaFinal);
                comprobarGanar();
            }
            else
            {
                //_motor->RecolocarFicha(recolocarFicha(), pilaInicial);
            }
        }
    }

    // Reiniciamos valores
    pilaInicial = NO_SELECT;
    pilaFinal = NO_SELECT;
}

int EstadoPuzle::getZonaVentana()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        int posX = (int)_motor->GetPosicionRaton()[0];
    #else
        //codigo motor irrlicht
        int posX = _motor->GetPosicionRaton().X;
    #endif

    if ((posX > 0) && (posX <= width)) {
        if ((posX > 0) && (posX <= width_aux)) {
            return IZQ;
        } else if ((posX > width_aux) && (posX <= width_aux*2)) {
            return CENTRO;
        } else {
            return DER;
        }
    }
    return NO_SELECT;// Fuera de ventana
}


// MotorGrafico *************************************************
/*  
    bool SeleccionarNodo();
    void DeseleccionarNodo();
    int GetFichaY();
    void MoverFichas(int pila);
    void RecolocarFicha(int y, int z);
*/

/*
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
int MotorGrafico::GetFichaY()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
    #else
        //codigo motor irrlicht
        return _nodoSeleccionado->getAbsolutePosition().Y;
    #endif
}
void MotorGrafico::MoverFichas(int pila)
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
void MotorGrafico::RecolocarFicha(int y, int z)
{
    #ifdef WEMOTOR
        //codigo motor catopengl
    #else
        //codigo motor irrlicht
        int x = _nodoSeleccionado->getAbsolutePosition().X;
        _nodoSeleccionado->setPosition(vector3df(x, y, z));
    #endif
}
*/