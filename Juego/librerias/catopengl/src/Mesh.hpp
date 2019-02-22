#ifndef MESH_HPP
#define MESH_HPP

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Shader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

//Estructura de Vertice
struct Vertex {
    glm::vec3 Position;   //Posicion
    glm::vec3 Normal;     //Normal
    glm::vec2 TexCoords;  //Coordenadas de textura
};

//Estructura de Textura
struct Texture {
    unsigned int id;        //ID
    std::string type;       //Tipo (difusa,especular)
    std::string path;       //Ruta de textura
};

class Mesh
{
    public:
        //Constructor y destructor
        Mesh(vector<Vertex> vert, vector<unsigned int> indx, vector<Texture> text);
        ~Mesh();

        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;

    private:
        unsigned int VAO, VBO, EBO; //Datos de render
        void setupMesh();           //Guardar malla
};

#endif
