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

void Light::move(int dir)
{
	switch (dir)
	{
		case GLUT_KEY_LEFT:
			_direction.x -= _movingSpeed;
			break;
		case GLUT_KEY_RIGHT:
			_direction.x += _movingSpeed;
			break;
		case GLUT_KEY_UP:
			_direction.y += _movingSpeed;
			break;
		case GLUT_KEY_DOWN:
			_direction.y -= _movingSpeed;
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
