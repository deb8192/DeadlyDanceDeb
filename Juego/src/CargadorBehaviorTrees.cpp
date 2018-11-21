#include "CargadorBehaviorTrees.hpp"
//#include "MotorGrafico.hpp"

void CargadorBehaviorTrees::cargadorBehaviorTrees()
{

}
/*******Cargador de arboles de comportamiento*******
 * Descripcion: Metodo que sirve par leer un xml de un
 * arbol de comportamiento y cargarlo en memoria
 * Entradas:
 *      tree: string con el nombre del arbol  
 */
void CargadorBehaviorTrees::cargarBehaviorTreeXml(std::string tree)
{
    //definimos los strings
    std::string arbol = "";
    std::string extension = ".xml";
    std::string ruta = "assets/trees/xml/";
    std::string ruta_completa = "";

    //Se pasa el nombre del arbol a texto
    arbol = tree;

    //Se crea la ruta completa hacia el arbol de comportamiento
    ruta_completa = ruta+arbol+extension;
    std::cout<<ruta_completa<<std::endl;  
    
    //Se transforma el string a un char array
    char cadena[sizeof(ruta_completa)];
    strcpy(cadena, ruta_completa.c_str()); 

    pugi::xml_document doc;
    doc.load_file(cadena);

    if(doc != NULL)
        std::cout<<"Hay documento"<<std::endl;

    //Se pasa a la lectura del archivo .xml
    //Prueba de lectura de nodos
    pugi::xml_node raiz = doc.child("BehaviorTree").child("Root");
    int id = raiz.attribute("id").as_int();
    std::string tipo = raiz.attribute("type").as_string();

    std::cout<<"El nodo raiz tiene el id "<< id <<" y es del tipo "<< tipo <<""<<std::endl;
    //for(pugi::xml_node hijo = doc.child("Composition"))
    
}

void CargadorBehaviorTrees::guardarBehaviorTreeXml(std::string tree)
{
    //definimos los strings
    std::string arbol = "";
    std::string extension = ".xml";
    std::string ruta = "src/ArbolesComportamiento/";
    std::string ruta_completa = "";

    //Se pasa el nombre del arbol a texto
    arbol = tree;

    //Se crea la ruta completa hacia el arbol de comportamiento
    ruta_completa = ruta+arbol+extension;

    //Se transforma el string a un char array
    char cadena[sizeof(ruta_completa)];
    strcpy(cadena, ruta_completa.c_str()); 
}