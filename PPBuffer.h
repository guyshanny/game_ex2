//
//  PPBuffer.h
//  cg-projects
//
//  Created by HUJI Computer Games Programming course staff, 2014.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // for glm::value_ptr

using namespace glm;

#include <iostream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include <GL/gl.h>
#endif

namespace PPEffects
{
	enum Modes
	{
		CONVOLUTION,
	};
}

class PPBuffer 
{
	// Shaders' handles
	GLuint _vao;
	GLuint _vbo_fbo_vertices;
	GLuint _fbo, _fbo_texture, _rbo_depth;
	GLuint _program_postproc, _attribute_v_coord_postproc, _uniform_fbo_texture;
	GLuint _textureMode;
	GLuint _convMatrixHandle;

	// PP params
	mat3 _convMatrix;
	float _texMode;

	// Window
	int _width;
	int _height;
	float _offsetX;
	float _offsetY;

	void _getShaderHandles();

public:
	PPBuffer();
	virtual ~PPBuffer();
	void init(const int& screenWidth, const int& screenHeight);
	void setup();
	void render();
	void resize(int width, int height);

	// Effects
	void setConvolutionMatrix(const mat3& convMatrix);

};
