#version 330 core
out vec4 FragColor;

in vec2 tex;
in vec3 norm;
uniform sampler2D Texture;

uniform samplerCube skybox;

void main()
{
    FragColor = texture(Texture, tex);
	FragColor = vec4(norm,1.0);
} 
