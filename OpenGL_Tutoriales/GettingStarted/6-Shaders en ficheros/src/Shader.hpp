#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    public:
        //ID del programa shader
        unsigned int ID;

        //Constructor
        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
        ~Shader();

        //Activar/Desactivar shader
        void use();
        //Funciones uniforme
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
    private:
        void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
