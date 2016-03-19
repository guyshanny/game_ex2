#ifndef __TEAPOT_H
#define __TEAPOT_H

#include "Object.h"

// Shader's uniform's variables
#define MATERIAL_COLOR "gMaterialColor"
#define TEXTURE_SAMPLER "gTextureSampler"

class Teapot : Object
{
public:
	Teapot(const GLuint& programID);

	void draw(const mat4& projection, const mat4& view);
	void update() {}
	void init() {}

	void changeColor();
private:
	int _colorIndicator;
};

#endif
