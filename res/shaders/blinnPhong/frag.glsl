#version 330 core
out vec4 FragColor;

in vec2 tex;
in vec3 norm;
uniform sampler2D Texture;
float near = 0.1; 
float far  = 100.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{    
	float ambientStrength = 0.1;
    vec3 ambient = vec3(1.0);
    FragColor = vec4(texture(Texture, tex).xyz*ambient,1.0);
} 
