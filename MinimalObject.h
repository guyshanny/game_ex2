#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "Globals.h"

#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

class MinimalObject
{
public:
 	virtual ~MinimalObject() {};

	// Updates the object's params if needed (does in each render frame)
	virtual void update() = 0;

	// Draws the object
	virtual void init() = 0;

	glm::vec3 getPosition() { return _position; }
	glm::vec4 getColor() { return _color; }

protected:
	MinimalObject(const glm::vec3& position, const glm::vec4& color) :
		_position(position), _color(color), _initialPosition(position), _initialColor(color)
	{
	};

	GLuint _programID;

	glm::vec3 _position;
	glm::vec4 _color;
	glm::vec3 _initialPosition;
	glm::vec4 _initialColor;
};