//
//  Model.cpp
//  cg-projects
//
//  Created by HUJI Computer Graphics course staff, 2013.
//

#include "World.h"

#include <GL/glew.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include <GL/gl.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/matrix_transform.hpp"

#define SHADERS_DIR "shaders/"

#define _USE_MATH_DEFINES
#include <math.h>

// Objects
#include "Teapot.h"

World::World(const GLuint& programID, const GLuint& texture) : _programID(programID),
															   _texture(texture)
{
	// Projection matrix : 45?Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	_projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	
	// Camera handling
	_camera = Camera::instance();
	_camera->setPosition(glm::vec3(0, 0, 15));
	_camera->setDirection(glm::vec3(0, 0, 0));
	_camera->setUp(glm::vec3(0, 1, 0));

	// Create scene objects
	_createSceneObjects();
}

World::~World()
{
	// Objects
	for (Object* object : _objects)
	{
		delete object;
	}
	_objects.clear();

	// Camera
	delete _camera;
}

#pragma region Init
void World::init()
{
}

void World::_createSceneObjects()
{
	_objects.push_back((Object*)(new Teapot(_programID)));

}
#pragma endregion

#pragma region Draw
void World::draw()
{
	// Camera handling
	_camera->update();
	mat4 view = _camera->getViewMatrix();

	// Drawing the world
	_drawWorld(view);

	// Drawing scene objects
	for (Object* object : _objects)
	{
		object->update();
		object->draw(_projection, view);
	}
}

void World::_drawWorld(const mat4& view)
{
}
#pragma endregion

#pragma region KeysHandling
void World::forwardKeyPressed() { _camera->moveForward(); }
void World::backwardKeyPressed() { _camera->moveBackward(); }
void World::turnRightKeyPressed() { _camera->turnRight(); }
void World::turnLeftKeyPressed() { _camera->turnLeft(); }
void World::changeColorKeyPressed() 
{
	Teapot* teapot = dynamic_cast<Teapot*>(_objects.front());
	teapot->changeColor();
}
#pragma endregion

void World::resize(int width, int height)
{
	_width = (float)width;
	_height = (float)height;
	_offsetX = 0;
	_offsetY = 0;
}

