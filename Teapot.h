#pragma once

#include "OpenMeshObject.h"

class Teapot : OpenMeshObject
{
public:
	Teapot(const char* vShaderFile, const char* fShaderFile, const std::string textureIMG, const char*  meshPath);

	void draw(const glm::mat4& projection, const glm::mat4& view,
			  const glm::vec3 camPos, Light* light);
	void update();
	void init();

	void changeColor();

private:
	int _colorIndicator;

	//std::vector<GLuint> _triangles;
};