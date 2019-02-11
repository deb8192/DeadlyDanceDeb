#include "CatOpengl.hpp"

FormaPrimitiva::FormaPrimitiva(float * vertices)
{

    float vertices2[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    glGenVertexArrays(1,&VAO);
    
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    
    glBufferData(GL_ARRAY_BUFFER, ((sizeof(vertices)+1)*(sizeof(*vertices))), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    glBindVertexArray(0);

    std::cout << sizeof(vertices) << " " << sizeof(vertices2) << " " << VAO << " " << VBO << std::endl;
}

FormaPrimitiva::~FormaPrimitiva()
{
    glDeleteVertexArrays(1,&VAO);//borra el array de vertices con este id
    glDeleteBuffers(1,&VBO);//borra el buffer con este id
}

void FormaPrimitiva::Remove()
{
    this->~FormaPrimitiva();
}

void FormaPrimitiva::Draw()
{
    glBindVertexArray(VAO); 
    glDrawArrays(GL_TRIANGLES,0,3);
}