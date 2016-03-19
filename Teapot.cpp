#include "Teapot.h"
#define _USE_MATH_DEFINES
#include <math.h>

Teapot::Teapot(const GLuint& programID) : Object(), _colorIndicator(0)
{
	_color = vec4(1, 1, 1, 1);
	_programID = programID;
	float angle = -1;
	glm::mat4 xRotation = glm::rotate(_model, angle, glm::vec3(1, 0, 0));
	_model = glm::rotate(xRotation, angle, glm::vec3(0, 1, 0));
}

void Teapot::draw(const mat4 & projection, const mat4 & view)
{
	_useMVP(projection, view);

	BEGIN_OPENGL;
	
	// Get a handle for our "gMaterialColor" uniform
	GLuint materialID = glGetUniformLocation(_programID, MATERIAL_COLOR);
	glUniform4f(materialID, _color.r, _color.g, _color.b, _color.a);
	
	GLuint textureID = glGetUniformLocation(_programID, TEXTURE_SAMPLER);
	glUniform1i(textureID, 0);

	glutSolidTeapot(1.0);
	glutSwapBuffers();

	END_OPENGL;
}

void Teapot::changeColor()
{
	_colorIndicator = (_colorIndicator + 1) % 5;
	switch (_colorIndicator)
	{
		case 0:
		{
			_color = glm::vec4(1, 1, 1, 1);
		}
		break;
		case 1:
		{
			_color = glm::vec4(1, 0, 0, 1);
		}
		break;
		case 2:
		{
			_color = glm::vec4(0, 1, 0, 1);
		}
		break;
		case 3:
		{
			_color = glm::vec4(0, 0, 1, 1);
		}
		break;
		case 4:
		{
			_color = glm::vec4(1, 1, 0, 1);
		}
		break;
		
		default:
			break;
	}
}
