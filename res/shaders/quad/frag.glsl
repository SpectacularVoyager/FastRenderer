#version 330 core
out vec4 FragColor;

in vec2 tex;
in vec3 pos;
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
	float r=texture(Texture,tex).r;
	FragColor=vec4(vec3(pow(r,4)),1.0);
} 
