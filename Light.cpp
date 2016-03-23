#include "Light.h"

Light::Light(const GLuint& programID, const glm::vec3 & position, const glm::vec4 color) :
	MinimalObject(programID, position, glm::vec3(0.0f), color)
{
}
