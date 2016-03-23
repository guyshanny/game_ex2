#pragma once

#include "MinimalObject.h"

#include "GlobalFunctions.h"

#define TEXTURE_SAMPLER "gTextureSampler"
#define MATERIAL_COLOR "gMaterialColor"

#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

typedef OpenMesh::PolyMesh_ArrayKernelT<> Mesh;


class Object : public MinimalObject
{
protected:
	// Shaders' stuff
	GLuint _programID;
	GLuint _vao, _vbo, _ebo;

	// MVP
	glm::mat4 _model;

	// Object's properties
	glm::vec3 _position;
	glm::vec3 _direction;
	glm::vec4 _color;
	GLuint _textureID;
	const std::string _textureImg;

	std::vector<glm::vec4> _vertices;

	Object(const GLuint& programID, 
		   const glm::vec3 & position,
		   const glm::vec3 & direction,
		   const glm::vec4 & color,
		   const std::string textureIMG);

	void _useMVP(const glm::mat4& projection, const glm::mat4& view);

public:
	virtual ~Object() {};

	glm::mat4 getModel() { return _model; }
};
