#include "TPlano.hpp"

TPlano::TPlano(const char * archivo, unsigned int x, unsigned int y, float scale, Shader * sact, GLuint ww, GLuint wh, const char * rutapulsado , const char * rutaencima )
{
    winwidth = ww;
    winheight = wh;
    didentidad = 'I';
    pixx = x;
    pixy = y;
    escaladox = scale;
    escaladoy = scale;
    this->SetShader(sact);
    shader->Use();
    bool recurso = CargarTextura(archivo);
    id = -1;
    esEncima = false;
    esPulsable = false;
    if(recurso)
    {
        CargarMalla(pixx,pixy,escaladox,escaladoy);
    }

    //ahora vamos a cargar las imagenes que seran los recursos de pulsado y encima
    if(rutapulsado != nullptr)
    {
        CargarTextura(rutapulsado,2);
    }

    if(rutaencima != nullptr)
    {
        CargarTextura(rutaencima,3);
    }
}

TPlano::~TPlano()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &textureID);
    glDeleteTextures(1, &textureIDPulsado);
    glDeleteTextures(1, &textureIDEncima);
}

// sobrecarga metodos TEntidad
void TPlano::beginDraw()
{
    shader->Use();

    //Actualizar datos si es necesario
    UdateMesh();

    // Desactivar cullin
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // Aplicar Textura
    glActiveTexture(GL_TEXTURE0);
    shader->setInt("texture1", 0);
    glBindTexture(GL_TEXTURE_2D, estado);

    // dibujar triangulo
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Activar cullin
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

bool TPlano::CargarTextura(const char * _ruta,unsigned int mode)
{
    //Crear textura
    if(mode == 1)//normal
    {
        glGenTextures(1, &textureID);
        estado = textureID;
    }

    if(mode == 2)//pulsado
    {
        glGenTextures(1, &textureIDPulsado);
    }

    if(mode == 3)//encima
    {
        glGenTextures(1, &textureIDEncima);
    }

    //Cargar y generar textura
    stbi_set_flip_vertically_on_load(true);  // le dices a stb_image.h que gire la textura cargada en el y-axis
    unsigned char *data = stbi_load(_ruta, &width, &height, &nrComponents, 0);//esto hay que ponerlo en la zona de recursos
    if (data)
    {
        //Enlazar textura
        if(mode == 1)//normal
        {
            glBindTexture(GL_TEXTURE_2D, textureID);
        }

        if(mode == 2)//pulsado
        {
            glBindTexture(GL_TEXTURE_2D, textureIDPulsado);
            esPulsable = true;
        }

        if(mode == 3)//encima
        {
            glBindTexture(GL_TEXTURE_2D, textureIDEncima);
            esEncima = true;
        }

        //Parametros de la textura
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   //glTexParameteri(tipo_de_textura,opcion_y_eje,modo_de_ajuste)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        //Filtrado y escalado de texturas (GL_NEAREST:mas pixelado, mejor para minimizar/ GL_LINEAR:mas suave y borroso, mejor para aumentar)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);       //Filtrado al minimizar
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);       //Filtrado al aumentar

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Fallo al cargar la textura: " << _ruta << std::endl;
        stbi_image_free(data);
        return false;
    }

    return true;
}

void TPlano::CargarMalla(unsigned int xx, unsigned int yy, float sx, float sy)
{
    float posx = xx;
    float posy = yy;
    float scalex = sx;
    float scaley = sy;
    int screen_w = winwidth;
    int screen_h = winheight;

    // Calculos de pixel a mundo 2D
    posx = ((posx + 0.5f) / (float)screen_w) * 2.0f - 1.0f;
    posy = 1.0f - ((posy + 0.5f) / (float)screen_h) * 2.0f;
    float x = ((width * scalex + 0.5f) / (float)screen_w) * 2.0f - 1.0f;
    float y = 1.0f - ((height * scaley + 0.5f) / (float)screen_h) * 2.0f;
    x = 1.0 + (x + posx);
    y = (y + posy) - 1.0;

    // cout << "width: "<< width << endl;
    // cout << "height: "<< height << endl;
    // cout << "posx: " << posx << endl;
    // cout << "posy: " << posy << endl;
    // cout << "x: "<< x << endl;
    // cout << "y: "<< y << endl;

    // Vertices de un RECTANGULO
    float vertices[] = {
        //positions           //colors          //Coordenadas de la textura (ejes s,t)
        x,    posy, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
        x,       y, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
        posx,    y, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
        posx, posy, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // primer triangulo
        1, 2, 3  // segundo triangulo
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
}

void TPlano::UdateMesh()
{
    if(cambios)
    {
        CargarMalla(pixx,pixy,escaladox,escaladoy);
        cambios = false;
    }
}

void TPlano::setSize(float w,float h)
{
    if(width != w || height != h)
    {
        width = w;
        height = h;
        cambios = true;
    }
}

void TPlano::setPosition(float x,float y)
{
    if(pixx != x || pixy != y)
    {
        pixx = x;
        pixy = y;
        cambios = true;
    }
}

void TPlano::setScale(float sx, float sy)
{
    if(escaladox != sx || escaladoy != sy)
    {
        escaladox = sx;
        escaladoy = sy;
        cambios = true;
    }
}

void TPlano::setScaleX(float nx)
{
    escaladox = nx;
    escaladoy = escaladoy;
    cambios = true;
}

void TPlano::setScaleY(float ny)
{
    escaladoy = ny;
    escaladox = escaladox;
    cambios = true;
}

void TPlano::endDraw()
{

}

bool TPlano::Comprobar()
{
    if(id != -1)
    {
        return true;
    }

    return false;
}

void TPlano::CambiarId(int newid)
{
    id = newid;
}

bool TPlano::botonPulsado(double * mouse)
{
    // cout << pixx << endl;
    // cout << pixx+(width * escalado) << endl;
    // cout << pixy << endl;
    // cout << pixy+(height * escalado) << endl;
    //Si el raton esta en rango
    if(mouse[0] > pixx && mouse[0] < pixx+(width * escaladox) && mouse[1] > pixy && mouse[1] < pixy+(height * escaladoy))
        return true;

    return false;
}

int TPlano::getID()
{
    return id;
}

bool TPlano::GetEsPulsable()
{
    return esPulsable;
}

bool TPlano::GetEsEncima()
{
    return esEncima;
}

void TPlano::CambiarEstado(unsigned int newEstado)
{
    if(newEstado == 3 && esEncima)
    {
        //std::cout << "esta encima" << std::endl;
        estado = textureIDEncima;
        return;
    }
    if(newEstado == 2 && esPulsable)
    {
        estado = textureIDPulsado;
        return;
    }

    estado = textureID;//cualquier otro estado
}
