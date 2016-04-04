#include "Object.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

Object::Object(const char* vShaderFile,
				const char* fShaderFile,
				const glm::vec3 & position,
				const glm::vec4 & color,
				const std::string textureIMG = "") :
				MinimalObject(position, color), 
				_vShaderFile(vShaderFile), _fShaderFile(fShaderFile), _textureImg(textureIMG)
{
}

void Object::_useMVP(const glm::mat4 & projection, const glm::mat4 & view)
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



// Create a NULL-terminated string by reading the provided file
static char* readShaderSource(const char* shaderFile)
{
	FILE* fp;
	fopen_s(&fp, shaderFile, "rb");

	if (fp == NULL) { return NULL; }

	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);

	fseek(fp, 0L, SEEK_SET);
	char* buf = new char[size + 1];
	fread(buf, 1, size, fp);

	buf[size] = '\0';
	fclose(fp);

	return buf;
}

// Create a GLSL program object from vertex and fragment shader files
GLuint Object::initShader(const char* vShaderFile, const char* fShaderFile)
{
	struct Shader
	{
		const char*  filename;
		GLenum       type;
		GLchar*      source;
	}
	shaders[2] = {
			{ vShaderFile, GL_VERTEX_SHADER, NULL },
			{ fShaderFile, GL_FRAGMENT_SHADER, NULL }
	};

	GLuint program = glCreateProgram();

	for (int i = 0; i < 2; ++i)
	{
		Shader& s = shaders[i];
		s.source = readShaderSource(s.filename);
		if (shaders[i].source == NULL)
		{
			std::cerr << "Failed to read " << s.filename << std::endl;
			exit(EXIT_FAILURE);
		}

		GLuint shader = glCreateShader(s.type);

		glShaderSource(shader, 1, (const GLchar**)&s.source, NULL);
		glCompileShader(shader);

		GLint  compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			std::cerr << s.filename << " failed to compile:" << std::endl;
			GLint  logSize;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetShaderInfoLog(shader, logSize, NULL, logMsg);
			std::cerr << logMsg << std::endl;
			delete[] logMsg;

			exit(EXIT_FAILURE);
		}

		delete[] s.source;

		glAttachShader(program, shader);
	}

	/* link  and error check */
	glLinkProgram(program);

	GLint  linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		std::cerr << "Shader program failed to link" << std::endl;
		GLint  logSize;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
		char* logMsg = new char[logSize];
		glGetProgramInfoLog(program, logSize, NULL, logMsg);
		std::cerr << logMsg << std::endl;
		delete[] logMsg;

		exit(EXIT_FAILURE);
	}

	/* use program object */
	glUseProgram(program);

	return program;
}

void Object::setWorldUniforms(const glm::vec3 camPos, Light* light)
{
	GLuint cameraID = glGetUniformLocation(_programID, "gEyePosition");
	glUniform3f(cameraID, camPos.x, camPos.y, camPos.z);

	GLuint lightPosID = glGetUniformLocation(_programID, "gLightPosition");
	glm::vec3 lightPos = light->getPosition();
	glUniform4f(lightPosID, lightPos.x, lightPos.y, lightPos.z, 1);

	GLuint lightColorID = glGetUniformLocation(_programID, "gLightColor");
	glm::vec4 lightColor = light->getColor();
	glUniform4f(lightColorID, lightColor.r, lightColor.g, lightColor.b, 1);

	GLuint lightDirID = glGetUniformLocation(_programID, "gLightDirection");
	glm::vec3 lightDir = light->getDirection();
	glUniform4f(lightDirID, lightDir.x, lightDir.y, lightDir.z, 1);
}