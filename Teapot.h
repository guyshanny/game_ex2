#ifndef __TEAPOT_H
#define __TEAPOT_H

#include "Object.h"

// Shader's uniform's variables
#define TEXTURE_IMG "textures\teapot.jpg"

class Teapot : Object
{
public:
	Teapot(const GLuint& programID, const std::string textureIMG);

	void draw(const mat4& projection, const mat4& view);
	void update() {}
	void init() {}

	void changeColor();
private:
	int _colorIndicator;
};

#endif
