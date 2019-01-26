#version 330 core

out vec4 FragColor;

struct Material {       //Estructura material
    sampler2D diffuse;  //Luz de la textura (luz ambiental y difusa)
    sampler2D specular; //Luz especular de la textura
    float shininess;    //Brillo (dispersion de punto de luz especular)
};

struct Light {       //Estructura de luz
    vec3 position;   //Posicion de luz
    vec3 direction;  //Direccion de la luz
    float cutOff;    //Punto de corte
    float outerCutOff; //Punto de corte de cono externo

    vec3 ambient;    //Influencia de la luz ambiental en los objetos
    vec3 diffuse;    //Influencia de la luz difusa en los objetos
    vec3 specular;   //Influencia de la luz especular en los objetos

    //Propiedades para la atenuacion (intensidad de la luz)
    float constant;
    float linear;
    float quadratic;
};

in vec3 Normal;            //Recibimos las normales del vertex
in vec3 FragPos;           //Recibimos la posicion del fragment actual
in vec2 TexCoords;         //Coordenadas de la textura

uniform vec3 viewPos;      //Posicion de la camara para calcular la luz especular
uniform Material material; //materiales (pagina con distintos materiales: http://devernay.free.fr/cours/opengl/materials.html)
uniform Light light;

void main()
{
    //Luz Ambiental
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;  //Calculo de la luz ambiental

    //Luz Difusa
    vec3 norm = normalize(Normal);                              //normalizar
    vec3 lightDir = normalize(light.position - FragPos);        //la direccion de la luz es la diferencia entre el vector de posicion de la luz y el vector de posicion del fragment
    //vec3 lightDir = normalize(-light.direction);              //La direccion de la luz en la luz direccional
    float diff = max(dot(norm, lightDir), 0.0);                 //impacto difuso real (usamos max para que el color nunca sea negativo si sube de 90 grados)
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  //Calculo de la luz difusa

    //Luz Especular
    vec3 viewDir = normalize(viewPos - FragPos);    //Calculo de direccion de camara
    vec3 reflectDir = reflect(-lightDir, norm);     //Reflejo (la direccion de la luz es negativa porque va desde la luz hasta la vista no hacia el fragment como en la difusa)
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); //Calculo del componente especular (max para asegurar que no sea negativo), material.shininess es el valor del brillo cambialo para mas o menos brillo (32,64,128,etc...)
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;              //Calculo de la luz especular

    //Luz Spotlight/Foco
    //Foco suave con un cono externo que se va atenuando
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;   //Aplicamos la intensidad del foco
    specular *= intensity;

    //Calculos de atenuacion y distancia de la luz
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;   //Agregamos la luz resultante a los objetos
    FragColor = vec4(result, 1.0);
}
