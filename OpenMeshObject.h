#pragma once
#include "Object.h"

#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

typedef OpenMesh::PolyMesh_ArrayKernelT<> Mesh;

class OpenMeshObject : public Object
{
protected:
	float _diff[3];
	float _maxDiff;
	float _midPoint[3], _lower[3], _higher[3];
	std::vector<float> _verticesRgb;
	const char* _meshFile;
	Mesh _mesh;
	
	// Load a mesh from the given input file
	bool loadMesh();

	/** This function computes the geometrical center and the axis aligned bounding box of the
	object. The bounding box is represented by the lower left and upper right corners. */
	void computeBoundingBox();

	float normalize(float value, int axis);
	float normalize_colour(float value, int axis);
	void calculate_vertex_normal(const Mesh::VertexHandle &vHandle, const Mesh::FaceHandle &fHandle);

public:

	OpenMeshObject(const GLuint& programID,
				   const glm::vec3 & position,
				   const glm::vec3 & direction,
				   const glm::vec4 & color,
				   const char* file_name,
				   const std::string textureIMG);

	/* this function computes the center of each mesh */
	virtual void init();

	virtual ~OpenMeshObject();
};

