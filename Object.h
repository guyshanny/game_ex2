#pragma once

#include "MinimalObject.h"
#include "Light.h"
#include <vector>

#define TEXTURE_SAMPLER "gTextureSampler"
#define MATERIAL_COLOR "gMaterialColor"

class Object : public MinimalObject
{
protected:
	// Shaders' stuff
	GLuint _vao, _vbo, _ebo;

	const char* _vShaderFile;
	const char* _fShaderFile;

	// MVP
	glm::mat4 _model;

	// Object's properties
	GLuint _textureID;
	const std::string _textureImg;

	std::vector<glm::vec4> _vertices;

	Object(const char* vShaderFile, 
		   const char* fShaderFile,
		   const glm::vec3 & position,
		   const glm::vec4 & color,
		   const std::string textureIMG);

	void _useMVP(const glm::mat4& projection, const glm::mat4& view);
	void setWorldUniforms(const glm::vec3 camPos, Light* light);
	static GLuint initTexture(const char* fName);
	static GLuint initShader(const char* vShaderFile, const char* fShaderFile);

public:
	virtual ~Object() {};
	
	virtual void draw(const glm::mat4& projection, const glm::mat4& view,
					  const glm::vec3 camPos, Light* light) = 0;
	
	void init()
	{
		_programID = initShader(_vShaderFile, _fShaderFile);
	}

	glm::mat4 getModel() { return _model; }
};
