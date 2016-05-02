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
	void reset();
	void moveUsingArrows(int key);
	void moveUsingMouse(const int& x, const int& y);
	glm::vec3 getDirection() { return _direction; }

private:
	glm::vec3 _direction;
	float _coneOfLight; //degrees
	float _attenuation;
	float _movingSpeed;

	glm::vec3 _initialDirection;
	float _initialConeOfLight;
	glm::vec3 _initialConeDirection;
	float _initialAttenuation;
	float _initialMovingSpeed;

	glm::vec2 _toWorld(const int& x, const int& y);
};