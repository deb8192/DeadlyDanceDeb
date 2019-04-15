#version 330 core
out vec4 FragColor;

uniform vec3 objectColor; //Color del objeto
uniform vec3 lightColor;  //Color de la luz

void main()
{
    FragColor = vec4(lightColor * objectColor, 1.0);
}
