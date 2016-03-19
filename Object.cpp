#include "Object.h"

Object::Object() : _programID(NULL), _textureID(NULL), _model(1.0), _position(0.0f), _direction(0.0f), _initialPosition(0.0f), _initialDirection(0.0f), _vao(0), _vbo(0)
{
}

Object::Object(const GLuint& programID,
				const vec3 & position,
				const vec3 & direction,
				const GLuint& vao,
				const GLint& vbo) :
	_programID(programID),
	_position(position),
	_direction(direction),
	_initialPosition(position),
	_initialDirection(direction),
	_vao(vao),
	_vbo(vbo)
{
}

void Object::_useMVP(const mat4 & projection, const mat4 & view)
{
	BEGIN_OPENGL

	// Get a handle for our "gProjection" uniform
	GLuint projectionMatrixID = glGetUniformLocation(_programID, "gProjection");
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projection[0][0]);
	// Get a handle for our "gView" uniform
	GLuint viewMatrixID = glGetUniformLocation(_programID, "gView");
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &view[0][0]);
	// Get a handle for our "gModel" uniform
	GLuint modelMatrixID = glGetUniformLocation(_programID, "gModel");
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &_model[0][0]);

	END_OPENGL
}
