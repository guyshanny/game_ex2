#ifndef __OBJECT_H
#define __OBJECT_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "Globals.h"
#include "GlobalFunctions.h"

#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

using namespace glm;

class Object
{
protected:
	// Shaders' stuff
	GLuint _vao, _vbo;
	GLuint _programID;

	// Position stuff
	glm::mat4 _model;
	vec3 _position;
	vec3 _direction;
	vec3 _initialPosition;
	vec3 _initialDirection;

	// Object's properties
	glm::vec4 _color;
	GLuint _textureID;
	const std::string _textureImg;

	Object(const std::string textureIMG);
	Object(const GLuint& programID, 
		   const vec3 & position, 
		   const vec3 & direction, 
		   const GLuint& vao, 
		   const GLint& vbo,
		   const std::string textureIMG);

	void _useMVP(const mat4& projection, const mat4& view);

public:
	virtual ~Object() {};

	// Updates the object's params if needed (does in each render frame)
	virtual void update() = 0;

	// Draws the object
	virtual void draw(const mat4& projection, const mat4& view) = 0;
	virtual void init() = 0;

	vec3 getPosition() { return _position; }
	vec3 getDirection() { return _direction; }
	mat4 getModel() { return _model; }
};

#endif
