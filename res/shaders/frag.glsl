#version 330 core
out vec4 FragColor;

in vec2 tex;
uniform sampler2D Texture;

void main()
{
    FragColor = texture(Texture, tex);
} 
