#pragma once

#include "OpenMeshObject.h"

class Teapot : OpenMeshObject
{
public:
	Teapot(const GLuint& programID, const std::string textureIMG, const char*  meshPath);

	void draw(const glm::mat4& projection, const glm::mat4& view);
	void update();
	void init();

	void changeColor();
private:
	int _colorIndicator;

	std::vector<GLuint> _triangles;
	
	//bool _loadMesh();
};