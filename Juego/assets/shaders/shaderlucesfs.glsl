#version 330 core

out vec4 FragColor;

struct Material {       //Estructura material
    sampler2D diffuse;  //Luz de la textura (luz ambiental y difusa)
    sampler2D specular; //Luz especular de la textura
    float shininess;    //Brillo (dispersion de punto de luz especular)
};

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

//Luz direccional
struct DirLight {
    vec3 direction;     //Direccion de la luz

    vec3 ambient;       //Influencia de la luz ambiental en los objetos
    vec3 diffuse;       //Influencia de la luz difusa en los objetos
    vec3 specular;      //Influencia de la luz especular en los objetos
};

//Punto de Luz
struct PointLight {
    vec3 position;      //Posicion de la luz

    //Propiedades para la atenuacion (intensidad de la luz)
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;       //Influencia de la luz ambiental en los objetos
    vec3 diffuse;       //Influencia de la luz difusa en los objetos
    vec3 specular;      //Influencia de la luz especular en los objetos
};

//Foco de luz
struct SpotLight {
    vec3 position;      //Posicion de la luz
    vec3 direction;     //Direccion de la luz
    float cutOff;       //Punto de corte
    float outerCutOff;  //Punto de corte de cono externo

    //Propiedades para la atenuacion (intensidad de la luz)
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;       //Influencia de la luz ambiental en los objetos
    vec3 diffuse;       //Influencia de la luz difusa en los objetos
    vec3 specular;      //Influencia de la luz especular en los objetos
};

#define NR_POINT_LIGHTS 4    //X puntos de luz

in vec3 Normal;            //Recibimos las normales del vertex
in vec3 FragPos;           //Recibimos la posicion del fragment actual
in vec2 TexCoords;         //Coordenadas de la textura

uniform vec3 viewPos;         //Posicion de la camara
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;    //materiales (pagina con distintos materiales: http://devernay.free.fr/cours/opengl/materials.html)

//Funciones de calculo de luces
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    //Propiedades
    vec3 norm = normalize(Normal);                          //Normalizar las normales
    vec3 viewDir = normalize(viewPos - FragPos);            //Calculo de direccion de camara

    //Fase 1: Luz direccional
    vec3 result = CalcDirLight(dirLight, norm, viewDir);

    //Fase 2: Puntos de Luz
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);

    //Fase 3: Foco de Luz/Spotlight
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}

//Calcular Luz Direccional
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);                //La direccion de la luz en la luz direccional

    //Luz Difusa
    float diff = max(dot(normal, lightDir), 0.0);               //Impacto difuso real (usamos max para que el color nunca sea negativo si sube de 90 grados)

    //Luz Especular
    vec3 reflectDir = reflect(-lightDir, normal);               //Reflejo (la direccion de la luz es negativa porque va desde la luz hasta la vista no hacia el fragment como en la difusa)
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);    //Calculo del componente especular (max para asegurar que no sea negativo), material.shininess es el valor del brillo cambialo para mas o menos brillo (32,64,128,etc...)

    //Combinar resultados
    vec3 ambient  = light.ambient  * vec3(texture(texture_diffuse1, TexCoords));  //Luz Ambiental
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));
    return (ambient + diffuse + specular);
}

//Calcular Punto de Luz
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);        //La direccion de la luz es la diferencia entre el vector de posicion de la luz y el vector de posicion del fragment

    //Luz Difusa
    float diff = max(dot(normal, lightDir), 0.0);               //Impacto difuso real (usamos max para que el color nunca sea negativo si sube de 90 grados)

    //Luz Especular
    vec3 reflectDir = reflect(-lightDir, normal);               //Reflejo (la direccion de la luz es negativa porque va desde la luz hasta la vista no hacia el fragment como en la difusa)
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);     //Calculo del componente especular (max para asegurar que no sea negativo), material.shininess es el valor del brillo cambialo para mas o menos brillo (32,64,128,etc...)

    //Calculos de distancia y atenuacion de la luz
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
  			            light.quadratic * (distance * distance));

    //Combinar resultados
    vec3 ambient  = light.ambient  * vec3(texture(texture_diffuse1, TexCoords));  //Luz Ambiental
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));
    //Aplicamos atenuacion a las luces
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

//Calcular Foco de luz
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    //Luz Difusa
    float diff = max(dot(normal, lightDir), 0.0);

    //Luz Especular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    //Calculos de distancia y atenuacion de la luz
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                        light.quadratic * (distance * distance));

    //Calculo de la Intensidad del foco
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    //Combinar resultados
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));
    //Aplicamos atenuacion e intensidad a las luces
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}
