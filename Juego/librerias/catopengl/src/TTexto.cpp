#include "TTexto.hpp"

TTexto::TTexto(GLuint width, GLuint height, Shader * sact)
{
    this->SetShader(sact);
    //Cargar y configurar Shader
    shader->Use();
    shader->setMat4("projection", glm::ortho(0.0f,static_cast<GLfloat>(width),static_cast<GLfloat>(height),0.0f));
    shader->setInt("text", 0);
    //Configurar VAO y VBO
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //Texto por defecto
    CrearTexto("Deafult Text",0,0,200,10, 1.0f, 1.0f, 1.0f, 1.0f);
}

void TTexto::CargarFuente(std::string font, GLuint fontSize)
{
    // Primero limpiar los caracteres cargados previamente
    this->Characters.clear();
    // Inicializar la libreria freetype
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) //Si ocurre un error (!= 0)
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    //Cargar la fuente
    FT_Face face;
    if (FT_New_Face(ft, font.c_str(), 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    //Ajustar tamanyo del glyph
    FT_Set_Pixel_Sizes(face, 0, fontSize);
    //Desactivar restriccion de alineacion de bytes
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //Guardar y compilar los 128 caracteres ASCII
    for (GLubyte c = 0; c < 128; c++)
    {
        // Cargar caracter
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generar textura
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RED,face->glyph->bitmap.width,face->glyph->bitmap.rows,0,GL_RED,GL_UNSIGNED_BYTE,face->glyph->bitmap.buffer);
        // Ajustar textura
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Guardar caracter para su uso mas tarde
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // Destruir el freetype
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TTexto::CrearTexto(std::string newtext, GLfloat xx, GLfloat yy, GLfloat xxe, GLfloat salto, GLfloat sc, float r, float g, float b)
{
    texto = newtext;
    x = xx;
    y = yy;
    endx = xxe;
    salto_linea = salto;
    scale = sc;
    color = glm::vec3(r, g, b);
}

void TTexto::beginDraw()
{
    // Activar render
    shader->Use();
    shader->setVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->VAO);

    //Guardar primera posicion
    GLfloat auxx = x;
    GLfloat auxy = y;
    // Iterar a traves de todods los caracteres
    std::string::const_iterator c;
    for (c = texto.begin(); c != texto.end(); c++)
    {
        Character ch = Characters[*c];

        //Comprobar si estas en el limite en x, saltar linea en y
        if(x + ch.Size.x > endx)
        {
            x = auxx;
            y = y + ch.Size.y + salto_linea;
        }

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Actualizar VBO por cada caracter
        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 1.0 },
            { xpos + w, ypos,       1.0, 0.0 },
            { xpos,     ypos,       0.0, 0.0 },

            { xpos,     ypos + h,   0.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 1.0 },
            { xpos + w, ypos,       1.0, 0.0 }
        };
        //Render el glyph
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        //Avanzar al siguiente caracter
        x += (ch.Advance >> 6) * scale; // desplazamiente es 6 para obtener valor en píxeles (1/64 veces 2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
     //poner valor de x e y de nuevo a la posicion primera
    x = auxx;
    y = auxy;

}

void TTexto::endDraw()
{

}
