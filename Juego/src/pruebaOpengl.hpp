#include "GL/glew.h"
#include "glfw3.h"

#include <iostream>

#ifndef pruebaOpengl_HPP
#define pruebaOpengl_HPP

class pruebaOpengl
{
    public:
        pruebaOpengl();
        void crearVentana();
        void processInput(GLFWwindow*);
        void framebuffer_size_callback(GLFWwindow*, int,int);
    private:
        const unsigned int SCR_WIDTH = 800;
        const unsigned int SCR_HEIGHT = 600;        

};

#endif