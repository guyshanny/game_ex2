#include "Object.h"


Object::Object(const GLuint& programID,
				const glm::vec3 & position,
				const glm::vec3 & direction,
				const glm::vec4 & color,
				const std::string textureIMG = "") :
	MinimalObject(programID, position, direction, color),
	_textureImg(textureIMG)
{
	if (NULL < _textureImg.size())
	{
		_textureID = InitTexture(_textureImg.c_str());
	}
}

void Object::_useMVP(const glm::mat4 & projection, const glm::mat4 & view)
{
	BEGIN_OPENGL
	{
		// Get a handle for our "gProjection" uniform
		GLuint projectionMatrixID = glGetUniformLocation(_programID, "gProjection");
		glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projection[0][0]);
		// Get a handle for our "gView" uniform
		GLuint viewMatrixID = glGetUniformLocation(_programID, "gView");
		glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &view[0][0]);
		// Get a handle for our "gModel" uniform
		GLuint modelMatrixID = glGetUniformLocation(_programID, "gModel");
		glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &_model[0][0]);
	}

	END_OPENGL
}
