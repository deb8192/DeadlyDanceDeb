#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 model;         //transformacion
uniform mat4 view;          //colocar vista
uniform mat4 projection;    //cplicar proyeccion

uniform vec2 scale;
uniform vec3 localcoord;

void main()
{
    mat4 modelView = view * model;

    modelView[0][0] = scale.x;
    modelView[0][1] = 0.0;
    modelView[0][2] = 0.0;

    modelView[1][0] = 0.0;
    modelView[1][1] = scale.y;
    modelView[1][2] = 0.0;

    modelView[2][0] = 0.0;
    modelView[2][1] = 0.0;
    modelView[2][2] = 1.0;

    vec3 newpos = vec3(aPos.x + localcoord.x, aPos.y + localcoord.y, aPos.z + localcoord.z/1000);
    vec4 P = modelView * vec4(newpos, 1.0);
    gl_Position = projection * P;

    ourColor = aColor;
    TexCoord = aTexCoord;
}
