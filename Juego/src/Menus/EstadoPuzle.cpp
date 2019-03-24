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
    }
    else
    {
        // HANNOI
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
    /*MotorGrafico *motor = MotorGrafico::getInstance();
    motor->updateMotorPuzzles(GetTipo());

    // Boton atras, vuelve al menu
    if(motor->ocurreEvento(GUI_ID_ATRAS_BUTTON))
    {
        // Se resetea en el Update de Juego
        //resetEvento(GUI_ID_ATRAS_BUTTON);

        // Borrar pila y vectores

        // Borrar escena y GUI de puzzles
        motor->borrarScena();
        motor->borrarGui();

        // Cargar GUI de menu
        motor->PintarBotonesMenu();
        return;
    }

    // Comprobar eventos, depende del tipo de puzzle
    switch(GetTipo())
    {
        case P_OPCIONES:
            ComprobarEventosOpciones();
            break;
        case P_HANOI:
            ComprobarEventosHanoi();
            break;
    }*/
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
}

// Vuelve al juego
void EstadoPuzle::atras()
{
    _motor->BorrarGuiPuzzle(tipo, opciones);
    Juego::GetInstance()->estado.QuitarPausa();
}

/*short Puzzles::GetTipo()
{
    return puzzle.GetTipo();
}

std::string Puzzles::GetEnunciado()
{
    return puzzle.GetEnunciado();
}

short Puzzles::GetOpciones()
{
    return puzzle.GetOpciones();
}

short Puzzles::GetSolucion()
{
    return puzzle.GetSolucion();
}

void Puzzles::Iniciar()
{
    MotorGrafico *motor = MotorGrafico::getInstance();

    // Monta la interfaz dependiendo del tipo de puzzle
    motor->PuzzlesGui(GetTipo(), GetEnunciado(), GetOpciones());

    if (GetTipo() == P_HANOI)
    {
        pasos = 0;
        pilaInicial = NO_SELECT; // Para colocar las fichas en pilaIzq
        pilaFinal = NO_SELECT;

        // Rellenamos la pilaIzq
        CrearFichasPila();
        motor->TextoPasos(pasos);
    }
}

void Puzzles::CrearFichasPila()
{
    MotorGrafico *motor = MotorGrafico::getInstance();
    short posY = 0;
    for (int tam=GetOpciones(); tam>0; tam--) {

        short r = rand() % (256 + 100); // +100 para que no salga blanco
        short g = rand() % (256 + 0);
        short b = rand() % (256 + 0);
        motor->CrearFichas(posY, tam, r, g, b);

        ficha = new PilaFichas(tam, posY);
        pilaIzq.push(ficha);
        posY++;
    }
}

void Puzzles::ComprobarEventosOpciones()
{
    MotorGrafico *motor = MotorGrafico::getInstance();
    short opcion = 0;
    bool evento = false;

    if(motor->ocurreEvento(GUI_ID_OP1))// Boton A
    {
        motor->resetEvento(GUI_ID_OP1);
        opcion = 1;
        evento = true;
    }
    if(motor->ocurreEvento(GUI_ID_OP2))// Boton B
    {
        motor->resetEvento(GUI_ID_OP2);
        opcion = 2;
        evento = true;
    }
    if(motor->ocurreEvento(GUI_ID_OP3))// Boton C
    {
        motor->resetEvento(GUI_ID_OP3);
        opcion = 3;
        evento = true;
    }
    if(motor->ocurreEvento(GUI_ID_OP4))// Boton D
    {
        motor->resetEvento(GUI_ID_OP4);
        opcion = 4;
        evento = true;
    }

    if (evento) {
        if (opcion == GetSolucion()) {
            cout << "Correcto" <<endl;
        } else {
            cout << "Has fallado" <<endl;
        }
    }
}

void Puzzles::ComprobarEventosHanoi()
{
    MotorGrafico *motor = MotorGrafico::getInstance();

    if(motor->ocurreEvento(GUI_ID_REINICIAR_HANOI))
    {
        motor->resetEvento(GUI_ID_REINICIAR_HANOI);
        if (pasos > 0) {
            // Reiniciamos posiciones mallas fichas
            motor->ReiniciarHanoi();
            ReiniciarPilas();
        }
    }

    if((motor->PulsadoClicIzq()) && (!motor->estaPulsado(MOUSE_MOVED)))
    {
        //cout<<"Pulso solo"<<endl;
        pulsado=true;
        if (motor->SeleccionarNodo()) {
            //cout << "Objeto"<<endl;

            // Obtenemos la zona seleccionada
            pilaInicial = motor->GetZonaVentana();

            // Comprobamos que la pila no este vacia
            if (!ComprobarPilaVacia(pilaInicial)) {
                // Solo movemos la ficha si es la primera de la pila
                if (!ComprobarTopPila(motor->GetFichaY()))
                {
                    motor->DeseleccionarNodo();
                    pilaInicial = NO_SELECT;
                }
            } else {
                //cout << "Pila vacia"<<endl;
                motor->DeseleccionarNodo();
                pilaInicial = NO_SELECT;
            }

        } else {
            //cout << "Fondo"<<endl;
            pilaInicial = NO_SELECT;
        }
    }

    if((motor->PulsadoClicIzq()) && (motor->estaPulsado(MOUSE_MOVED))) {
        //cout<<"X: "<<motor->GetPosicionRaton().X<<" Y: "<<motor->GetPosicionRaton().Y<<endl;
        //cout<<"Arrastrar"<<endl;
        motor->MoverFichas(pilaInicial);
    }

    if ((motor->SueltoClicIzq()) && (pulsado))
    {
        //cout<<"Soltar"<<endl;
        pulsado=false;
        DeseleccionarNodo();
        motor->resetEventoMoveRaton();
    }
    motor->TextoPasos(pasos);
}

void Puzzles::DeseleccionarNodo()
{
    MotorGrafico *motor = MotorGrafico::getInstance();
    // No mueve la ficha de zona
    if (pilaInicial != NO_SELECT)
    {
        // Obtenemos la zona donde se suelta la ficha
        pilaFinal = motor->GetZonaVentana();

        if (pilaInicial == pilaFinal)           // Misma zona
        {
            motor->RecolocarFicha(RecolocarFicha(), pilaInicial);
        } else {                            // Distinta zona

            if (ComprobarTamanyo()) {
                pasos++;
                SacarFicha();
                motor->RecolocarFicha(MeterFicha(), pilaFinal);
                ComprobarGanar();

            } else {
                motor->RecolocarFicha(RecolocarFicha(), pilaInicial);
            }
        }
    }

    // Reiniciamos valores
    pilaInicial = NO_SELECT;
    pilaFinal = NO_SELECT;
}

bool Puzzles::ComprobarPilaVacia(short pila)
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

bool Puzzles::ComprobarTopPila(short fichaY)
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
bool Puzzles::ComprobarTamanyo()
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

short Puzzles::RecolocarFicha()
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

void Puzzles::SacarFicha()
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

short Puzzles::MeterFicha()
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

void Puzzles::ReiniciarPilas()
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

void Puzzles::ComprobarGanar()
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