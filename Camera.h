#pragma  once


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
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		ZOOM_IN,
		ZOOM_OUT,

		// Number of commands
		NUM_OF_COMMANDS = 6
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
	void reset();

	// Key functions
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void zoomIn();
	void zoomOut();

	// Getters & setters
	glm::mat4 getViewMatrix() { return _view; }
	glm::vec3 getPosition() { return _position; }

private:
	glm::vec3 _direction;
	glm::vec3 _position;
	glm::vec3 _up;
	glm::vec3 _initialDirection;
	glm::vec3 _initialPosition;

	glm::mat4 _view;

	// Moving camera properties
	float _speed;
	float _angle;

	// Commands
	bool _commands[Commands::NUM_OF_COMMANDS];
	void _moveUpLogic();
	void _moveDownLogic();
	void _moveLeftLogic();
	void _moveRightLogic();
	void _zoomIn();
	void _zoomOut();

	Camera();
	static Camera* _instance;

	glm::mat4 Camera::_calculateViewMatrix();
};