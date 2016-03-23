#pragma once

#include "Object.h"

class Teapot : Object
{
public:
	Teapot(const GLuint& programID, const std::string textureIMG, const std::string meshPath);

	void draw(const glm::mat4& projection, const glm::mat4& view);
	void update() {}
	void init();

	void changeColor();
private:
	int _colorIndicator;
	
	Mesh _mesh;
	const std::string _meshPath;
	std::vector<GLuint> _triangles;
	

	BOOL _loadMesh();
};