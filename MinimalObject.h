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
	virtual void draw(const glm::mat4& projection, const glm::mat4& view) = 0;
	virtual void init() = 0;

	glm::vec3 getPosition() { return _position; }
	glm::vec3 getDirection() { return _direction; }

protected:
	MinimalObject(const GLuint& programID,
		const glm::vec3& position,
		const glm::vec3& direction,
		const glm::vec4& color) :
		_programID(programID), _position(position), _direction(direction), _color(color) {};

	GLuint _programID;

	glm::vec3 _position;
	glm::vec3 _direction;
	glm::vec4 _color;
};