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

World::World(const GLuint& programID) : _programID(programID), _lightPos(4, 4, 4, 1)
{
	// Projection matrix : 45?Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	_projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	
	// Camera handling
	_camera = Camera::instance();

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
	_camera->init(0);
	for (Object* object : _objects)
	{
		object->init();
	}
}

void World::_createSceneObjects()
{
 	_objects.push_back((Object*)(new Teapot(_programID, "textures\\teapot.jpg", "meshes\\teapotMesh.off")));
	_objects.push_back((Object*)(new Wall(_programID, 5, 5, "textures\\wall.bmp")));
}
#pragma endregion

#pragma region Draw
void World::draw()
{
	// Camera handling
	_camera->update();
	glm::mat4 view = _camera->getViewMatrix();

	// Drawing the world
	_drawWorld(view);

	// Drawing scene objects
	for (Object* object : _objects)
	{
		object->update();
		object->draw(_projection, view);
	}
}

void World::_drawWorld(const glm::mat4& view)
{
	BEGIN_OPENGL
	{
		// Get a handle for our "gEyePosition" uniform
		glm::vec3 cameraPosition = _camera->getPosition();
		GLuint cameraID = glGetUniformLocation(_programID, "gEyePosition");
		glUniform3f(cameraID, cameraPosition.x, cameraPosition.y, cameraPosition.z);
		// Get a handle for our "gLightPosition" uniform
		GLuint lightID = glGetUniformLocation(_programID, "gLightPosition");
		glUniform4f(lightID, _lightPos.x, _lightPos.y, _lightPos.z, _lightPos.w);
	}
	END_OPENGL
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
void World::moveLight(int key)
{
	switch (key)
	{
		case GLUT_KEY_LEFT:
			_lightPos[0] -= 0.5f;
			break;
		case GLUT_KEY_RIGHT:
			_lightPos[0] += 0.5f;
			break;
		case GLUT_KEY_UP:
			_lightPos[1] += 0.5f;
			break;
		case GLUT_KEY_DOWN:
			_lightPos[1] -= 0.5f;
			break;
		case GLUT_KEY_PAGE_UP:
			_lightPos[2] -= 0.5f;
			break;
		case GLUT_KEY_PAGE_DOWN:
			_lightPos[2] += 0.5f;
			break;
	}
	//printf("lightPos %f %f %f\n", _lightPos[0], _lightPos[1], _lightPos[2]);
}

#pragma endregion

void World::resize(int width, int height)
{
	_width = (float)width;
	_height = (float)height;
	_offsetX = 0;
	_offsetY = 0;
}

