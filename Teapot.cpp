#include "Teapot.h"
#include <math.h>

Teapot::Teapot(const char* vShaderFile, const char* fShaderFile, 
			   const std::string textureIMG, const char*  meshPath) :
			   OpenMeshObject(vShaderFile, fShaderFile, glm::vec3(0, 0, 0), glm::vec4(1, 1, 1, 1), meshPath, textureIMG),
			   _colorIndicator(0), _flickerLightIndicator(0.f)
{
}

void Teapot::draw(const glm::mat4 & projection, const glm::mat4 & view,
				  const glm::vec3 camPos, Light* light)
{
	BEGIN_OPENGL;
	{
		_useMVP(projection, view);
		setWorldUniforms(camPos, light);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glBindVertexArray(_vao);

		// Get a handle for our "gMaterialColor" uniform
		GLuint materialID = glGetUniformLocation(_programID, MATERIAL_COLOR);
		glUniform4f(materialID, _color.r, _color.g, _color.b, _color.a);
		
		GLuint flickerLightID = glGetUniformLocation(_programID, "lightFlicker");
		glUniform1f(flickerLightID, _flickerLightIndicator);

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
			GLint _posAttr = glGetAttribLocation(_programID, "position");
			glEnableVertexAttribArray(_posAttr);
			glVertexAttribPointer(_posAttr, // attribute handle
								  4,          // number of scalars per vertex
								  GL_FLOAT,   // scalar type
								  GL_FALSE,
								  sizeof(glm::vec4) * 2,
								  0);
			
			GLint _normAttr = glGetAttribLocation(_programID, "norm");
			glEnableVertexAttribArray(_normAttr);
			glVertexAttribPointer(_normAttr, // attribute handle
								  4,          // number of scalars per vertex
								  GL_FLOAT,   // scalar type
								  GL_FALSE,
								  sizeof(glm::vec4) * 2,
								  (GLvoid*)(sizeof(glm::vec4)));

			// Unbind vertex array:
			glBindVertexArray(0);
		}
	}

	if (0 < _textureImg.size())
	{
		_textureID = initTexture(_textureImg.c_str());
	}
}

#pragma region Game events
void Teapot::changeColor()
{
	_commands[Commands::CHANGE_COLOR] = true;
}

void Teapot::flickerLight(const bool & mode)
{
	if (mode)
	{
		_commands[Commands::FLICKER_LIGHT] = true;
	}
	else
	{
		_commands[Commands::UNDO_FLICKER_LIGHT] = true;
	}
}
#pragma endregion


void Teapot::_updateCommands()
{
	if (_commands[Commands::CHANGE_COLOR]) { _changeColor(); }
	if (_commands[Commands::FLICKER_LIGHT]) { _flickerLight(true); }
	if (_commands[Commands::UNDO_FLICKER_LIGHT]) { _flickerLight(false); }
}

void Teapot::_changeColor()
{
	_commands[Commands::CHANGE_COLOR] = false;

	int x = _colorIndicator;
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

void Teapot::_flickerLight(const bool & mode)
{
	_commands[Commands::FLICKER_LIGHT] = false;
	_commands[Commands::UNDO_FLICKER_LIGHT] = false;
	
	if (mode)
	{
		_flickerLightIndicator = 1.f;
	}
	else
	{
		_flickerLightIndicator = 0.f;
	}
}

void Teapot::update()
{
	// Update commands
	_updateCommands();

	// translate & rotate around x/y axis
	_angle += 0.001f;

	// 1st geometry translate & rotate in x & rotate in y
	glm::mat4 xTranslate = glm::translate(glm::mat4(1), _position);
	glm::mat4 xRotation = glm::rotate(xTranslate, _angle, glm::vec3(1, 0, 0));
	_model = glm::rotate(xRotation, _angle, glm::vec3(0, 1, 0));
}
