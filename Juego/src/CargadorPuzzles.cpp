#include "CargadorPuzzles.hpp"

CargadorPuzzles::CargadorPuzzles()
{

}

CargadorPuzzles::~CargadorPuzzles()
{
    _fondo = nullptr;

    short tam = _listaPuzzles.size();
    for(short i=0; i < tam; i++)
    {
        delete _listaPuzzles.at(i);
    }
    _listaPuzzles.clear();
}

/*******Cargador de puzzles*******
 * Descripcion: Metodo que sirve par leer un xml con
 * todos los tipos de puzzles y cargarlo en memoria
 */
void CargadorPuzzles::CargarPuzzlesXml()
{
	stringstream buffer;
	short tipoV;
	short opc;
	short sol;
	std::string enun;

    //definimos los strings
    string ruta = "assets/puzzles/preguntas.xml";

    //Se transforma el string a un char array
    char cadena[sizeof(ruta)];
    strcpy(cadena, ruta.c_str()); 

    // Cargar el documento
    pugi::xml_document doc;
    if (!doc.load_file(cadena)) {
    	cout<<"No existe el documento"<<"\n"<<endl;
	}

    //Se pasa a la lectura del archivo .xml
    pugi::xml_node puzzles = doc.child("Puzzles");

    _fondo = puzzles.attribute("Fondo").value();

    // Comprbamos si tiene puzzles
    if(puzzles == NULL) {
        cout << "No hijos" << "\n" <<endl;
    } else {
        for (pugi::xml_node tool = puzzles.first_child(); tool; tool = tool.next_sibling())
        {
        	// Convertir los datos del buffer a short
        	buffer << tool.attribute("tipo").value();
        	buffer >> tipoV;
        	buffer.clear();

        	buffer << tool.attribute("opciones").value();
        	buffer >> opc;
        	buffer.clear();

        	buffer << tool.attribute("solucion").value();
        	buffer >> sol;
        	buffer.clear();

        	// Crear el puzzle y anyadirlo a la lista
        	Puzzle* _puzzle = new Puzzle(tipoV, tool.child_value("Descripcion"), opc, sol);

            for (pugi::xml_node hijo = tool.first_child(); hijo; hijo = hijo.next_sibling())
            {
                if(std::strcmp(hijo.name(), "Respuestas") == 0)
                {
                    for (pugi::xml_node resp = hijo.first_child(); resp; resp = resp.next_sibling())
                    {
                        _puzzle->AnyadirImgRespuesta(resp.attribute("img").value());
                    }
                }
            }
            _listaPuzzles.push_back(move(_puzzle));
            _puzzle = nullptr;
        }
    }

    // Pruebas en consola
    /*for (int a=0; a<listaPuzzles.size(); a++) {
    	cout << "Tipo: " << listaPuzzles.at(a).GetTipo() <<endl;
    	cout << "Acertijo: " << listaPuzzles.at(a).GetEnunciado() <<endl;
    	cout << "Opciones: " << listaPuzzles.at(a).GetOpciones() <<endl;
    }
    cout << "FIN" << "\n" <<endl;*/
}

Puzzle* CargadorPuzzles::GetPuzzle(unsigned short pos) 
{
	return _listaPuzzles.at(pos);
}

const char* CargadorPuzzles::GetFondo()
{
    return _fondo;
}