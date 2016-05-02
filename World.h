//
//  Model.h
//  cg-projects
//
//  Created by HUJI Computer Graphics course staff, 2013.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // for glm::value_ptr
#include <vector>
#include "Camera.h"
#include "Light.h"
#include "Object.h"

#include <iostream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include <GL/gl.h>
#endif

class World 
{
	// MVP matrices
	glm::mat4 _projection;

	// Scene objects
	std::vector<Object*> _objects;
	Camera* _camera;
 	Light* _light;
	void _createSceneObjects();

	template <typename T>
	T* _getObject()
	{
		T* wantedObj = NULL;
		for (Object* obj : _objects)
		{
			wantedObj = dynamic_cast<T*>(obj);
			if (NULL != wantedObj)
			{
				return wantedObj;
			}
		}
		return NULL;
	}

public:
	World();
	virtual ~World();
	void init();
	void draw();
	void update();
	void resize(int width, int height);
	void loadShaders();

	// Keyboard handling
	void forwardKeyPressed();
	void backwardKeyPressed();
	void turnRightKeyPressed();
	void turnLeftKeyPressed();
	void changeColorKeyPressed();
	void moveLightUsingArrows(int key);
	void resetKeyPressed();

	// Mouse handling
	void mouseLeftDown(const int& x, const int& y);
	void mouseLeftUp(const int& x, const int& y);
	void mouseWheelForward(const int& x, const int& y);
	void mouseWheelBackWard();
	void moveLightUsingMouse(const int& x, const int& y);

	// Events
	void flickerLight(const bool& mode);
	glm::vec3 getDestPos();

};
