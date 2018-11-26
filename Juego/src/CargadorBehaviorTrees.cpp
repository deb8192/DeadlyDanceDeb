#include "CargadorBehaviorTrees.hpp"
#include <sstream>



CargadorBehaviorTrees::CargadorBehaviorTrees()
{

}

/* Función recursiva para acceder a todos los nodos */
pugi::xml_node CargadorBehaviorTrees::sacarNodo(pugi::xml_node tree, Nodo *nodo, Nodo *padre) {
    int i = 0;
    const char* atributos[8];
    stringstream ID;
    stringstream tipo;
    stringstream tarea;
    int IDInt;
    int tipoInt;
    int tareaInt;

    //Caso base
    if(tree == NULL) {
        cout << "No hijos" << "\n" <<endl;
        return tree;
    }
    //Algoritmo recursivo
    else {
        //Bucle para recorrer el arbol
        for (pugi::xml_node tool = tree.first_child(); tool; tool = tool.next_sibling())
        {
            i = 0;
            //Se recorren los atributos de cada nodo
            for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute())
            {
                atributos[i] = attr.value(); //devuelve los atributos como const char*
                cout << " " << attr.name() << "=" << atributos[i];
                i++;
            }
            cout<<endl;
            //Se crea y actualizan los nodos del arbol.
            if(std::strcmp(tool.name(), "root") == 0)
            {
                //Se crea la raiz y el arbol
               if((std::strcmp(atributos[1], SELECTOR)  == 0) || (std::strcmp(atributos[1], SECUENCIA) == 0))
               {
                    ID << atributos[0];
                    tipo << atributos[1];
                    ID >> IDInt;
                    tipo >> tipoInt;
                    nodo = new Composicion(IDInt, tipoInt, NULL);
                    padre = nodo;
                    behavior_tree = new Arbol(nodo, tool.name());
               }
            }
            //Se crean el resto de nodos del arbol
            else
            {
                if(std::strcmp(tool.name(), "Composition") == 0)
                {
                    ID << atributos[0];
                    tipo << atributos[1];
                    ID >> IDInt;
                    tipo >> tipoInt;
                    nodo = new Composicion(IDInt, tipoInt, padre);
                    //padre->addHijo(nodo);
                    padre = nodo;
                }
                else if(std::strcmp(tool.name(), "Decorator") == 0)
                {
                    ID << atributos[0];
                    tipo << atributos[1];
                    ID >> IDInt;
                    tipo >> tipoInt;
                    nodo = new Decorador(IDInt, tipoInt, padre, atributos[2], atributos[3]);
                    //padre->addHijo(nodo);
                    padre = nodo;
                }
                else if(std::strcmp(tool.name(), "Leaf") == 0)
                {
                    if((tool.first_child() != NULL) && (std::strcmp(tool.first_child().name(), "Blackboard") == 0))
                    {
                        cout<<"Pizarra?"<<endl;
                        atributos[i] = "true";
                        i++;
                        for (pugi::xml_attribute attr = tool.first_child().first_attribute(); attr; attr = attr.next_attribute())
                        {
                            atributos[i] = attr.value();
                            cout << " " << attr.name() << "=" << atributos[i];
                            i++;
                        }
                        ID << atributos[0];
                        tipo << atributos[1];
                        tarea << atributos[5];
                        ID >> IDInt;
                        tipo >> tipoInt;
                        tarea >> tareaInt;
                        nodo = new Hoja(IDInt, tipoInt, padre, atributos[2], atributos[3], atributos[4], tareaInt, atributos[6]);
                        //padre->addHijo(nodo);
                    }
                }
            }
            sacarNodo(tool, nodo, padre);
            cout<< "sale"<<endl;
        }
    }
}
/*******Cargador de arboles de comportamiento*******
 * Descripcion: Metodo que sirve par leer un xml de un
 * arbol de comportamiento y cargarlo en memoria
 * Entradas:
 *      tree: string con el nombre del arbol  
 */
void CargadorBehaviorTrees::cargarBehaviorTreeXml(string nombre_arbol)
{
    Nodo *nodo;
    Nodo *padre;
    //definimos los strings
    string extension = ".xml";
    string ruta = "assets/trees/xml/";
    string ruta_completa = "";

    //Se crea la ruta completa hacia el arbol de comportamiento
    ruta_completa = ruta+nombre_arbol+extension;
    cout<<ruta_completa<<endl;  

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

    sacarNodo(tree, nodo, padre);
    cout << "FIN" << "\n" <<endl;
    
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