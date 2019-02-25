#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    public:

        //Constructor
        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
        //Shader(char const *, char const *);
        ~Shader();

        //Activar/Desactivar shader
        void Use();

        //Funciones uniforme
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
        //ID del programa shader
        unsigned int ID;
    private:

        void checkCompileErrors(unsigned int shader, std::string type);


};

#endif
