#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;   //Posicion del fragment real
out vec3 Normal;    //Normales al fragment
out vec2 TexCoords; //Coordenadas de textura al fragment
out vec4 FragPosLightSpace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));              //Posicion real del fragment
    Normal = mat3(transpose(inverse(model))) * aNormal;   //Para que al escalar de manera uniforme las normales no se rompan
    TexCoords = aTexCoords;                               //Texturas coordeandas
    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
    gl_Position = projection * view * vec4(FragPos, 1.0); //El model ya no se pasa aqui
}
