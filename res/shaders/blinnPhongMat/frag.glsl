#version 330 core
out vec4 FragColor;

in vec3 pos;
in vec2 tex;
in vec3 norm;
uniform sampler2D Texture;
  
uniform vec3 cameraPos;

void main()
{    
	vec3 lightPos=vec3(0,2,0);

	vec3 _norm=normalize(norm);
	vec3 lightDir=normalize(lightPos-pos);
	vec3 viewDir=normalize(cameraPos-pos);
	vec3 halfway=normalize(lightDir+viewDir);

	float diffuse=max(dot(halfway,_norm),0);
	float spec = pow(max(dot(_norm, halfway), 0.0), 32);

	float dist=length(lightPos-pos);
	float atten=8/(dist*dist);

	vec3 tex=texture(Texture, tex).xyz*(spec+diffuse)*atten;
	FragColor=vec4(vec3(tex),1.0);
} 
