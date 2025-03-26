#pragma once

#include "glm/glm.hpp"
#include "Shaders/ShaderProgram.h"
class Renderable{
public:
	virtual glm::mat4& getTransform()=0;
	virtual void Bind()=0;
	virtual ShaderProgram& GetShader()=0;
	virtual void Draw()=0;
};
