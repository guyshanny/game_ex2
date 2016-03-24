#include "Wall.h"

Wall::Wall(const GLuint & programID, 
		   const float & width, 
		   const float & height, 
		   const std::string textureIMG) :
	Object(programID, glm::vec3(0.f, 0.f, -3.f), glm::vec3(0.0f), glm::vec4(0.0f), textureIMG),
	_width(width),
	_height(height)
{
	_color = glm::vec4(1, 0, 1, 1);
	_model = glm::translate(_model, glm::vec3(0, 0, -5.0f));
}

void Wall::init()
{
	// Create vertices
	_vertices.push_back(glm::vec4(-_width / 2, -_height / 2, _position.z, 1.0f));
	_vertices.push_back(glm::vec4(-_width / 2, _height / 2, _position.z, 1.0f));
	_vertices.push_back(glm::vec4(_width / 2, -_height / 2, _position.z, 1.0f));
	_vertices.push_back(glm::vec4(_width / 2, _height / 2, _position.z, 1.0f));

	{
		// Create and bind the object's Vertex Array Object
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		// Create and load vertex data into a Vertex Buffer Object
		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER,
					sizeof(glm::vec4) * _vertices.size(),
					&_vertices[0],
					GL_STATIC_DRAW);

		// Tells OpenGL that there is vertex data in this buffer object and what form that vertex data takes:
		// Obtain attribute handles:
		GLint posAttrib = glGetAttribLocation(_programID, "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, // attribute handle
								4,          // number of scalars per vertex
								GL_FLOAT,   // scalar type
								GL_FALSE,
								0,
								0);

		// Unbind vertex array:
		glBindVertexArray(0);
	}
}

void Wall::draw(const glm::mat4 & projection, const glm::mat4 & view)
{
	_useMVP(projection, view);

	BEGIN_OPENGL;
	{
		// Get a handle for our "gMaterialColor" uniform
 		GLuint materialID = glGetUniformLocation(_programID, MATERIAL_COLOR);
 		glUniform4f(materialID, _color.r, _color.g, _color.b, _color.a);

 		glUniform1i(glGetUniformLocation(_programID, TEXTURE_SAMPLER), 0);
 		glActiveTexture(GL_TEXTURE0);
 		glBindTexture(GL_TEXTURE_2D, _textureID);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(_vao);
		//glUniform1i(glGetUniformLocation(_programID, "isTeapot"), false);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, _vertices.size());
		glBindVertexArray(0);
	}
	END_OPENGL;
}