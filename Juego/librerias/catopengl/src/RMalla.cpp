#include "RMalla.hpp"
#include "Gestor.hpp"

RMalla::RMalla(int f)
{
    tipo = 'M';
    objetos = f;
    mallas = 0;
    text_cargada = false;
    frames.reserve(150);
}

RMalla::~RMalla()
{
    textures_loaded.clear();
}

// draws the model, and thus all its meshes
void RMalla::Draw(Shader *shader, float frame)
{
    for(unsigned int j = 0; j < frames[frame].size() && frame < frames.size(); j++)
    {

        frames[frame][j]->Draw(shader);
    }
}

bool RMalla::CargarRecurso(const char * _ruta)
{
    std::string path = _ruta;
    bool recurso = CargarAnimacion(_ruta);
    return recurso;
}

//Carga de frames
bool RMalla::CargarAnimacion(const char * _ruta)
{
    //Pasarlo a string
    std::string path = _ruta;

    //Directorio
    directory = path.substr(0, path.find_last_of('/'));

    //Si tiene mas de 1 frame
    if(objetos > 1)
    {
        //Obtenemos el nombre del fichero
        std::size_t found = path.find_last_of("/\\");
        std::string filename = path.substr(found+1);
        std::string name = filename.substr(0, filename.find_last_of('_'));

        //Obtener extension del fichero
        found = filename.find('.');
        std::string ext = filename.substr(found+1);

        for(unsigned int i=1; i <= objetos; i++)
        {
            if(i > 1 && text_cargada == false)text_cargada = true;
            //cout << "Objeto " << i << ": " << endl;

            //Crear el string del numero de frames
            std::stringstream ss;
            ss << setw(6) << setfill('0') << i;
            std::string nframes = ss.str();

            //String con el directorio completo
            std::ostringstream newstring;
            newstring << directory << "/" << name << "_" << nframes << "." << ext;
            std::string pathfile = newstring.str();

            //Cargar mallas
            if(!CargarMalla(pathfile))
            {
                return false;
            }
        }
    }
    else
    {
        //Cargar mallas
        if(!CargarMalla(path))
        {
            return false;
        }
    }

    textures_loaded.clear();

    return true;

}

bool RMalla::CargarMalla(std::string _ruta)
{
    //carga los datos con assimp, mete el numero de datos que tiene en objetos,
    //numeros de mallas que tiene en mallas
    //Leer fichero de assimp
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(_ruta, aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_CalcTangentSpace);

    //Mirar errores en la lectura
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return false;
    }

    // procesar recursivamente los nodos
    processNode(scene->mRootNode, scene);

    /*for(unsigned int i=0; i < meshes.size(); i++)
    {
        cout << " |- Malla " << i << ": " << meshes.at(i) << endl;
    }*/

    mallas = meshes.size();
    frames.push_back(meshes); //Guardar frame de animacion
    meshes.clear();

    return true;
}

// Procesar un nodo en recursiva. Procesea individualmente las mallas localizadas en el nodo y repite este proceso
void RMalla::processNode(aiNode *node, const aiScene *scene)
{
    // Procesar cada malla localizada en el nodo actual
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // Los objetos nodo contiene indices de los objetos actuales en la escena.
        // La escena contiene todos los datos, los nodos se mantienen organizados (relaciones entre nodos)
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    // Despues procesamos todos las mallas que recursivamente procesa cada uno de los nodos hijos
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

//Procesar una malla
Mesh * RMalla::processMesh(aiMesh *mesh, const aiScene *scene)
{
    //Datos
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    //Moverse por cada unos de los vertices de las mallas
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        //Posiciones
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        //Normales
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        //Coordinadas de textura
        if(mesh->mTextureCoords[0]) //¿La malla contiene las coordeandas de las texturas?
        {
            glm::vec2 vec;
            // Un vertice puede contener 8 diferentes coordinadas de texturas.Por lo tanto, asumimos que no vamos a
            // usar modelos en los que un vértice puede tener múltiples coordenadas de textura, por lo que siempre
            // tomamos la primera serie (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    // Ahora atraves de cada cara de la malla, y salva los indices del vertice correspondiente
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // salva todos los indices de la cara y guarda en los indices del vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    //Mirar si ya existe la textura para no cargarla
    if(text_cargada == false)
    {
        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if(strcmp(textures_loaded.at(j).path,"default_texture") == 0)
            {
                textures.push_back(textures_loaded.at(j));
                skip = true; //Si la texgtura ya ha se ha creado no volverla a crearla
                break;
            }
        }
        if(!skip)
        {
            unsigned char r = 231;
            unsigned char g = 255;
            unsigned char b = 50;
            unsigned char a = 255;
            //std::cout << " texturecolor: (" << (float)r << " , " << (float)g << " , " << (float)b << " , " << (float)a << ")" << std::endl;
            //textura no cargada
            unsigned int textureID;

            //AQUI SE PUEDE CREAR UN MODO EN EL GESTOR PARA GUARDAR UNA TEXTURA DE COLORES SOLIDOS DE MOMENTO NO SE PONE PORQUE LOS DATOS ESTAN EN EL COMPILADO, son parte del programa inicial

            glGenTextures(1, &textureID);

            int width=1, height=1;
            GLubyte datamat[] = {r,g,b,a}; //RGBA
            GLenum format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, datamat);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Texture texture;
            texture.id = textureID;
            texture.type = "texture_diffuse";
            texture.path = "default_texture";
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    else
    {
        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            textures.push_back(textures_loaded.at(j));
        }
    }
    //Devolver un objeto mesh creado a partir de los datos mesh extraídos
    Mesh * newmesh = new Mesh(vertices, indices, textures);
    return newmesh;
}

void RMalla::SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    //std::cout << " NUEVA::texturecolor: (" << (float)r << " , " << (float)g << " , " << (float)b << " , " << (float)a << ")" << std::endl;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width=1, height=1;
    GLubyte datamat[] = { r, g, b, a }; //RGBA 231, 255, 50, 255
    GLenum format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, datamat);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Texture newtexture;
    newtexture.id = textureID;
    newtexture.type = "texture_diffuse";
    newtexture.path = "default_texture";

    //Pasar por cada una de las mallas
    for(unsigned int i = 0; i < frames.size(); i++)
    {
        for(unsigned int j = 0; j < frames[i].size(); j++)
        {
            frames[i][j]->ChangeTexture(newtexture);
        }
    }

}

//Cambiar la textura de la malla
void RMalla::SetTexture(const char * _ruta)
{
    if(_ruta != nullptr)
    {
        //std::string filename = std::string(_ruta);

        if(strlen(_ruta) > 0)
        {
            Texture newtexture;

            //Comprobar si ya existe
            bool skip = false;
            for(unsigned int j = 0; j < textures_loaded.size(); j++)
            {
                if(strcmp(textures_loaded.at(j).path,_ruta) == 0)
                {
                    newtexture = textures_loaded.at(j);
                    skip = true; //Si la texgtura ya ha se ha creado no volverla a crearla
                    //std::cout << " CARGADA::filename: " << filename << std::endl;
                    break;
                }
            }
            if(!skip)
            {
                //No existe la textura
                //Nueva textura
                newtexture.id = TextureFromFile(_ruta);
                newtexture.type = "texture_diffuse";
                newtexture.path = _ruta;

                //Guardar para la proxima carga
                textures_loaded.push_back(newtexture);
            }
            //Pasar por cada una de las mallas
            for(unsigned int i = 0; i < frames.size(); i++)
            {
                for(unsigned int j = 0; j < frames[i].size(); j++)
                {
                    frames[i][j]->ChangeTexture(newtexture);
                }
            }
        }
    }
}

//Carga el fichero de textura
unsigned int RMalla::TextureFromFile(const char * path)
{
    Gestor * gestor = Gestor::GetInstance();//instanciamos el gestor para poder crear la textura

    //std::string filename = std::string(path);
    //std::cout << " NUEVA::filename: " << filename << std::endl;

    unsigned int textureID;

    if(gestor->TieneTextura(path))
    {
        //obtenemos el id de la textura ya cargada en opengl
        textureID = gestor->GetTexturaId(path);
    }
    else
    {
        //generamos un id nuevo
        glGenTextures(1, &textureID);
    }
    


    int width, height, nrComponents;

    if(gestor->TieneTextura(path))
    {
        //std::cout << "Ya existe la textura -> " << path << "\n";
        //tiene textura ya en memoria
        gestor->CopiarParametrosImagen(path, &width, &height, &nrComponents);
    }
    else
    {
        //std::cout << "No existe la textura -> " << path << "\n";
        //no tiene textura en gestor
        unsigned char * data = gestor->CargarImagen(path, &width, &height, &nrComponents);
        
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            data = nullptr;

            //le decimos que el id de la textura en opengl pertenece a esta imagen cargada (path)
            gestor->VincularTexturaImagen(path,textureID);
            //liberamos los datos al cargar la imagen, no se liberan los datos de opengl para eso habria que llamar a DestruirDatosImagenOpengl, una vez ya la textura en memoria no sirve de nada tener los datos de la carga
            gestor->DestruirDatosImagen(path);
            //stbi_image_free(data);
        }
        else
        {
            std::cout << "ERROR:: en la ruta de textura: " << path << std::endl;
            data = nullptr;
            //stbi_image_free(data);
        }
    }
    
    gestor = nullptr;

    return textureID;
}
