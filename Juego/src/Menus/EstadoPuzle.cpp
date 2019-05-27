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
        /*_motor->CrearTextoPuzzles("IZQ", width_aux,420,width_aux+anchoBtn,130);
        _motor->CrearTextoPuzzles("CENTRO", width_aux*3,420,width_aux*3+anchoBtn,130);
        _motor->CrearTextoPuzzles("DER", width_aux*5,420,width_aux*5+anchoBtn,130);*/

        // Para la ventana de 800, 600
        // width = 798, dejamos 1 punto a cada lado
        width_aux = (width-2)/3;    // Dividimos la pantalla en 3 zonas
        x_linea1 = width_aux;
        x_linea2 = width_aux*2;
        iniXFichas = IZQ;

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
    if (tipo == P_ACERTIJO)
    {
       comprobarEventosOpciones();
    }
    else
    {
        comprobarEventosHanoi();
    }
}

void EstadoPuzle::atras()
{
    if ((_motor->OcurreEvento(GUI_ID_ATRAS_PUZ)) ||
        (_motor->EstaPulsado(KEY_ESC)))
    {
        _motor->ResetKey(KEY_ESC);
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        _motor->ResetEvento(GUI_ID_ATRAS_PUZ);
        _motor->BorrarGuiPuzzle(tipo, opciones);
        _motor->HabilitarDinero();
        Juego::GetInstance()->estado.QuitarPausa();
    }
}

void EstadoPuzle::comprobarEventosOpciones()
{
    atras(); // Comprobamos si se pulsan los botones para volver al juego

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
    if (!pulsado)
    {
        atras();
        if(_motor->OcurreEvento(GUI_ID_REINICIAR_HANOI))
        {
            _motor->ResetEvento(GUI_ID_REINICIAR_HANOI);
            if (pasos > 0) {
                // Reiniciamos posiciones mallas fichas
                _motor->ReiniciarHanoi(IZQ, 400);

                _motor->CambiarPosicionImagen(GUI_FICHA_1, iniXFichas, 400);
                _motor->CambiarPosicionImagen(GUI_FICHA_2, iniXFichas, 480);
                _motor->CambiarPosicionImagen(GUI_FICHA_3, iniXFichas, 560);

                reiniciarPilas();
            }
        }
    }
    _motor->ActualizarTextoPasos(pasos);

    if((_motor->PulsadoClicIzq()) && (!pulsado))
    {
        if(_motor->OcurreEvento(GUI_FICHA_1))
        {
            pulsado=true;
            fichaMover = GUI_FICHA_1;
        } else if(_motor->OcurreEvento(GUI_FICHA_2))
        {
            pulsado=true;
            fichaMover = GUI_FICHA_2;
        } else if(_motor->OcurreEvento(GUI_FICHA_3))
        {
            pulsado=true;
            fichaMover = GUI_FICHA_3;
        }

        if (pulsado)
        {
            // Obtenemos la zona seleccionada
            pilaInicial = getZonaVentana();

            // Comprobamos que la pila no este vacia
            if (!comprobarPilaVacia(pilaInicial)) {
                // Solo movemos la ficha si es la primera de la pila
                if (!comprobarTopPila(fichaMover))
                {
                    fichaMover = 0;
                    pilaInicial = NO_SELECT;
                    pulsado=false;
                }
            } else {
                fichaMover = 0;
                pilaInicial = NO_SELECT;
                pulsado=false;
            }
        } else {
            pilaInicial = NO_SELECT;
            pulsado=false;
        }
    }

    if ( ((float)_motor->GetPosicionRaton()[0] >= 0.0f && (float)_motor->GetPosicionRaton()[0] <= width) &&
         ((float)_motor->GetPosicionRaton()[1] >= 0.0f && (float)_motor->GetPosicionRaton()[1] <= height) &&
         (pulsado)
        )
    {
        _motor->CambiarPosicionImagen(fichaMover, _motor->GetPosicionRaton()[0]-25, _motor->GetPosicionRaton()[1]-20);
    }

    if ((!_motor->PulsadoClicIzq()) && (pulsado))
    {
        pulsado=false;
        deseleccionarNodo();
    }
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
    if (pasos <= solucion*2) 
    {
        // Comprobar fin de juego
        if (tam == opciones) 
        {
            if (pilaDer.top()->GetTamayo() == 1) 
            {
                ficha = pilaDer.top();
                pilaDer.pop();
                if (pilaDer.top()->GetTamayo() == 2) 
                {
                    _motor->BorrarGuiPuzzle(tipo, opciones);
                    Juego::GetInstance()->estado.ReanudarDesdePuzzle(true);
                }
                pilaDer.push(ficha);
            }
        }
    } 
    else 
    {
        _motor->BorrarGuiPuzzle(tipo, opciones);
        Juego::GetInstance()->estado.ReanudarDesdePuzzle(false);
    }
}

void EstadoPuzle::crearFichasPila()
{
    #ifdef WEMOTOR
        //codigo motor catopengl
        int img = 0;
        int posY_OpenGL = 300;
        for (int tam=opciones; tam>0; tam--) 
        {
            ficha = new PilaFichas(tam, iniXFichas, posY_OpenGL);
            img = _motor->CrearFichas(ficha->GetPosX(), posY_OpenGL, tam); //X, Y, tamanyo
            ficha->SetIMG(img);
            pilaIzq.push(ficha);
            posY_OpenGL-=25;
        }
        // Torres de prueba para poder centrarlas en la pantalla
        /*img = _motor->CrearFichas((CENTRO), 300, opciones);
        img = _motor->CrearFichas((DER), 300, opciones);*/
        /*img = _motor->CrearFichas((CENTRO+inc+25), 300-25, opciones-1);
        img = _motor->CrearFichas((DER+inc+25), 300-25, opciones-1);
        img = _motor->CrearFichas((CENTRO+inc+50), 300-50, opciones-2);
        img = _motor->CrearFichas((DER+inc+50), 300-50, opciones-2);*/
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
            if (pilaIzq.top()->GetIMG() == fichaY) {
                return true;
            }
        break;

        case CENTRO:
            if (pilaCentro.top()->GetIMG() == fichaY) {
                return true;
            }
        break;

        case DER:
            if (pilaDer.top()->GetIMG() == fichaY) {
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

PilaFichas* EstadoPuzle::recolocarFicha()
{
    if (pilaInicial == IZQ)
        return pilaIzq.top();
    else if (pilaInicial == CENTRO)
        return pilaCentro.top();
    else if (pilaInicial == DER)
        return pilaDer.top();
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

void EstadoPuzle::meterFicha()
{
    int y = 300;
    switch(pilaFinal)
    {
        case IZQ:
            if (!pilaIzq.empty()) {
                y = pilaIzq.top()->GetPosY()-25;
            }
            ficha->SetPosX(ficha->GetInc()+IZQ);
            ficha->SetPosY(y);
            pilaIzq.push(ficha);
            break;

        case CENTRO:
            if (!pilaCentro.empty()) {
                y = pilaCentro.top()->GetPosY()-25;
            }
            ficha->SetPosX(ficha->GetInc()+CENTRO+25);
            ficha->SetPosY(y);
            pilaCentro.push(ficha);
            break;

        case DER:
            if (!pilaDer.empty()) {
                y = pilaDer.top()->GetPosY()-25;
            }
            ficha->SetPosX(ficha->GetInc()+DER+50);
            ficha->SetPosY(y);
            pilaDer.push(ficha);
            break;
    }
    _motor->CambiarPosicionImagen(ficha->GetIMG(),
        ficha->GetPosX(), ficha->GetPosY());
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
    _motor->BorrarElemento(GUI_FICHA_1);
    _motor->BorrarElemento(GUI_FICHA_2);
    _motor->BorrarElemento(GUI_FICHA_3);
    crearFichasPila();
}

void EstadoPuzle::deseleccionarNodo()
{
    // No mueve la ficha de zona
    if (pilaInicial != NO_SELECT)
    {
        // Obtenemos la zona donde se suelta la ficha
        pilaFinal = getZonaVentana();

        if ((pilaInicial == pilaFinal) || // Misma zona
            (pilaFinal == NO_SELECT))     // Fuera de la ventana
        {
            ficha = recolocarFicha();
            _motor->CambiarPosicionImagen(ficha->GetIMG(),
                ficha->GetPosX(), ficha->GetPosY());
        }
        else // Distinta zona
        {
            if (comprobarTamanyo())
            {
                pasos++;
                sacarFicha();
                meterFicha();
                comprobarGanar();
            }
            else
            {
                ficha = recolocarFicha();
                _motor->CambiarPosicionImagen(ficha->GetIMG(),
                    ficha->GetPosX(), ficha->GetPosY());
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