#include "TBillboard.hpp"

// Constructor y destructor
TBillboard::TBillboard(GLfloat x, GLfloat y, GLfloat z, const char * _ruta, Shader * sact, GLfloat movx, GLfloat movy, GLfloat movz)
{
    this->SetShader(sact);

    posx = x;
    posy = y;
    posz = z;
    localxyz = glm::vec3(movx,movy,movz);

    CargarBillboard(_ruta);
}

TBillboard::~TBillboard()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture);
}

//Cargar cuadrado de billboard
void TBillboard::CargarBillboard(const char * _ruta)
{
    //***********RECTANGULO***********
    //Vertices de un RECTANGULO
    float vertices[] = {
        // positions          // colors           //Coordenadas de la textura (ejes s,t)
        -1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
         1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
         1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    // Crear buffers/arrays

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Enlazar el objeto Vertex Array
    glBindVertexArray(VAO);

    // Cargar datos en los buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //**********VERTICES***********
    // Atributo posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Atributo color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    // Atributo textura
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //Cerrar el enlace
    glBindVertexArray(0);

    //*********** TEXTURAS ***********
    //TEXTURA 1
    //Crear textura
    glGenTextures(1, &texture); //primer parametro el numero de texturas

    //Enlazar textura
    glBindTexture(GL_TEXTURE_2D, texture);

    //Parametros de la textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);   //glTexParameteri(tipo_de_textura,opcion_y_eje,modo_de_ajuste)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);   //GL_MIRRORED_REPEAT:se repite la textura si no encaja, pero girada
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);       //Filtrado al minimizar
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);        //Filtrado al aumentar

    //Crear textura
    glGenTextures(1, &texture);

    //Cargar y generar textura
    stbi_set_flip_vertically_on_load(true);  // le dices a stb_image.h que gire la textura cargada en el y-axis
    unsigned char *data = stbi_load(_ruta, &width, &height, &nrComponents, 0);
    if (data)
    {
        //Enlazar textura
        glBindTexture(GL_TEXTURE_2D, texture);

        //Parametros de la textura
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        //Filtrado y escalado de texturas
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Fallo al cargar la textura: " << _ruta << std::endl;
        stbi_image_free(data);
    }

    shader->Use();
    shader->setInt("texture1", 0);
}

//sobrecarga metodos TEntidad
void TBillboard::beginDraw()
{
    shader->Use();
    glm::vec2 newscale = glm::vec2(1.0,1.0);
    if(matriz_compartida == nullptr)
    {
        glm::mat4 * _matriz_resultado = nullptr;
        std::queue<glm::mat4 *> * cola_compartidaAuxiliar = new std::queue<glm::mat4 *>; //creamos una cola nueva para ir encolando  los elementos que desencolamos de la cola compartida(se aplicaria parecido con una pila)
        glm::mat4 * _matriz_escalado = new glm::mat4(1.0f);
        glm::mat4 * _matriz_traslade = new glm::mat4(1.0f);
        glm::mat4 * _matriz_rotacion = new glm::mat4(1.0f);

        while(cola_compartida->size() > 0)
        {
            glm::mat4 * nodo = cola_compartida->front();
            cola_compartidaAuxiliar->push(nodo);
            //cogemos el primer valor de la pila
            if(_matriz_resultado == nullptr)
            {
                _matriz_resultado = new glm::mat4(1.0f);
                *_matriz_resultado = (*_matriz_resultado)*(*nodo);

                if(cola_compartida->size() == 3)
                {
                    // std::cout << "escalado: "<< "\n" << (*nodo)[0][0] << " " << (*nodo)[1][0] << " " << (*nodo)[2][0]  << " " << (*nodo)[3][0] << "\n" << (*nodo)[0][1] << " " << (*nodo)[1][1] << " " << (*nodo)[2][1]  << " " << (*nodo)[3][1] << "\n" << (*nodo)[0][2] << " " << (*nodo)[1][2] << " " << (*nodo)[2][2]  << " " << (*nodo)[3][2] << "\n" << (*nodo)[0][3] << " " << (*nodo)[1][3] << " " << (*nodo)[2][3]  << " " << (*nodo)[3][3] << std::endl;
                    *_matriz_escalado = *nodo;
                    newscale = glm::vec2((*nodo)[0][0],(*nodo)[1][1]);
                }
            }
            else
            {
                if(cola_compartida->size() == 1)
                {
                    //std::cout << "traslacion: "<< "\n" << (*nodo)[0][0] << " " << (*nodo)[1][0] << " " << (*nodo)[2][0]  << " " << (*nodo)[3][0] << "\n" << (*nodo)[0][1] << " " << (*nodo)[1][1] << " " << (*nodo)[2][1]  << " " << (*nodo)[3][1] << "\n" << (*nodo)[0][2] << " " << (*nodo)[1][2] << " " << (*nodo)[2][2]  << " " << (*nodo)[3][2] << "\n" << (*nodo)[0][3] << " " << (*nodo)[1][3] << " " << (*nodo)[2][3]  << " " << (*nodo)[3][3] << std::endl;
                    *_matriz_traslade = *nodo;
                }

                if(cola_compartida->size() == 2)
                {
                    //std::cout << "rotacion: "<< "\n" << (*nodo)[0][0] << " " << (*nodo)[1][0] << " " << (*nodo)[2][0]  << " " << (*nodo)[3][0] << "\n" << (*nodo)[0][1] << " " << (*nodo)[1][1] << " " << (*nodo)[2][1]  << " " << (*nodo)[3][1] << "\n" << (*nodo)[0][2] << " " << (*nodo)[1][2] << " " << (*nodo)[2][2]  << " " << (*nodo)[3][2] << "\n" << (*nodo)[0][3] << " " << (*nodo)[1][3] << " " << (*nodo)[2][3]  << " " << (*nodo)[3][3] << std::endl;
                    *_matriz_rotacion = *nodo;
                }
            }

            cola_compartida->pop();
        }

        *_matriz_resultado = (*_matriz_traslade) * (*_matriz_rotacion) * (*_matriz_escalado);

        if(_matriz_resultado != nullptr)
        {
            // Aplicar Textura
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            shader->setVec2("scale", newscale);
            shader->setVec3("localcoord", localxyz);
            // dibujar triangulo
            glBindVertexArray(VAO);
            shader->setMat4("model", (*_matriz_resultado));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        delete cola_compartida;//borramos la cola anterior porque esta vacia
        delete _matriz_escalado;
        delete _matriz_traslade;
        delete _matriz_rotacion;
        delete _matriz_resultado;
        cola_compartida = cola_compartidaAuxiliar;//ponemos la nueva cola que tiene los elementos situados como la anterior

    }
    else
    {
        if(matriz_compartida != nullptr)
        {
            // Aplicar Textura
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);

            shader->setVec2("scale", newscale);
            shader->setVec3("localcoord", localxyz);

            // dibujar triangulo
            glBindVertexArray(VAO);
            shader->setMat4("model", (*matriz_compartida));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }

}

void TBillboard::endDraw()
{

}
