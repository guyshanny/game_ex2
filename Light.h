#pragma once

#include "MinimalObject.h"

class Light : public MinimalObject
{
public:
	Light(const glm::vec3& position, 
		  const glm::vec3& direction, 
		  const glm::vec4 color);

	void update() {};
	void draw(const glm::mat4& projection, const glm::mat4& view) {};
	void init() {};
	void move(int dir);
	glm::vec3 getDirection() { return _direction; }

private:
	glm::vec3 _direction;
	float _coneOfLight; //degrees
	glm::vec3 _coneDirection;
	float _attenuation;
	float _movingSpeed;
};