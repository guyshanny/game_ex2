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


World::World() :
	_world(1.0f)
{
	// Projection matrix : 45?Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	_projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	
	// Camera handling
	_camera = Camera::instance();
	_camera->setPosition(glm::vec3(0, 0, 15));
	_camera->setDirection(glm::vec3(0, 0, 0));
	_camera->setUp(glm::vec3(0, 1, 0));
}

World::~World()
{
	for (Object* object : _objects)
	{
		delete object;
	}
	_objects.clear();
}

#pragma region Init
void World::init()
{
}

void World::_createSceneObjects()
{
}
#pragma endregion

#pragma region Draw
void World::draw()
{
// 	_camera->update();
// 	mat4 view = _camera->getViewMatrix();
// 	// Drawing the world
// 	_drawWorld(view);
// 
// 	// Drawing scene objects
// 	for (Object* object : _objects)
// 	{
// 		object->update();
// 		object->draw(_projection, view);
// 	}
}

void World::_drawWorld(const mat4& view)
{
}
#pragma endregion

#pragma region KeysHandling
void World::moveForwardKeyPressed()
{
	_camera->moveForward();
}

void World::moveBackwardKeyPressed()
{
	_camera->moveBackward();
}

void World::turnLeftKeyPressed()
{
	_camera->turnLeft();
}

void World::turnRightKeyPressed()
{
	_camera->turnRight();
}

#pragma endregion

void World::resize(int width, int height)
{
	_width = (float)width;
	_height = (float)height;
	_offsetX = 0;
	_offsetY = 0;
}
