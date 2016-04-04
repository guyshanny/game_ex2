#include "Camera.h"
#include "Globals.h"

Camera* Camera::_instance = NULL;

Camera::Camera() : _direction(0, 0, -15),
					_position(0, 0, 15),
					_up(0, 1, 0),
					_initialPosition(_position),
					_initialDirection(_direction),
					_speed(0.2f)
{
	for (int i = 0; i < Commands::NUM_OF_COMMANDS; i++)
	{
		_commands[i] = false;
	}	
}

void Camera::init(const float & angle)
{
	_angle = angle;
	_calculateViewMatrix();
}

void Camera::update()
{
	/************************************************************************/
	/* All regular controls                                                 */
	/************************************************************************/
	if (_commands[Commands::MOVE_UP]) { _moveUpLogic(); }
	if (_commands[Commands::MOVE_DOWN]) { _moveDownLogic(); }
	if (_commands[Commands::MOVE_RIGHT]) { _moveRightLogic(); }
	if (_commands[Commands::MOVE_LEFT]) { _moveLeftLogic(); }
	if (_commands[Commands::ZOOM_IN]) { _zoomIn(); }
	if (_commands[Commands::ZOOM_OUT]) { _zoomOut(); }
}

glm::mat4 Camera::_calculateViewMatrix()
{
	_view = lookAt(_position, _position + _direction, _up);
	return _view;
}

#pragma region KeysHandling

void Camera::moveUp() { _commands[Commands::MOVE_UP] = true; }
void Camera::moveDown() { _commands[Commands::MOVE_DOWN] = true; }
void Camera::moveLeft() { _commands[Commands::MOVE_LEFT] = true; }
void Camera::moveRight() { _commands[Commands::MOVE_RIGHT] = true; }
void Camera::zoomIn() { _commands[Commands::ZOOM_IN] = true; }
void Camera::zoomOut() { _commands[Commands::ZOOM_OUT] = true; }

void Camera::_moveUpLogic()
{
	_commands[Commands::MOVE_UP] = false;

	glm::vec3 tmpPos = _position + _up*_speed;
	if (glm::abs(tmpPos.y) >= WRAPPING_CUBE_SIZE/2)
	{
		return;
	}
	_position += _up * _speed;
	_calculateViewMatrix();
}

void Camera::_moveDownLogic()
{
	_commands[Commands::MOVE_DOWN] = false;

	glm::vec3 tmpPos = _position - _up*_speed;
	if (glm::abs(tmpPos.y) >= WRAPPING_CUBE_SIZE / 2)
	{
		return;
	}
	_position -= _up * _speed;
	_calculateViewMatrix();
}

void Camera::_moveLeftLogic()
{
	_commands[Commands::MOVE_LEFT] = false;

	glm::vec3 tmpPos = _position - glm::vec3(1,0,0)*_speed;
	if (glm::abs(tmpPos.x) >= WRAPPING_CUBE_SIZE / 2)
	{
		return;
	}
	_position -= glm::vec3(1, 0, 0) * _speed;
	_calculateViewMatrix();
}

void Camera::_moveRightLogic()
{
	_commands[Commands::MOVE_RIGHT] = false;

	glm::vec3 tmpPos = _position + glm::vec3(1, 0, 0)*_speed;
	if (glm::abs(tmpPos.x) >= WRAPPING_CUBE_SIZE / 2)
	{
		return;
	}
	_position += glm::vec3(1, 0, 0) * _speed;
	_calculateViewMatrix();
}

void Camera::_zoomIn()
{
	_commands[Commands::ZOOM_IN] = false;

	glm::vec3 tmpPos = _position + glm::vec3(0.f, 0.f, -4.f)*_speed;
	if (tmpPos.z <= 5)
	{
		return;
	}
	_position = tmpPos;
	_calculateViewMatrix();
}

void Camera::_zoomOut()
{
	_commands[Commands::ZOOM_OUT] = false;

	glm::vec3 tmpPos = _position + glm::vec3(0.f, 0.f, 4.f)*_speed;
	if (tmpPos.z > (_initialPosition + glm::vec3(0.f, 0.f, 30.f)).z)
	{
		return;
	}
	_position = tmpPos;
	_calculateViewMatrix();
}

#pragma endregion


