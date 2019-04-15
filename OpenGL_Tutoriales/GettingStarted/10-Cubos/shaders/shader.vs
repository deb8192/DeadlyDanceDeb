#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;

//out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 model;         //transformacion
uniform mat4 view;          //colocar vista
uniform mat4 projection;    //cplicar proyeccion

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);    //Todo multiplicado
    //ourColor = aColor;
    TexCoord = aTexCoord;
}
