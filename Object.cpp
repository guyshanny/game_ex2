#include "Object.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

Object::Object(const GLuint& programID,
				const glm::vec3 & position,
				const glm::vec4 & color,
				const std::string textureIMG = "") :
	MinimalObject(programID, position, color),
	_textureImg(textureIMG)
{
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

GLuint Object::initTexture(const char* fName)
{
	cv::Mat img = cv::imread(fName);
	//cv::imshow("CV debug", img);

	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, img.cols, img.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, img.ptr());
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}
