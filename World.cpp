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

#include <math.h>

// Objects
#include "Teapot.h"
#include "Wall.h"

World::World()
{
	// Projection matrix : 45?Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	_projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	
	// Camera handling
	_camera = Camera::instance();

	// Light object
	_light = new Light(glm::vec3(2, 2, 5), glm::vec3(0, 0, 1), glm::vec4(1, 1, 0.88, 1));

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

	delete _camera;
 	delete _light;
}

#pragma region Init
void World::init()
{
	_camera->init(0);
	_light->init();
	for (Object* object : _objects)
	{
		object->init();
	}
}

void World::_createSceneObjects()
{
	_objects.push_back((Object*)(new Teapot("shaders\\þþphong_teapotV3.3.vert", "shaders\\þþphong_teapotV3.3.frag", "textures\\teapot.jpg", "meshes\\teapot.obj")));
	_objects.push_back((Object*)(new Wall("shaders\\phong_wallV3.3.vert", "shaders\\phong_wallV3.3.frag", 100, 100, "textures\\wall.bmp")));
}
#pragma endregion


void World::update()
{
	_camera->update();
	for (Object* object : _objects)
	{
		object->update();
	}
}

#pragma region Draw

void World::draw()
{
	// Camera handling
	glm::mat4 view = _camera->getViewMatrix();

	// Drawing scene objects
	for (Object* object : _objects)
	{
		object->draw(_projection, view, _camera->getPosition(), _light);
	}
}

#pragma endregion

#pragma region KeysHandling

void World::forwardKeyPressed() { _camera->moveForward(); }
void World::backwardKeyPressed() { _camera->moveBackward(); }
void World::turnRightKeyPressed() { _camera->turnRight(); }
void World::turnLeftKeyPressed() { _camera->turnLeft(); }
void World::changeColorKeyPressed() 
{
	//Teapot* teapot = dynamic_cast<Teapot*>(_objects.front()); // NOT WORKING!!
	Teapot* teapot = (Teapot*)(_objects.front());
	teapot->changeColor();
}
void World::moveLight(int key)
{
	_light->move(key);
}

#pragma endregion

void World::resize(int width, int height)
{
	_width = (float)width;
	_height = (float)height;
	_offsetX = 0;
	_offsetY = 0;
}

