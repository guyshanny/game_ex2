#include "Camera.h"
#include "Globals.h"

Camera* Camera::_instance = NULL;

Camera::Camera() : _direction(0.0f, 0.0f, 1.0f),
					_position(0.0f, 0.0f, 15.0f),
					_up(0.0f, 1.0f, 0.0f),
					_initialPosition(_position),
					_initialDirection(_direction),
					_speed(0.1f)
{
}

void Camera::init(const float & angle, const float & windowBoundary)
{
	_angle = angle;
	_calculateViewMatrix();
}

void Camera::update()
{
	/************************************************************************/
	/* All regular controls                                                 */
	/************************************************************************/
	if (_commands[Commands::MOVE_FORWARD]) { _moveForwardLogic(); }
	if (_commands[Commands::MOVE_BACKWARD]) { _moveBackwardLogic(); }
	if (_commands[Commands::TURN_RIGHT]) { _turnRightLogic(); }
	if (_commands[Commands::TURN_LEFT]) { _turnLeftLogic(); }
}

mat4 Camera::_calculateViewMatrix()
{
	_view = lookAt(_position, _position + _direction, _up);
	return _view;
}

#pragma region KeysHandling

void Camera::moveForward() { _commands[Commands::MOVE_FORWARD] = true; }
void Camera::moveBackward() { _commands[Commands::MOVE_BACKWARD] = true; }
void Camera::turnLeft() { _commands[Commands::TURN_LEFT] = true; }
void Camera::turnRight() { _commands[Commands::TURN_RIGHT] = true; }

void Camera::_moveForwardLogic()
{
	_commands[Commands::MOVE_FORWARD] = false;

	vec3 tmpPos = _position + _direction*_speed;
	if (glm::abs(tmpPos.x) >= WINDOW_BOUNDARY.x || glm::abs(tmpPos.z) >= WINDOW_BOUNDARY.z)
	{
		return;
	}

	_position += _direction * _speed;
	_calculateViewMatrix();
}

void Camera::_moveBackwardLogic()
{
	_commands[Commands::MOVE_BACKWARD] = false;

	vec3 tmpPos = _position - _direction*_speed;
	if (glm::abs(tmpPos.x) >= WINDOW_BOUNDARY.x || glm::abs(tmpPos.z) >= WINDOW_BOUNDARY.z)
	{
		return;
	}

	_position -= _direction * _speed;
	_calculateViewMatrix();
}

void Camera::_turnLeftLogic()
{
	_commands[Commands::TURN_LEFT] = false;

	_angle += _speed;
	_direction.x = glm::sin(_angle);
	_direction.z = -glm::cos(_angle);
	_calculateViewMatrix();
}

void Camera::_turnRightLogic()
{
	_commands[Commands::TURN_RIGHT] = false;

	_angle -= _speed;
	_direction.x = glm::sin(_angle);
	_direction.z = -glm::cos(_angle);
	_calculateViewMatrix();
}
#pragma endregion


