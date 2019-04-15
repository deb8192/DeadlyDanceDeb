#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <glm.hpp>

namespace CatOpengl
{
    class Gestor;
    //apartado dedicado a inicializar las opciones de la grafica como puede ser las ventanas
    namespace Video
    {
        class Ventana;
    };
    //apartado dedicado a elementos interactivos como pueden ser botones, imagenes, hud.
    namespace Gui
    {
        
    };
    //apartado a la scena 3d del motor, sirve para crear/borrar objetos asi como para moverlos
    namespace Scena
    {
        //cuando se quiere pasar algo a opengl se llama al gestor
        //class Gestor;
        //crea objetos con array de vertices [puede crear formas como un triangulo un rectangulo, cajas, etc..]
        class FormaPrimitiva;
    };
    //apartado dedicado al gestor de shaders (crear, cargar, vincular)
    namespace Shaders
    {
        //class Shader;
    };
}

using CatOpengl::Video::Ventana;

#include "Ventana.hpp"

//using CatOpengl::Shaders::Shader;

//#include "Shader.hpp" 

using CatOpengl::Scena::FormaPrimitiva;

#include "FormaPrimitiva.hpp"

using CatOpengl::Gestor;

#include "Gestor.hpp"