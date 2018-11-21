#include "CargadorNiveles.hpp"
#include "Nivel.hpp"
#include "MotorGrafico.hpp"

CargadorNiveles::CargadorNiveles()
{

}

void CargadorNiveles::CargarNivelXml(int level)
{
    MotorGrafico * motor = MotorGrafico::getInstance();
    //definimos los strings
    std::string nivel = ""; //donde se almacenara el nombre del nivel   
    std::string extension = ".xml"; // extension del archivo a abrir
    std::string ruta = "assets/maps/xml/"; // ruta del archivo
    std::string ruta_completa = ""; // ruta del archivo
    //ahora pasamos el nivel a texto
    nivel = std::to_string(level);
    //creamos la ruta completa
    ruta_completa = ruta+nivel+extension;

    //esto transforma el string std 11 a char
    char cadena[sizeof(ruta_completa)];//le dice la longitud del char que sera igual a la longitud del string
    strcpy(cadena,ruta_completa.c_str()); //pasa el string a char
    //fin de la transformacion

    //ahora vamos a abrir el fichero en xml y crear una instancia de pugixml(libreria)

    pugi::xml_document doc;//instanciamos el objeto de la libreria xml
    doc.load_file(cadena);//cargamos el archivo

    for (pugi::xml_node hijo = doc.child("Level").child("Platform"); hijo; hijo = hijo.next_sibling("Platform"))//esto nos devuelve todos los hijos que esten al nivel del anterior
    {
        int x = hijo.attribute("X").as_int();//nos devuelve un int
        int y = hijo.attribute("Y").as_int();//nos devuelve un int
        int z = hijo.attribute("Z").as_int();//nos devuelve un int 
        const char * textura = hijo.attribute("Texture").value(); //nos da un char[] = string
        const char * modelo  =  hijo.attribute("Model").value(); //nos da un char[] = string
        motor->CargarPlataformas(x,y,z,modelo,textura); //cargamos el objeto

        //carga del jugador
        //if(estajugador){}

        for (pugi::xml_node enem = hijo.child("Enemy"); enem; enem = enem.next_sibling("Enemy"))//esto nos devuelve todos los hijos que esten al nivel del anterior
        {
            //aqui va la carga de enemigos
            //motor->CargarEnemigos(x,y,z,modelo,textura); //cargamos el enemigo
        }

        for (pugi::xml_node obj = hijo.child("Object"); obj; obj = obj.next_sibling("Object"))//esto nos devuelve todos los hijos que esten al nivel del anterior
        {
            //aqui va la carga de objetos
            //motor->CargarObjetos(x,y,z,modelo,textura); //cargamos el enemigo
        }
    }

    for (pugi::xml_node hijo = doc.child("Level").child("Light"); hijo; hijo = hijo.next_sibling("Light"))//esto nos devuelve todos los hijos que esten al nivel del anterior
    {
        int x = hijo.attribute("X").as_int();//nos devuelve un int
        int z = hijo.attribute("Y").as_int();//nos devuelve un int
        int y = hijo.attribute("Z").as_int();//nos devuelve un int 
        motor->CargarLuces(x,y,z); //cargamos el objeto
    }


}

void CargadorNiveles::GuardarNivelXml(int level)
{
    //definimos los strings
    std::string nivel = ""; //donde se almacenara el nombre del nivel   
    std::string extension = ".xml"; // extension del archivo a abrir
    std::string ruta = "assets/maps/xml/"; // ruta del archivo
    std::string ruta_completa = ""; // ruta del archivo
    //ahora pasamos el nivel a texto
    nivel = std::to_string(level);
    //creamos la ruta completa
    ruta_completa = ruta+nivel+extension;

    //esto transforma el string std 11 a char
    char cadena[sizeof(ruta_completa)];//le dice la longitud del char que sera igual a la longitud del string
    strcpy(cadena,ruta_completa.c_str()); //pasa el string a char
    //fin de la transformacion

    //vamos a llamar a los datos desde nivel para almacenarlos en formato xml

}

void CargadorNiveles::CargarNivelBin(int level)
{
    //definimos los strings
    std::string nivel = ""; //donde se almacenara el nombre del nivel   
    std::string extension = ".bin"; // extension del archivo a abrir
    std::string ruta = "assets/maps/bin/"; // ruta del archivo
    std::string ruta_completa = ""; // ruta del archivo
    //ahora pasamos el nivel a texto
    nivel = std::to_string(level);
    //creamos la ruta completa
    ruta_completa = ruta+nivel+extension; 

    //esto transforma el string std 11 a char
    char cadena[sizeof(ruta_completa)];//le dice la longitud del char que sera igual a la longitud del string
    strcpy(cadena,ruta_completa.c_str()); //pasa el string a char
    //fin de la transformacion

    //cargamos el archivo binario para cargar el nivel en la clase nivel
}

void CargadorNiveles::GuardarNivelBin(int level)
{
    //definimos los strings
    std::string nivel = ""; //donde se almacenara el nombre del nivel   
    std::string extension = ".bin"; // extension del archivo a abrir
    std::string ruta = "assets/maps/bin/"; // ruta del archivo
    std::string ruta_completa = ""; // ruta del archivo
    //ahora pasamos el nivel a texto
    nivel = std::to_string(level);
    //creamos la ruta completa
    ruta_completa = ruta+nivel+extension; 

    //esto transforma el string std 11 a char
    char cadena[sizeof(ruta_completa)];//le dice la longitud del char que sera igual a la longitud del string
    strcpy(cadena,ruta_completa.c_str()); //pasa el string a char
    //fin de la transformacion

    //llamamos a las datos desde nivel para almacenarlos en formato binario 
}
