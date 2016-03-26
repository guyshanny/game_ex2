#pragma once

#include "Object.h"
#include <vector>
#include <string>

class Wall : Object
{
public:
	Wall(const GLuint& programID, 
		 const float& width,
		 const float& height,
		 const std::string textureIMG);

	void draw(const glm::mat4& projection, const glm::mat4& view);
	void update() {}
	void init();

private:
	float _width;
	float _height;
};
