#pragma once

#include "Object.h"
#include <vector>
#include <string>

class Wall : public Object
{
public:
	Wall(const char* vShaderFile,
		 const char* fShaderFile,
		 const float& width,
		 const float& height,
		 const std::string textureIMG);

	void draw(const glm::mat4& projection, const glm::mat4& view,
			  const glm::vec3 camPos, Light* light);
	void update() {}
	void init();

private:
	float _width;
	float _height;
};
