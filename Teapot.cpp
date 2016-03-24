#include "Teapot.h"
#include <math.h>
#include "GlobalFunctions.h"

Teapot::Teapot(const GLuint& programID, const std::string textureIMG, const char*  meshPath) :
OpenMeshObject(programID, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f), glm::vec4(0.0f), meshPath, textureIMG),
	_colorIndicator(0)
{
	// Params
	_color = glm::vec4(0, 0, 1, 1);
	_textureID = InitTexture(_textureImg.c_str());

	// InitialPosition
	float angle = -1;
	glm::mat4 xRotation = glm::rotate(_model, angle, glm::vec3(1, 0, 0));
	_model = glm::rotate(xRotation, angle, glm::vec3(0, 1, 0));
}

void Teapot::draw(const glm::mat4 & projection, const glm::mat4 & view)
{
	_useMVP(projection, view);

	BEGIN_OPENGL;
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glBindVertexArray(_vao);

		// Get a handle for our "gMaterialColor" uniform
		GLuint materialID = glGetUniformLocation(_programID, MATERIAL_COLOR);
		glUniform4f(materialID, _color.r, _color.g, _color.b, _color.a);
		
		GLuint textureSamplerID = glGetUniformLocation(_programID, TEXTURE_SAMPLER);
		glUniform1i(textureSamplerID, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _textureID);

		//draw
		glDrawArrays(GL_TRIANGLES, 0, _mesh.n_faces() * 3);

		// Unbind the Vertex Array object
		glBindVertexArray(0);
		// Teapot
		//	glutSolidTeapot(1.0);
	}
	END_OPENGL;
}

void Teapot::init()
{
	OpenMeshObject::init();

	// Initialize vertices buffer and transfer it to OpenGL
	{
		// Create and bind the Mesh Vertex Array Object
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		// Create and load vertex data into a Vertex Buffer Object
		{
			glGenBuffers(1, &_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBufferData(GL_ARRAY_BUFFER,
						sizeof(glm::vec4) * _vertices.size(),
						&_vertices[0],
						GL_STATIC_DRAW);

			// Obtain attribute handles:
			GLint _posAttrib = glGetAttribLocation(_programID, "position");
			glEnableVertexAttribArray(_posAttrib);
			glVertexAttribPointer(_posAttrib, // attribute handle
								  4,          // number of scalars per vertex
								  GL_FLOAT,   // scalar type
								  GL_FALSE,
								  sizeof(glm::vec4) * 2,
								  0);
			//TODO: Smear colours.
			GLint _fillColorUV = glGetAttribLocation(_programID, "norm");
			glEnableVertexAttribArray(_fillColorUV);
			glVertexAttribPointer(_fillColorUV, // attribute handle
								  4,          // number of scalars per vertex
								  GL_FLOAT,   // scalar type
								  GL_FALSE,
								  sizeof(glm::vec4) * 2,
								  (GLvoid*)(sizeof(glm::vec4)));

			//glGenBuffers(1, &_ebo);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
			//glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			//			sizeof(GLuint) * _triangles.size(),
			//			&_triangles[0],
			//			GL_STATIC_DRAW);

			//GLint posAttrib = glGetAttribLocation(_programID, "position");
			//glEnableVertexAttribArray(posAttrib);
			//glVertexAttribPointer(posAttrib,
			//						4,
			//						GL_FLOAT,
			//						GL_FALSE,
			//						0,
			//						0);

			// Unbind vertex array:
			glBindVertexArray(0);
		}
	}
}

//bool Teapot::_loadMesh()
//{
//	if (!OpenMesh::IO::read_mesh(_mesh, _meshPath))
//	{
//		// if we didn't make it, exit...
//		fprintf(stderr, "Error loading mesh, Aborting.\n");
//		return false;
//	}
//
//	// Add all vertices to vertices vector
//	for (Mesh::VertexIter vertexIter = _mesh.vertices_begin(); vertexIter != _mesh.vertices_end(); vertexIter++)
//	{
//		Mesh::Point& p = _mesh.point(*vertexIter);
//		_vertices.push_back(glm::vec4(p[0], p[1], p[2], 1.0f));
//	}
//
//	// Add all triangles to elements vector
//	for (auto f_it = _mesh.faces_begin(); f_it != _mesh.faces_end(); f_it++)
//	{
//		for (auto fv_it = _mesh.fv_iter(f_it.handle()); fv_it; fv_it++)
//		{
//			_triangles.push_back(fv_it.handle().idx());
//		}
//	}
//	return true;
//}

void Teapot::changeColor()
{
	_colorIndicator = (_colorIndicator + 1) % 5;
	switch (_colorIndicator)
	{
		case 0:
			_color = glm::vec4(1, 1, 1, 1);
			break;
		case 1: 
			_color = glm::vec4(1, 0, 0, 1);
			break;
		case 2: 
			_color = glm::vec4(0, 1, 0, 1);
			break;
		case 3: 
			_color = glm::vec4(0, 0, 1, 1);
			break;
		case 4: 
			_color = glm::vec4(1, 1, 0, 1);
			break;
	}
}

void Teapot::update()
{
	// translate & rotate around x/y axis
	static float angle = 0.0f;
	angle += 0.1f;
	glm::mat4 xTranslate, xRotation;

	// 1st geometry translate & rotate in x & rotate in y
	xTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0, -1, 0));
	xRotation = glm::rotate(xTranslate, angle, glm::vec3(1, 0, 0));
	_model = glm::rotate(xRotation, angle, glm::vec3(0, 1, 0));
}

