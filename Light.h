#pragma once

#include "MinimalObject.h"

class Light : public MinimalObject
{
public:
	Light(const GLuint& programID, const glm::vec3& position, const glm::vec4 color);

	void update() {};
	void draw(const glm::mat4& projection, const glm::mat4& view) {};
	void init() {};

private:
	glm::vec4 _position;
	glm::vec4 _color;
};