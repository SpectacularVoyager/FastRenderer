#include "../Buffer/Buffer.h"
#include "../Shaders/ShaderProgram.h"
class Drawable{
public:
	Buffer vertices;
	Buffer indices;
	VertexLayout layout;
	ShaderProgram program;
};
