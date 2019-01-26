#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 transform;   //uniform que recibe la matriz de transformacion

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);    //multiplicamos la matriz de transformacion
    ourColor = aColor;
    TexCoord = aTexCoord;
}
