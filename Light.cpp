#include "Light.h"

Light::Light(const glm::vec3& position, 
			 const glm::vec3& direction, 
			 const glm::vec4 color) :
										MinimalObject(position, color), 
										_movingSpeed(0.1f),
										_direction(direction), 
										_coneOfLight(3.01f), 
										_attenuation(1.0f)
{
}

void Light::moveUsingArrows(int key)
{
	float speed = _movingSpeed / 5;
	switch (key)
	{
		case GLUT_KEY_LEFT:
			_direction.x -= speed;
			break;
		case GLUT_KEY_RIGHT:
			_direction.x += speed;
			break;
		case GLUT_KEY_UP:
			_direction.y += speed;
			break;
		case GLUT_KEY_DOWN:
			_direction.y -= speed;
			break;
		case GLUT_KEY_PAGE_UP:
			_position.z -= _movingSpeed * 10;
			break;
		case GLUT_KEY_PAGE_DOWN:
			_position.z += _movingSpeed * 10;
			break;
	}
	//printf("lightPos %f %f %f\n", _position.x, _position.y, _position.z);
}

glm::vec2 Light::_toWorld(const int& x, const int& y)
{
	const float maxBoundary = 0.5f;
	const float minBoundary = 0.5f;

	float xnorm = ((float)x <= WINDOW_WIDTH / 2.f) ? -(WINDOW_WIDTH / 2.f - (float)x) : (float)x - WINDOW_WIDTH / 2.f;
	float ynorm = ((float)y <= WINDOW_HEIGHT / 2.f) ? WINDOW_HEIGHT / 2.f - (float)y : -((float)y - WINDOW_HEIGHT / 2.f);

	xnorm = (xnorm / (WINDOW_WIDTH / 2.f)) / 2.f;
	ynorm = (ynorm / (WINDOW_HEIGHT / 2.f)) / 2.f;

	return glm::vec2(xnorm, ynorm);
}

void Light::moveUsingMouse(const int & x, const int & y)
{
	glm::vec2 screenToWorldCoords = _toWorld(x, y);	
  	_direction.x = screenToWorldCoords.x;
  	_direction.y = screenToWorldCoords.y;
}
