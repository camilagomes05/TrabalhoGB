#version 450 core
in vec4 ourColor;
in vec2 TexCoord;

out vec4 color;

// pixels da textura
uniform sampler2D tex1;

void main()
{
    color = texture(tex1, TexCoord);

    color.r = color.b * 2.7;
    color.g = color.b * 1.7;
}
