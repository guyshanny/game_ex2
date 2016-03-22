#include "Wall.h"

Wall::Wall(const GLuint & programID, 
		   const int & width, 
		   const int & height, 
		   const std::string textureIMG) :
	Object(programID, glm::vec3(0.f, 0.f, -5.f), glm::vec3(0.0f), 0, 0, textureIMG, ""),
	_width(0.1),
	_height(0.1)
{
	_color = glm::vec4(1, 0, 1, 1);
}

void Wall::init()
{
	_buildWall();
}

void Wall::draw(const glm::mat4 & projection, const glm::mat4 & view)
{
	glUseProgram(_programID);
	{
		// Get a handle for our "gMaterialColor" uniform
		GLuint materialID = glGetUniformLocation(_programID, MATERIAL_COLOR);
		glUniform4f(materialID, _color.r, _color.g, _color.b, _color.a);

		glUniform1i(glGetUniformLocation(_programID, TEXTURE_SAMPLER), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _textureID);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(_vao);
		glDrawArrays(GL_TRIANGLE_FAN, 0, _vertices.size());
		glBindVertexArray(0);
	}
	glUseProgram(0);
}

void Wall::_buildWall()
{
	// Create vertices
	_vertices.push_back(glm::vec4(-_width/2., -_height/2., 3.f, 1.0f));
	_vertices.push_back(glm::vec4(-_width/2., _height/2., 3.f, 1.0f));
	_vertices.push_back(glm::vec4(_width/2., -_height/2., 3.f, 1.0f));
	_vertices.push_back(glm::vec4(_width/2., _height/2., 3.f, 1.0f));
	
	BEGIN_OPENGL;
	{
		// Create and bind the object's Vertex Array Object
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		// Create and load vertex data into a Vertex Buffer Object
		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

		// Tells OpenGL that there is vertex data in this buffer object and what form that vertex data takes:
		// Obtain attribute handles:
		GLint _posAttrib;
		_posAttrib = glGetAttribLocation(_programID, "position");
		glEnableVertexAttribArray(_posAttrib);
		glVertexAttribPointer(0, // attribute handle
								4,          // number of scalars per vertex
								GL_FLOAT,   // scalar type
								GL_FALSE,
								0,
								0);
	}
	END_OPENGL;
}
