#pragma once

#include "MinimalObject.h"
#include <vector>

#define TEXTURE_SAMPLER "gTextureSampler"
#define MATERIAL_COLOR "gMaterialColor"

class Object : public MinimalObject
{
protected:
	// Shaders' stuff
	GLuint _vao, _vbo, _ebo;

	// MVP
	glm::mat4 _model;

	// Object's properties
	GLuint _textureID;
	const std::string _textureImg;

	std::vector<glm::vec4> _vertices;

	Object(const GLuint& programID, 
		   const glm::vec3 & position,
		   const glm::vec4 & color,
		   const std::string textureIMG);

	void _useMVP(const glm::mat4& projection, const glm::mat4& view);
	GLuint initTexture(const char* fName);

public:
	virtual ~Object() {};

	glm::mat4 getModel() { return _model; }
};
