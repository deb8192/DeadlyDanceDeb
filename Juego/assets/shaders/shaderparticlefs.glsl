#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D sprite;

void main()
{
    vec4 texColor = texture(sprite, TexCoord);
    if(texColor.a < 0.1)
        discard;
	FragColor = texColor * ourColor;
}
