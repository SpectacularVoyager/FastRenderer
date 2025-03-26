#include "Shaders/ShaderProgram.h"
#include <unordered_map>
#include <Textures/Texture.h>
class Material{
	std::unordered_map<int,void*> uniforms;
	ShaderProgram& shader;
	std::vector<TextureFile> textures;
	Material(ShaderProgram& shader):
		shader(shader)
	{}
};
