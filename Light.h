#pragma once

#include "MinimalObject.h"

class Light : public MinimalObject
{
public:
	Light(const GLuint& programID, const glm::vec3& position, const glm::vec4 color);

	void update() {};
	void draw(const glm::mat4& projection, const glm::mat4& view) {};
	void init() {};
	void move(int dir);

private:
	float _movingSpeed;
};