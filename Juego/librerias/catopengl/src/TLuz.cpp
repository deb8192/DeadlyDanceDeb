#include "TLuz.hpp"

TLuz::TLuz(int t,int anim)
{
    didentidad = 'L'; //para sabe que funcion hace
    tipo_luz = t; //tipo de luz
    if(t == 0)
    {
        setAmbient(140.25f, 140.25f, 140.25f);
        setDiffuse(178.5f, 178.5f, 178.5f);
        setSpecular(204.0f, 204.0f, 204.0f);
        setDirection(0.0f, -1.0f, -0.5f);
        setBrillos(8.0f);
    }
    else if(t == 1)
    {
        setAmbient(178.5f, 178.5f, 178.5f);
        setDiffuse(229.5f, 229.5f, 229.5f);
        setSpecular(255.0f, 255.0f, 255.0f);
        setLightRange(150.0f);
        setBrillos(32.0f);
        tipo_anim = anim;
    }
    else if(t == 2)
    {
        setAmbient(255.0f, 255.0f, 255.0f);
        setDiffuse(255.0f, 255.0f, 255.0f);
        setSpecular(255.0f, 255.0f, 255.0f);
        setDirection(0.0f, -1.0f, 0.0f);
        setLightRange(150.0f);
        setBrillos(32.0f);
    }
}

TLuz::~TLuz()
{

}

void TLuz::setIntensidad(float *)
{

}

float TLuz::getIntensidad()
{
    return 0.0f;
}

void TLuz::beginDraw()
{
    //comprobamos que la cola o pila no haya tenido cambios, si los tiene se vuelve a calcular
    if(matriz_compartida == nullptr)
    {
        glm::mat4 rotacion;
        glm::mat4 * _matriz_resultado = nullptr;
        std::queue<glm::mat4 *> * cola_compartidaAuxiliar = new std::queue<glm::mat4 *>; //creamos una cola nueva para ir encolando  los elementos que desencolamos de la cola compartida(se aplicaria parecido con una pila)
        while(cola_compartida->size() > 0)
        {
            glm::mat4 * nodo = cola_compartida->front();
            cola_compartidaAuxiliar->push(nodo);
            //cogemos el primer valor de la pila
            if(_matriz_resultado == nullptr)
            {
                _matriz_resultado = new glm::mat4;
                *_matriz_resultado = *nodo;
            }
            else
            {
                if(cola_compartida->size() == 1)//traslacion
                {
                    posicion = glm::vec3((*nodo)[3][0],(*nodo)[3][1],(*nodo)[3][2]);
                }

                if(cola_compartida->size() == 2)
                {
                    rotacion = (*nodo);
                }

                *_matriz_resultado = (*_matriz_resultado) * (*nodo);
            }

            cola_compartida->pop();
        }

        delete cola_compartida;//borramos la cola anterior porque esta vacia
        cola_compartida = cola_compartidaAuxiliar;//ponemos la nueva cola que tiene los elementos situados como la anterior
        delete _matriz_resultado;//borrado de la luz

        shader->Use();
        shader->setFloat("material.shininess", brillos_shader); //Cantidad de Brillos
        //Tipos de luces
        if(tipo_luz == 0)
        {
            shader->setVec3("dirLight.ambient", ambient);
            shader->setVec3("dirLight.diffuse", diffuse);
            shader->setVec3("dirLight.specular", specular);
            shader->setVec3("dirLight.direction", direction); //Enviar la direccion donde mira la luz direccional
        }
        else if(tipo_luz == 1)
        {
            //Animacion 1
            if(tipo_anim == 1)
            {
                posicion.x = posicion.x + (((rand() % 50) + (-50)) / 100.0f);
                posicion.y = posicion.y + (((rand() % 50) + (-50)) / 100.0f);
                posicion.z = posicion.z + (((rand() % 50) + (-50)) / 100.0f);
            }
            //Animacion 2
            else if(tipo_anim == 2)
            {
                if(animaescala == 100)cambiaranima = true;
                if(animaescala == 0)cambiaranima = false;
                if(cambiaranima)
                {
                    animaescala=animaescala-2;
                }else{
                    animaescala=animaescala+2;
                }
                setAmbient(ambient.x+animaescala,ambient.y+animaescala,ambient.z+animaescala);
                setDiffuse(diffuse.x+animaescala,diffuse.y+animaescala,diffuse.z+animaescala);
                setSpecular(specular.x+animaescala,specular.y+animaescala,specular.z+animaescala);
            }

            std::string n = std::to_string(numberoflight);
            shader->setVec3("pointLights[" + n + "].ambient", ambient);
            shader->setVec3("pointLights[" + n + "].diffuse", diffuse);
            shader->setVec3("pointLights[" + n + "].specular", specular);
            shader->setVec3("pointLights[" + n + "].position", posicion);
            shader->setFloat("pointLights[" + n + "].constant", 1.0f);
            shader->setFloat("pointLights[" + n + "].linear", linear);
            shader->setFloat("pointLights[" + n + "].quadratic", quadratic);
        }
        else if(tipo_luz == 2)
        {
            shader->setVec3("spotLight.position", posicion);    //Enviar la posicion
            shader->setVec3("spotLight.direction", direction);  //Enviar la direccion
            shader->setVec3("spotLight.ambient", ambient);
            shader->setVec3("spotLight.diffuse", diffuse);
            shader->setVec3("spotLight.specular", specular);
            shader->setFloat("spotLight.constant", 1.0f);
            shader->setFloat("spotLight.linear", linear);
            shader->setFloat("spotLight.quadratic", quadratic);
            shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));       //Punto de corte
            shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));  //Punto de corte con el cono externo
        }

        //if(_matriz_resultado != nullptr)//si la matriz de resultado es nula es que no hay nada en la cola por lo que no hay nada que enviar al shader
        //{
            //enviar a uniform
            //std::cout << (*_matriz_resultado)[3][0] << " " << (*_matriz_resultado)[3][1] << " " << (*_matriz_resultado)[3][2] << " " << (*_matriz_resultado)[3][3] << std::endl;
        //}
    }
    else
    {
        shader->Use();
        shader->setFloat("material.shininess", brillos_shader); //Cantidad de Brillos
        //Tipos de luces
        if(tipo_luz == 0)
        {
            shader->setVec3("dirLight.ambient", ambient);
            shader->setVec3("dirLight.diffuse", diffuse);
            shader->setVec3("dirLight.specular", specular);
            shader->setVec3("dirLight.direction", direction); //Enviar la direccion donde mira la luz direccional
        }
        else if(tipo_luz == 1)
        {
            std::string n = std::to_string(numberoflight);
            shader->setVec3("pointLights[" + n + "].ambient", ambient);
            shader->setVec3("pointLights[" + n + "].diffuse", diffuse);
            shader->setVec3("pointLights[" + n + "].specular", specular);
            shader->setVec3("pointLights[" + n + "].position", glm::vec3(0.0f,0.0f,0.0f));
            shader->setFloat("pointLights[" + n + "].constant", 1.0f);
            shader->setFloat("pointLights[" + n + "].linear", linear);
            shader->setFloat("pointLights[" + n + "].quadratic", quadratic);
        }
        else if(tipo_luz == 2)
        {
            shader->setVec3("spotLight.position", glm::vec3(0.0f,0.0f,0.0f));  //Enviar la posicion
            shader->setVec3("spotLight.direction", direction);                 //Enviar la direccion
            shader->setVec3("spotLight.ambient", ambient);
            shader->setVec3("spotLight.diffuse", diffuse);
            shader->setVec3("spotLight.specular", specular);
            shader->setFloat("spotLight.constant", 1.0f);
            shader->setFloat("spotLight.linear", linear);
            shader->setFloat("spotLight.quadratic", quadratic);
            shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));       //Punto de corte
            shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));  //Punto de corte con el cono externo
        }
    }
}

//Color luz ambiental
void TLuz::setAmbient(float r,float g,float b)
{
    float rf = transformToRGB(r);
    float gf = transformToRGB(g);
    float bf = transformToRGB(b);
    ambient = glm::vec3(rf,gf,bf);
}

//Color luz difusa
void TLuz::setDiffuse(float r,float g,float b)
{
    float rf = transformToRGB(r+50);
    float gf = transformToRGB(g+50);
    float bf = transformToRGB(b+50);
    diffuse = glm::vec3(rf,gf,bf);
}

//Color luz especular
void TLuz::setSpecular(float r,float g,float b)
{
    float rf = transformToRGB(r+75);
    float gf = transformToRGB(g+75);
    float bf = transformToRGB(b+75);
    specular = glm::vec3(rf,gf,bf);
}

//numero de luz
void TLuz::setNumberoflight(int n)
{
    numberoflight = n;
}

//Direccion de la luz
void TLuz::setDirection(float x,float y,float z)
{
    direction = glm::vec3(x,y,z);
}

//Atenuacion por distancia de la luz
void TLuz::setLightRange(float range)
{
    linear = 4.5f / range;
    quadratic = 75.0f / (range*range);
}

//Aplica una cantidad de brillos para el shader (32 por defecto)
void TLuz::setBrillos(float b)
{
    brillos_shader = b;
}

float TLuz::transformToRGB(float c)
{
    if(c > 255.0f)c = 255.0f;
    if(c < 0.0f)c = 0.0f;
    float t = (1.0f/255.0f) * c;
    return t;
}

void TLuz::endDraw()
{
    //std::cout << didentidad << "final" << std::endl;
}
