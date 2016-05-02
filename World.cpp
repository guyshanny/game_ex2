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
	_objects.push_back((new Teapot("shaders\\phong_teapotV3.3.vert", "shaders\\phongV3.3.frag", "textures\\teapot.jpg", "meshes\\teapot.obj")));
	_objects.push_back((new Wall("shaders\\phong_wallV3.3.vert", "shaders\\phongV3.3.frag", WRAPPING_CUBE_SIZE, WRAPPING_CUBE_SIZE, "textures\\wall.bmp")));

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

void World::forwardKeyPressed() { _camera->moveUp(); }
void World::backwardKeyPressed() { _camera->moveDown(); }
void World::turnRightKeyPressed() { _camera->moveRight(); }
void World::turnLeftKeyPressed() { _camera->moveLeft(); }
void World::changeColorKeyPressed() 
{
	Teapot* teapot = NULL;
	for (Object* obj : _objects)
	{
		teapot = dynamic_cast<Teapot*>(obj);
		if (NULL != teapot)
		{
			break;
		}
	}

	if (NULL != teapot)
	{
		teapot->changeColor();
	}
}

void World::moveLightUsingArrows(int key)
{
	_light->moveUsingArrows(key);
}

void World::resetKeyPressed()
{

}

#pragma endregion

#pragma region MouseHandling

void World::mouseLeftDown(const int & x, const int & y)
{
}

void World::mouseLeftUp(const int & x, const int & y)
{
}

void World::mouseWheelForward(const int & x, const int & y)
{
	_camera->zoomIn();
}

void World::mouseWheelBackWard()
{
	_camera->zoomOut();
}

void World::moveLightUsingMouse(const int & x, const int & y)
{
	_light->moveUsingMouse(x, y);
}



#pragma endregion


#pragma region Game events

void World::flickerLight(const bool & mode)
{
	Teapot* teapot = NULL;
	Wall* wall = NULL;
	for (Object* obj : _objects)
	{
		if (NULL == teapot)
		{
			teapot = dynamic_cast<Teapot*>(obj);
		}
		if (NULL == wall)
		{
			wall = dynamic_cast<Wall*>(obj);
		}
	}
	teapot->flickerLight(mode);
	wall->flickerLight(mode);
}

#pragma endregion

void World::resize(int width, int height)
{
	Globals::WINDOW_WIDTH = width;
	Globals::WINDOW_HEIGHT = height;
}

