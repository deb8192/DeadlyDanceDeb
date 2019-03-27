#include "CargadorPuzzles.hpp"

CargadorPuzzles::CargadorPuzzles()
{

}

CargadorPuzzles::~CargadorPuzzles()
{
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
        	Puzzle* _puzzle = new Puzzle(tipoV, tool.child_value(
                "Descripcion"), opc, sol);

            if (tipoV == 1)
            {
                // Imagen con la imagen de ejemplo
                pugi::xml_node hijo = tool.child("Respuestas");
                _puzzle->AnyadirImgRespuesta(hijo.attribute("ejemplo").value());

                // Resto de imgs para las respuestas
                for (pugi::xml_node resp = hijo.first_child(); resp; resp = resp.next_sibling())
                {
                    _puzzle->AnyadirImgRespuesta(resp.attribute("img").value());
                }
            }
            
            _listaPuzzles.push_back(move(_puzzle));
            _puzzle = nullptr;
        }
    }
}

Puzzle* CargadorPuzzles::GetPuzzle(unsigned short pos) 
{
	return _listaPuzzles.at(pos);
}