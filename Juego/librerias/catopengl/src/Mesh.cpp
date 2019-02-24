#include "Mesh.hpp"

//Constructor
Mesh::Mesh(vector<Vertex> vert, vector<unsigned int> indx, vector<Texture> text)
{
    vertices = vert;
    indices = indx;
    textures = text;
    setupMesh();
}

//Destructor
Mesh::~Mesh()
{

}

//Guardar Vertices de la Malla
void Mesh::setupMesh()
{
    //Crear buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Enlazar el objeto Vertex Array
    glBindVertexArray(VAO);

    //Cargar datos en los buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),&indices[0], GL_STATIC_DRAW);

    //Atributos de los Vertices
    //Atributo posicion
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    //Atributo normales
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    //Atributo texturas
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    //Cerrar el enlace
    glBindVertexArray(0);
}

//Renderizar la Malla
void Mesh::Draw(Shader* shader)
{
    //Enlazar las texturas apropiadas
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;

    //Solucion al problema del numero indeterminado de texturas que puede tener una malla (definirlas como "uniform sampler2D texture_diffuseN" donde N es el numero de textura)
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); //Activa la unidad de textura adecuada antes de vincular
        //recuperar el n�mero de textura (la N en diffuse_textureN)
        string number;
        string name = textures[i].type;
        if(name == "texture_diffuse")
        {
            //number = std::to_string(diffuseNr++); //transformar unsigned int a string
            stringstream ss; //Borrar cuando funcione tostring
            ss << diffuseNr++;
            number = ss.str();
        }
        else if(name == "texture_specular")
        {
            //number = std::to_string(specularNr++);
            stringstream ss; //Borrar cuando funcione tostring
            ss << specularNr++;
            number = ss.str();
        }
        else if(name == "texture_normal")
        {
            //number = std::to_string(normalNr++);
            stringstream ss; //Borrar cuando funcione tostring
            ss << normalNr++;
            number = ss.str();
        }
        else if(name == "texture_height")
        {
            //number = std::to_string(heightNr++);
            stringstream ss; //Borrar cuando funcione tostring
            ss << heightNr++;
            number = ss.str();
        }

        //Ahora ajuste el sampler a la unidad de textura correcta
        //glUniform1i(glGetUniformLocation(shader->ID, (name + number).c_str()), i);
        //Finalmente enlazamos la textura
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    //Dibujar malla
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    //Dejar en valor predeterminado antes de terminar
    glActiveTexture(GL_TEXTURE0);
}
