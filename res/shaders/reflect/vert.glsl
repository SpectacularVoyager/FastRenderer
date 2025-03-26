#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 _tex;
layout (location = 1) in vec3 aNorm;

out vec3 pos;
out vec2 tex;
out vec3 norm;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;


void main()
{
    gl_Position =projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);

	tex=_tex;
	norm=aNorm;
	pos=vec3(model * vec4(aPos, 1.0));
}
