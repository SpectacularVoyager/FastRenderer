#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 _tex;
layout (location = 2) in vec2 aNorm;

out vec2 tex;
out vec2 norm;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
void main()
{
    gl_Position =projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	norm=aNorm;
	tex=_tex;
}
