#include "CargadorNiveles.hpp"
#include "Nivel.hpp"

CargadorNiveles::CargadorNiveles()
{

}

void CargadorNiveles::CargarNivelXml(int level)
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

    //ahora vamos a abrir el fichero en xml y crear una instancia de pugixml(libreria)

    pugi::xml_document doc;//instanciamos el objeto de la libreria xml
    pugi::xml_parse_result resultado = doc.load_file(cadena);//cargamos el archivo

    std::cout << "Load result: " << resultado.description() << ", La textura de la primera plataforma se encuenta en: " << doc.child("Level").child("Platform").attribute("Texture").value()<< std::endl;


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
