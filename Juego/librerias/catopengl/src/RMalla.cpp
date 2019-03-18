#include "RMalla.hpp"

RMalla::RMalla(int f)
{
    tipo = 'M';
    objetos = f;
    mallas = 0;
    frames.reserve(45);
}

void RMalla::Remove()
{

}

// draws the model, and thus all its meshes
void RMalla::Draw(Shader *shader, float frame)
{
    for(unsigned int j = 0; j < frames[frame].size(); j++)
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
            cout << "Objeto " << i << ": " << endl;

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

    return true;

}

bool RMalla::CargarMalla(std::string _ruta)
{
    //carga los datos con assimp, mete el numero de datos que tiene en objetos,
    //numeros de mallas que tiene en mallas

    //Leer fichero de assimp
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(_ruta, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    //directory = _ruta.substr(0, _ruta.find_last_of('/'));

    //Mirar errores en la lectura
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return false;
    }

    // procesar recursivamente los nodos
    processNode(scene->mRootNode, scene);

    for(unsigned int i=0; i < meshes.size(); i++)
    {
        cout << " |- Malla " << i << ": " << meshes.at(i) << endl;
    }

    for(unsigned int i=0; i < textures_loaded.size(); i++)
    {
        cout << " |- Textura " << i << ": " << textures_loaded.at(i) << endl;
    }
    cout << "--------------------" << endl;

    mallas = meshes.size();

    frames.push_back(meshes); //Guardar frame de animacion
    meshes.clear();
    textures_loaded.clear();

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

    // Procesar materiales
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // Asumimos unas lineas para los nombres de los samplers en los shaders. cada textura difusa tiene que ser nombrada
    // como "texture_diffuseN", donde N es un número secuencial que va de 1 a MAX_SAMPLER_NUMBER.
    // Lo mismo se aplica a otras texturas que se resumen en la siguiente lista:
    // Difusa: texture_diffuseN
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    // Especular: texture_specularN
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    if(diffuseMaps.size() == 0 && specularMaps.size() == 0)
    {
        //Mirar si ya existe la textura para no cargarla
        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if(std::strcmp(textures_loaded.at(j)->path.data(), "default_texture") == 0)
            {
                textures.push_back(*textures_loaded.at(j));
                skip = true; //Si la texgtura ya ha se ha creado no volverla a crearla
                break;
            }
        }
        if(!skip)
        {   //textura no cargada aún
            unsigned int textureID;
            glGenTextures(1, &textureID);

            int width=1, height=1;
            GLubyte datamat[] = { 35, 35, 35, 255 }; //RGBA
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
            textures_loaded.push_back(&texture);
        }
    }

    //Devolver un objeto mesh creado a partir de los datos mesh extraídos
    Mesh * newmesh = new Mesh(vertices, indices, textures);
    return newmesh;
}

// checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a Texture struct.
vector<Texture> RMalla::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;

        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if(std::strcmp(textures_loaded.at(j)->path.data(), str.C_Str()) == 0)
            {
                textures.push_back(*textures_loaded.at(j));
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(&texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}

//Carga el fichero de textura
unsigned int RMalla::TextureFromFile(const char *path, const std::string &directory)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    std::cout << " filename: " << filename << std::endl;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
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

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
/* datos * RMalla::GetMalla()
{
    return datos;
}
*/
