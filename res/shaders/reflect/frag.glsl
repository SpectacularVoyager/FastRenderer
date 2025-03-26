#version 330 core
out vec4 FragColor;

in vec3 pos;
in vec2 tex;
in vec3 norm;
uniform sampler2D Texture;
  
uniform vec3 cameraPos;

uniform samplerCube skybox;

void main()
{    
    vec3 I = normalize(pos - cameraPos);
    vec3 R = reflect(I, normalize(norm));
	FragColor = vec4(texture(skybox, R).xyz,1.0);
} 
