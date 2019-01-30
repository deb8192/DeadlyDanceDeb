#version 330 core
out vec4 FragColor;

uniform vec3 objectColor; //Color del objeto
uniform vec3 lightColor;  //Color de la luz
uniform vec3 lightPos;    //Posicion de luz para calcular luz difusa
uniform vec3 viewPos;     //Posicion de la camara para calcular la luz especular

in vec3 Normal;  //Recibimos las normales del vertex
in vec3 FragPos; //Recibimos la posicion del fragment actual

void main()
{
    //Luz Ambiental
    float ambientStrength = 0.1;                    //Fuerza de la luz ambiental
    vec3 ambient = ambientStrength * lightColor;    //Calculo de la luz ambiental

    //Luz Difusa
    vec3 norm = normalize(Normal);                  //normalizar
    vec3 lightDir = normalize(lightPos - FragPos);  //la direccion de la luz es la diferencia entre el vector de posicion de la luz y el vector de posicion del fragment
    float diff = max(dot(norm, lightDir), 0.0);     //impacto difuso real (usamos max para que el color nunca sea negativo si sube de 90 grados)
    vec3 diffuse = diff * lightColor;               //Calculo de la luz difusa

    //Luz Especular
    float specularStrength = 0.5;                   //Fuerza de la luz especular
    vec3 viewDir = normalize(viewPos - FragPos);    //Calculo de direccion de camara
    vec3 reflectDir = reflect(-lightDir, norm);     //Reflejo (la direccion de la luz es negativa porque va desde la luz hasta la vista no hacia el fragment como en la difusa)
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);     //Calculo del componente especular (max para asegurar que no sea negativo), 32 es el valor del brillo cambialo para mas o menos brillo (32,64,128,etc...)
    vec3 specular = specularStrength * spec * lightColor;         //Calculo de la luz especular

    vec3 result = (ambient + diffuse + specular) * objectColor;   //Agregamos la luz resultante a los objetos
    FragColor = vec4(result, 1.0);
}
