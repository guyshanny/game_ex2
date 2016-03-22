#ifndef __TEAPOT_H
#define __TEAPOT_H

#include "Object.h"

#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

typedef OpenMesh::PolyMesh_ArrayKernelT<> Mesh;

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
};

#endif
