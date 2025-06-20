#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 _tex;

out vec2 tex;
out vec3 pos;
uniform mat4 projection;
uniform mat4 view;
void main()
{
    // gl_Position =projection*view*vec4(aPos.x, aPos.y, aPos.z, 1.0);
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	tex=_tex;
	pos=aPos;
}
