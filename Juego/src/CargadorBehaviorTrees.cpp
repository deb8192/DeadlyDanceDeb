#include "CargadorBehaviorTrees.hpp"



CargadorBehaviorTrees::CargadorBehaviorTrees()
{

}

/* Función recursiva para acceder a todos los nodos */
pugi::xml_node CargadorBehaviorTrees::sacarNodo(pugi::xml_node tree, Nodo *nodo, Nodo *padre) {
    int i = 0;
    const char* atributos[8];

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
                i++;
                cout << " " << attr.name() << "=" << attr.value();
            }
            
            cout<<" Sigue"<<endl;

            //Se crea y actualizan los nodos del arbol.
            if(std::strcmp(tool.name(), "root") == 0)
            {
                //Se crea la raiz y el arbol
               if((std::strcmp(atributos[1], SELECTOR)  == 0) || (std::strcmp(atributos[1], SECUENCIA) == 0))
               {
                    nodo = new Composicion(3, 1, NULL);
                    padre = nodo;
                    behavior_tree = new Arbol(nodo, tool.name());
               }
            }
            //Se crean el resto de nodos del arbol
            else
            {
                if(std::strcmp(tool.name(), "Composition") == 0)
                {
                    nodo = new Composicion(3, 1, padre);
                    //padre->addHijo(nodo);
                    padre = nodo;
                }
                else if(std::strcmp(tool.name(), "Decorator") == 0)
                {
                    nodo = new Decorador(3, 5, padre, atributos[2], atributos[3]);
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
                            i++;
                            cout << " " << attr.name() << "=" << attr.value();
                        }
                        nodo = new Hoja(3, 6, padre, atributos[2], atributos[3], atributos[4], 3, atributos[6]);
                        //padre->addHijo(nodo);
                    }
                }
            }
            sacarNodo(tool, nodo, padre);
            cout<<"sale"<<endl;
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