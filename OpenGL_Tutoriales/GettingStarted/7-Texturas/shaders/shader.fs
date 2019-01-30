#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //FragColor = texture(texture1, TexCoord);                                    //Una textura
    //FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);              //Junta textura con el color
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);    //Unir con mas texturas a la vez (0.2 es 80% del primero y 20% del segundo)
}
