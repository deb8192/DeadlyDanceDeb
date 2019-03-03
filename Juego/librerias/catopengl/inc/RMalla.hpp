#ifndef RMalla_HPP
#define RMalla_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>

#include "Mesh.hpp"
#include "Recurso.hpp"

class RMalla : public Recurso
{
    public:

        RMalla();
        void Remove();

        //te carga los datos en la matrix
        bool CargarRecurso(const char *);
        void Draw(Shader *shader);
        //datos * CargarFrames(unsigned short,unsigned short); //le pasas datos[x]


    private:

        void processNode(aiNode *node, const aiScene *scene);
        Mesh * processMesh(aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        unsigned int TextureFromFile(const char *path, const std::string &directory);

        vector<Mesh *> meshes;              //Guardar mallas del modelo
        vector<Texture *> textures_loaded;	//Guarda todas las texturas cargadas
        std::string directory;              //Directorio con los objetos
        unsigned short objetos,mallas;      //Numero de objetos y mallas
        //datos * para pasarlos a la entidad

};

#endif
