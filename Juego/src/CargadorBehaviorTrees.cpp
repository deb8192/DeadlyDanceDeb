#include "CargadorBehaviorTrees.hpp"
using namespace std;
//#include "MotorGrafico.hpp"

/* Función recursiva para acceder a todos los nodos */
pugi::xml_node CargadorBehaviorTrees::sacarNodo(pugi::xml_node nodo, int nivel) {
    nivel++;
    if(nodo == NULL) {
        cout << "No hijos" << "\n" <<endl;
        return nodo;
    }
    else {
        for (pugi::xml_node tool = nodo.first_child(); tool; tool = tool.next_sibling())
        {
            cout << tool.name();

            for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute())
            {
                cout << " " << attr.name() << "=" << attr.value();
            }
            cout << "nivel = " << nivel << "\n" <<endl;
            sacarNodo(tool, nivel);
        }
    }
    nivel--;
}

void CargadorBehaviorTrees::cargadorBehaviorTrees()
{

}
/*******Cargador de arboles de comportamiento*******
 * Descripcion: Metodo que sirve par leer un xml de un
 * arbol de comportamiento y cargarlo en memoria
 * Entradas:
 *      tree: string con el nombre del arbol  
 */
void CargadorBehaviorTrees::cargarBehaviorTreeXml(string arbol)
{
    //definimos los strings
    string extension = ".xml";
    string ruta = "assets/trees/xml/";
    string ruta_completa = "";

    //Se crea la ruta completa hacia el arbol de comportamiento
    ruta_completa = ruta+arbol+extension;
    cout<<ruta_completa<<endl;  
    
    int nivel = 0;

    //Se transforma el string a un char array
    char cadena[sizeof(ruta_completa)];
    strcpy(cadena, ruta_completa.c_str()); 

    // Cargar el documento
    pugi::xml_document doc;
    //if (!doc.load_file(ruta_completa)) { // <- caca de linux q no lo acepta
    if (!doc.load_file(cadena)) {
    	cout<<"No existe el documento"<<"\n"<<endl;
	}
    cout<<"Hay documento"<<"\n"<<endl;

    //Se pasa a la lectura del archivo .xml
    //Prueba de lectura de nodos
    pugi::xml_node tree = doc.child("BehaviorTree");

    sacarNodo(tree, nivel);
    cout << "FIN" << "\n" <<endl;

    /*string nombre = raiz.name();
    //string selector = "selector";
    int id = raiz.attribute("id").as_int();
    int tipo;
    string accion;
    string objetivo;
    bool pizarra;
    int tarea;
    string info;
    if(SELECTOR == (raiz.attribute("type").as_string()))
    {
        tipo = 2;
        accion = "";
        objetivo = "";
        pizarra = false;
        tarea = 0;
        info = "";
    }
    nodo = new Nodo(nombre, id, tipo, accion, objetivo, pizarra, tarea, info);
    cout<<"El nodo raiz tiene el nombre " << nodo->getNombre() << " el id "<< nodo->getId() <<" y es del tipo "<< nodo->getTipo() <<""<<endl;
    */
    
}

void CargadorBehaviorTrees::guardarBehaviorTreeXml(string arbol)
{
    //definimos los strings
    string extension = ".xml";
    string ruta = "src/ArbolesComportamiento/";
    string ruta_completa = "";

    //Se crea la ruta completa hacia el arbol de comportamiento
    ruta_completa = ruta+arbol+extension;

    //Se transforma el string a un char array
    char cadena[sizeof(ruta_completa)];
    strcpy(cadena, ruta_completa.c_str()); 
}