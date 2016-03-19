//
//  Model.h
//  cg-projects
//
//  Created by HUJI Computer Graphics course staff, 2013.
//

#ifndef __WORLD__
#define __WORLD__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // for glm::value_ptr
#include <vector>
#include "Camera.h"
#include "Object.h"

using namespace glm;

#include <iostream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include <GL/gl.h>
#endif

class World {
	// Attribute handle:
	GLint _posAttrib;

	// Program params
	GLuint _programID;

	// View port frame:
	float _width, _height, _offsetX, _offsetY;

	// MVP matrices
	mat4 _projection;

	// Camera variables
	Camera* _camera;

	// Scene objects
	std::vector<Object*> _objects;
	void _createSceneObjects();

	void _drawWorld(const mat4& view);

public:
	World(const GLuint& programID);
	virtual ~World();
	void init();
	void draw();
	void resize(int width, int height);

	// Keyboard handling
	void forwardKeyPressed();
	void backwardKeyPressed();
	void turnRightKeyPressed();
	void turnLeftKeyPressed();
	void changeColorKeyPressed();

	// Getters&Setters
	GLuint getProgramID() { return _programID; }
	Camera* getCamera() { return _camera; }

};

#endif
