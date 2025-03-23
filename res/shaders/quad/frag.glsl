#version 330 core
out vec4 FragColor;

in vec2 tex;
in vec3 pos;
uniform sampler2D Texture;

void main()
{
    FragColor = vec4(vec3(1.0)-vec3(texture(Texture, tex)),1.0);
} 
