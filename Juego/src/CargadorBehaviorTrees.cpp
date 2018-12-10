#include "CargadorBehaviorTrees.hpp"
#include <sstream>



CargadorBehaviorTrees::CargadorBehaviorTrees()
{

}

void CargadorBehaviorTrees::generarTarea(pugi::xml_node tool, const char ** atributos, int tarea, unsigned int i, int tipo)
{
    if((tool.first_child() != NULL) && (std::strcmp(tool.first_child().name(), PIZARRA) == 0))
    {
        cout<<"Pizarra?"<<endl;
        atributos[i] = VERDADERO;
        i++;
        for (pugi::xml_attribute attr = tool.first_child().first_attribute(); attr; attr = attr.next_attribute())
        {
            atributos[i] = attr.value();
            cout << " " << attr.name() << "=" << atributos[i];
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
        cout<<"No Pizarra"<<endl;
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
pugi::xml_node CargadorBehaviorTrees::sacarNodo(pugi::xml_node tree, Nodo *nodo, Nodo *padre, int nivel) {
    unsigned int i = 0;
    const char** atributos = (const char**) malloc(8 * sizeof(const char*));
    int IDInt = 0;
    int tipo = 0;
    int tarea =0;
    

    //Caso base
    if(tree == NULL || (nodo != NULL && strcmp(nodo->getNombre(), HOJA) == 0)) {
        cout << "No hijos" << "\n" <<endl;
        return tree;
    }
    //Algoritmo recursivo
    else 
    {
        //Bucle para recorrer el arbol
        for (pugi::xml_node tool = tree.first_child(); tool; tool = tool.next_sibling())
        {
            if(std::strcmp(tool.name(), PIZARRA)  == 0)
            {
                tool = tool.next_sibling();
            }
            free(atributos);
            nivel++;
            i = 0;
            //Se recorren los atributos de cada nodo
            for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute())
            {
                atributos[i] = attr.value(); //devuelve los atributos como const char*
                cout << " " << attr.name() << "=" << atributos[i];
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
                    

                    nodo = nullptr;
                    nodo = new Composicion(tool.name(), IDInt, tipo, nivel, padre, atributos[2], atributos[3], atributos[4], tarea, atributos[6], false);

                    padre = nodo;
                    raiz = nodo;
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
                    nodo = new Composicion(tool.name(), IDInt, tipo, nivel, padre, NULL, NULL, NULL, 0, NULL, true);
                    padre = nodo;
                    raiz = nodo;
               }
                behavior_tree = new Arbol(raiz, raiz->getNombre());
               //Faltaria comprobar otro tipo de nodos raiz pero principalmente seran secuencias o selectores
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

                padre = CargadorBehaviorTrees::anyadirHijo(behavior_tree, padre, nodo, nivel);
                
                padre = nodo;
            }
            else if(std::strcmp(tool.name(), DECORADOR) == 0)
            {
                tipo = 6;
                nodo = nullptr;
                nodo = new Decorador(tool.name(), IDInt, tipo, nivel, padre, atributos[2], atributos[3]);

                //SEPARAR EN UNA FUNCION DISTINTA
                padre = CargadorBehaviorTrees::anyadirHijo(behavior_tree, padre, nodo, nivel);
                padre = nodo;
            }
            else if(std::strcmp(tool.name(), HOJA) == 0)
            {
                
                generarTarea(tool, atributos, tarea, i, tipo);
                
                nodo = nullptr;
                nodo = new Hoja(tool.name(), IDInt, tipo, nivel, padre, atributos[2], atributos[3], atributos[4], tarea, atributos[6]);
                
                padre = CargadorBehaviorTrees::anyadirHijo(behavior_tree, padre, nodo, nivel);
                
                 
            }
            sacarNodo(tool, nodo, padre, nivel);
            
            nivel--;
            
            padre = (Nodo*)nodo->getPadre();
        }
    }
}
/*******Cargador de arboles de comportamiento*******
 * Descripcion: Metodo que sirve par leer un xml de un
 * arbol de comportamiento y cargarlo en memoria
 * Entradas:
 *      tree: string con el nombre del arbol  
 * Salidas:
 *      behavior_tree: estructura que contiene un arbol de comportamiento
 */
Arbol* CargadorBehaviorTrees::cargarBehaviorTreeXml(string nombre_arbol)
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

    sacarNodo(tree, nodo, padre, level);
    cout << "FIN" << "\n" <<endl;
    return behavior_tree;
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