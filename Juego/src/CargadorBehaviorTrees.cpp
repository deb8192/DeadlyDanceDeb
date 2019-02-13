#include "CargadorBehaviorTrees.hpp"
#include <sstream>



CargadorBehaviorTrees::CargadorBehaviorTrees()
{
    
}

CargadorBehaviorTrees::~CargadorBehaviorTrees()
{
    //delete raiz;
    //delete behavior_tree;
}

void CargadorBehaviorTrees::generarTarea(pugi::xml_node tool, const char ** atributos, int tarea, unsigned int i, int tipo)
{
    if((tool.first_child() != NULL) && (std::strcmp(tool.first_child().name(), PIZARRA) == 0))
    {
        atributos[i] = VERDADERO;
        i++;
        for (pugi::xml_attribute attr = tool.first_child().first_attribute(); attr; attr = attr.next_attribute())
        {
            atributos[i] = attr.value();
            i++;
        }

        if(std::strcmp(atributos[5], LEE) == 0)
        {
            tarea = 1;
        }
        else if(std::strcmp(atributos[5], ESCRIBE) == 0)
        {
            tarea = 2;
        }
    }
    else
    {
        atributos[i] = FALSO;
        i++;
        while(i < sizeof(atributos))
        {
            atributos[i] = "";
            i++;
        }
        tarea = 0;
    }
    tipo = 1;
}

Nodo* CargadorBehaviorTrees::anyadirHijo(Arbol *arbol, Nodo* padre, Nodo* nodo, int nivel)
{
    if(nodo != NULL)
    {
        padre = arbol->anyadirHijo(nodo);
    }
    return padre;
}

/*******************  Sacar nodo  *********************
 * Descripcion: Metodo que sirve par leer los nodos y
 * los atributos de un arbol en formato xml y almacernarlos
 * en una estructura arborea a modo de arbol de comportamiento
 * Entradas:
 *      tree: nodo del archivo xml
 *      *nodo: puntero hacia el nodo en que se guardara la info del nuevo nodo
 *      *padre: puntero hacia el nodo padre del nodo pasado por parametro  
 * Salidas:
 *      tree: nodo del archivo xml
 */
Arbol CargadorBehaviorTrees::CrearArbolComportamiento(vector<pugi::xml_node> tree, Nodo *nodo, Nodo *padre, int nivel) {
    unsigned int i = 0;
    const char** atributos = (const char**) malloc(8 * sizeof(const char*));
    int IDInt = 0;
    int tipo = 0;
    int tarea =0;
    Arbol *arbol;
    
    //Bucle para recorrer el arbol
    for (pugi::xml_node tool = tree.back().first_child(); tool; tool = tool.next_sibling())
    {
        while(tool != NULL)
        {
            if(std::strcmp(tool.name(), PIZARRA)  == 0)
            {
                tool = tool.next_sibling();
            }
            else 
            {
                nivel++;
            }
            i = 0;
            //Se recorren los atributos de cada nodo
            for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute())
            {
                atributos[i] = attr.value(); //devuelve los atributos como const char*;
                i++;
            }

            std::string s(atributos[0]);
            IDInt = std::stoi(s);
            
            //Se crea el arbol.
            if(std::strcmp(tool.name(), RAIZ) == 0)
            {
                //Se crea la raiz y el arbol
                if((std::strcmp(atributos[1], SELECTOR)  == 0) || (std::strcmp(atributos[1], SECUENCIA) == 0) || (std::strcmp(atributos[1], TAREA) == 0))
                {
                    if(std::strcmp(atributos[1], TAREA) == 0)
                    {
                        generarTarea(tool, atributos, tarea, i, tipo);
                    }
                    else
                    {
                        atributos[i] = FALSO;
                        i++;
                        while(i < sizeof(atributos))
                        {
                            atributos[i] = "";
                            i++;
                        }
                        tarea = 0;
                    }
                    if(std::strcmp(atributos[1], SECUENCIA) == 0)
                    {
                        tipo = 2;
                    }
                    else if(std::strcmp(atributos[1], SELECTOR) == 0)
                    {
                        tipo = 3;
                    }
                    

                    raiz = new Composicion(tool.name(), IDInt, tipo, nivel, padre, atributos[2], atributos[3], atributos[4], tarea, atributos[6], false);
                    padre = raiz;
                }
                else if((std::strcmp(atributos[1], SEL_ALEATORIO)  == 0) || (std::strcmp(atributos[1], SEC_ALEATORIA) == 0))
                {
                    if(std::strcmp(atributos[1], SEL_ALEATORIO)  == 0)
                    {
                        tipo = 4;
                    } 
                    else if(std::strcmp(atributos[1], SEC_ALEATORIA)  == 0)
                    {
                        tipo = 5;
                    }
                    raiz = new Composicion(tool.name(), IDInt, tipo, nivel, padre, NULL, NULL, NULL, 0, NULL, true);
                    padre = raiz;
                }
                arbol = new Arbol(raiz, raiz->getNombre());
            }
            //Se crean el resto de nodos del arbol
            else if(std::strcmp(tool.name(), COMPOSICION) == 0)
            {
                if((std::strcmp(atributos[1], SELECTOR)  == 0) || (std::strcmp(atributos[1], SECUENCIA) == 0) || (std::strcmp(atributos[1], TAREA) == 0))
                {
                    if(std::strcmp(atributos[1], TAREA) == 0)
                    {
                        generarTarea(tool, atributos, tarea, i, tipo);
                    }
                    else
                    {
                        atributos[i] = FALSO;
                        i++;
                        while(i < sizeof(atributos))
                        {
                            atributos[i] = "";
                            i++;
                        }
                        tarea = 0;
                    }
                    if(std::strcmp(atributos[1], SECUENCIA) == 0)
                    {
                        tipo = 2;
                    }
                    else if(std::strcmp(atributos[1], SELECTOR) == 0)
                    {
                        tipo = 3;
                    }
                    nodo = nullptr;
                    nodo = new Composicion(tool.name(), IDInt, tipo, nivel, padre, atributos[2], atributos[3], atributos[4], tarea, atributos[6], false);
            }
            else if((std::strcmp(atributos[1], SEL_ALEATORIO)  == 0) || (std::strcmp(atributos[1], SEC_ALEATORIA) == 0))
            {
                    if(std::strcmp(atributos[1], SEL_ALEATORIO)  == 0)
                    {
                        tipo = 4;
                    } 
                    else if(std::strcmp(atributos[1], SEC_ALEATORIA)  == 0)
                    {
                        tipo = 5;
                    }
                    nodo = nullptr;
                    nodo = new Composicion(tool.name(), IDInt, tipo, nivel, padre, "", "", "", 0, "", true);
            }
                
                //SEPARAR EN UNA FUNCION DISTINTA

                padre = CargadorBehaviorTrees::anyadirHijo(arbol, padre, nodo, nivel);            
                padre = nodo;
            }
            else if(std::strcmp(tool.name(), DECORADOR) == 0)
            {
                tipo = 6;
                nodo = nullptr;
                nodo = new Decorador(tool.name(), IDInt, tipo, nivel, padre, atributos[2], atributos[3]);

                //SEPARAR EN UNA FUNCION DISTINTA
                padre = CargadorBehaviorTrees::anyadirHijo(arbol, padre, nodo, nivel);
                padre = nodo;
            }
            else if(std::strcmp(tool.name(), HOJA) == 0)
            {
                
                generarTarea(tool, atributos, tarea, i, tipo);
                
                nodo = nullptr;
                nodo = new Hoja(tool.name(), IDInt, tipo, nivel, padre, atributos[2], atributos[3], atributos[4], tarea, atributos[6]);
                
                padre = CargadorBehaviorTrees::anyadirHijo(arbol, padre, nodo, nivel);
                padre = nodo;            
                
            }
            if(tool != NULL)
            {
                tree.push_back(tool);
                tool = tool.first_child();
            }
            //CrearArbolComportamiento(tool, nodo, padre, nivel);
        }
        while(tool.next_sibling() == NULL && !tree.empty())
        {
            nivel--;
            tool = tree.back();
            tree.pop_back();
            nodo = padre;
            if(nodo != nullptr)
            {
                padre = (Nodo*)nodo->getPadre();
            }
        }
    }
    return *arbol;
}

/*
******Cargador de arboles de comportamiento*******
 * Descripcion: Metodo que sirve par leer un xml de un
 * arbol de comportamiento y cargarlo en memoria
 * Entradas:
 *      tree: string con el nombre del arbol  
 * Salidas:
 *      behavior_tree: estructura que contiene un arbol de comportamiento
 */

Arbol CargadorBehaviorTrees::cargarBehaviorTreeXml(string nombre_arbol)
{
    int level = 0;
    Nodo *nodo = nullptr;
    Nodo *padre = nullptr;
    //definimos los strings
    string extension = ".xml";
    string ruta = "assets/trees/xml/";
    string ruta_completa = "";

    //Se crea la ruta completa hacia el arbol de comportamiento
    ruta_completa = ruta+nombre_arbol+extension;

    //Se transforma el string a un char array
    char cadena[sizeof(ruta_completa)];
    strcpy(cadena, ruta_completa.c_str()); 

    // Cargar el documento
    pugi::xml_document doc;
    //if (!doc.load_file(ruta_completa)) { // <- caca de linux q no lo acepta
    if (!doc.load_file(cadena)) {
    	cout<<"No existe el documento"<<"\n"<<endl;
	}
    else
    {
        cout<<"Hay documento"<<"\n"<<endl;
    }
    
    //Se pasa a la lectura del archivo .xml
    //Prueba de lectura de nodos
    vector<pugi::xml_node> tree;
    tree.push_back(doc.child("BehaviorTree"));
    return CrearArbolComportamiento(tree, nodo, padre, level);
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

Arbol2 * CargadorBehaviorTrees::cargarArbol(string nombre)
{
    //primero creamos el arbol
        Arbol2 * arbol = new Arbol2();
    //ahora creamos raiz
    
    //ahora nos recorremos las primeras hojas y llamamos recursivamente a agregarHoja si estas hojas tienen otras.
        //definimos los strings
        string extension = ".xml";
        string ruta = "assets/trees/xml/";
        string ruta_completa = "";

        //Se crea la ruta completa hacia el arbol de comportamiento
        ruta_completa = ruta+nombre+extension;

        //Se transforma el string a un char array
        char cadena[sizeof(ruta_completa)];
        strcpy(cadena, ruta_completa.c_str()); 

        // Cargar el documento
        pugi::xml_document doc;
        //if (!doc.load_file(ruta_completa)) { // <- caca de linux q no lo acepta
        if (!doc.load_file(cadena)) 
        {
            //cout<<"No existe el documento"<<"\n"<<endl;
        }
        else
        {
            pugi::xml_node tree = doc.child("BehaviorTree");
            agregarHoja(tree,arbol->getCabeza(),arbol);
        }
        //Se pasa a la lectura del archivo .xml
        //Prueba de lectura de nodos
        
    //cout << "Fin construccion arbol" << "\n" <<endl;
    //finalmente devolvemos el arbol
    return arbol;
}

void CargadorBehaviorTrees::agregarHoja(pugi::xml_node rutapadre,hoja2 * padre,Arbol2 * arb)
{
    //nos vamos a recorrer todas las hojas de este nivel 
    hoja2 * padre2;//lo utilizamos para no tener que crear otra funcion donde se crea la raiz
    if(arb != nullptr)
    {
        //esto significa que es la primera hoja por lo que es la raiz
        padre2 = arb->crearHoja();
        padre2->definirComportamientoHoja(0);//esto significa que es la raiz
        arb->setCabeza(padre2);
        //cout << "Creamos raiz" << "\n" <<endl;
    }
    else
    {
        //esto significa que el padre es la hoja que han pasado porque no es la raiz
        padre2 = padre;
        //cout << "no es raiz" << "\n" <<endl;
    }
    for (pugi::xml_node plat = rutapadre.child("hoja"); plat; plat = plat.next_sibling("hoja"))//esto nos devuelve todos los hijos que esten al nivel del anterior
    {
        //cout << "Creamos hoja" << "\n" <<endl;
        //creamos nueva hoja
        //cout << "agrego hijo" << "\n" <<endl;
        hoja2 * nueva = arb->crearHoja();
        //le damos valores
        nueva->setPadre(padre2);//agregamos a su padre sea raiz o la hoja pasado como parametro
        padre2->agregarHijo(nueva);//agregamos el hijo
        nueva->definirComportamientoHoja(plat.attribute("action").as_int());//nos devuelve un int
        if(plat.attribute("repetitivo").as_bool())//si es true agregara que es repetitiva la accion y cuantas repeticiones tiene
        {
            nueva->definirRepiticion(plat.attribute("repetitivo").as_bool());
            nueva->definirNumeroRepeticiones(plat.attribute("numeroRepeticiones").as_int());
        }
        agregarHoja(plat,nueva,nullptr);
        //final se pasa a la siguiente hoja si existe
    }
}