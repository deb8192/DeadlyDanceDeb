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

        RMalla(int f);
        ~RMalla();

        //te carga los datos en la matrix
        bool CargarMalla(std::string _ruta);
        bool CargarAnimacion(const char * _ruta);
        bool CargarRecurso(const char * _ruta);
        void Draw(Shader *shader, float time);
        void SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
        void SetTexture(const char * _ruta);

    private:

        void processNode(aiNode *node, const aiScene *scene);
        Mesh * processMesh(aiMesh *mesh, const aiScene *scene);
        unsigned int TextureFromFile(const char *path);

        vector< vector<Mesh *> > frames;    //Frames de animacion
        vector<Mesh *> meshes;              //Guardar mallas del modelo
        vector<Texture> textures_loaded;	//Guarda todas las texturas cargadas
        std::string directory;              //Directorio con los objetos
        unsigned int objetos,mallas;      //Numero de objetos y mallas
        bool text_cargada;

};

#endif
