#ifndef __CAMERA_H
#define __CAMERA_H


#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

// GLM headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // for glm::value_ptr

using namespace glm;

#include <iostream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include <GL/gl.h>
#endif

class Camera
{
public:
	// Options
	enum Commands
	{
		MOVE_FORWARD,
		MOVE_BACKWARD,
		TURN_LEFT,
		TURN_RIGHT,

		// Number of commands
		NUM_OF_COMMANDS = 4
	};

	static Camera* instance()
	{
		if (NULL == _instance)
		{
			_instance = new Camera();
		}
		return _instance;
	}
	void init(const float& angle);
	void update();

	// Key functions
	void moveForward();
	void moveBackward();
	void turnLeft();
	void turnRight();

	// Getters & setters
	mat4 getViewMatrix() { return _view; }
	vec3 getPosition() { return _position; }

private:
	vec3 _direction;
	vec3 _position;
	vec3 _up;
	vec3 _initialDirection;
	vec3 _initialPosition;

	mat4 _view;

	// Moving camera properties
	float _speed;
	float _angle;

	// Commands
	bool _commands[Commands::NUM_OF_COMMANDS];
	void _moveForwardLogic();
	void _moveBackwardLogic();
	void _turnLeftLogic();
	void _turnRightLogic();

	Camera();
	static Camera* _instance;

	mat4 Camera::_calculateViewMatrix();
};

#endif