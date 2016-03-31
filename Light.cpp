#include "Light.h"

Light::Light(const glm::vec3& position, const glm::vec3& direction, const glm::vec4 color) :
MinimalObject(position, color), _movingSpeed(0.5f), _direction(direction), _coneOfLight(3.01f), _attenuation(0.5f)
{
}

void Light::move(int dir)
{
	switch (dir)
	{
		case GLUT_KEY_LEFT:
			_position.x -= _movingSpeed;
			break;
		case GLUT_KEY_RIGHT:
			_position.x += _movingSpeed;
			break;
		case GLUT_KEY_UP:
			_position.y += _movingSpeed;
			break;
		case GLUT_KEY_DOWN:
			_position.y -= _movingSpeed;
			break;
		case GLUT_KEY_PAGE_UP:
			_position.z -= _movingSpeed;
			break;
		case GLUT_KEY_PAGE_DOWN:
			_position.z += _movingSpeed;
			break;
	}
	//printf("lightPos %f %f %f\n", _lightPos.x, _lightPos.y, _lightPos.z);
}
