#include "Wall.h"

Wall::Wall(const char* vShaderFile,
		   const char* fShaderFile,
		   const float & width, 
		   const float & height, 
		   const std::string textureIMG) :
		   //150, 22, 11
		   Object(vShaderFile, fShaderFile, glm::vec3(0, 0, -50), glm::vec4(0.8, 0.25, 0.1, 1), textureIMG),
	_width(width),
	_height(height),
	_flickerLightIndicator(0.f)
{
}

void Wall::init()
{
	Object::init();
	glm::vec3 tmp1 = glm::vec3(-_width / 2, -_height / 2, _position.z) - glm::vec3(-_width / 2, _height / 2, _position.z);
	glm::vec3 tmp2 = glm::vec3(-_width / 2, -_height / 2, _position.z) - glm::vec3(_width / 2, -_height / 2, _position.z);
	glm::vec3 norm = -cross(normalize(tmp1), normalize(tmp2));

	// Create vertices
	//lower left corner
	_vertices.push_back(glm::vec4(-_width / 2, -_height / 2, _position.z, 1));
	_vertices.push_back(glm::vec4(norm, 0));
	_vertices.push_back(glm::vec4(0, 1, 0, 0));
	//upper left corner
	_vertices.push_back(glm::vec4(-_width / 2, _height / 2, _position.z, 1));
	_vertices.push_back(glm::vec4(norm, 0));
	_vertices.push_back(glm::vec4(0, 0, 0, 0));
	//lower right corner
	_vertices.push_back(glm::vec4(_width / 2, -_height / 2, _position.z, 1));
	_vertices.push_back(glm::vec4(norm, 0));
	_vertices.push_back(glm::vec4(1, 1, 0, 0));
	//upper right corner
	_vertices.push_back(glm::vec4(_width / 2, _height / 2, _position.z, 1));
	_vertices.push_back(glm::vec4(norm, 0));
	_vertices.push_back(glm::vec4(1, 0, 0, 0));

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
								sizeof(glm::vec4) * 3,
								0);

		GLint _normAttr = glGetAttribLocation(_programID, "norm");
		glEnableVertexAttribArray(_normAttr);
		glVertexAttribPointer(_normAttr, // attribute handle
							  4,          // number of scalars per vertex
							  GL_FLOAT,   // scalar type
							  GL_FALSE,
							  sizeof(glm::vec4) * 3,
							  (GLvoid*)(sizeof(glm::vec4)));

		GLint _texAttr = glGetAttribLocation(_programID, "texCoord");
		glEnableVertexAttribArray(_texAttr);
		glVertexAttribPointer(_texAttr, // attribute handle
							  4,          // number of scalars per vertex
							  GL_FLOAT,   // scalar type
							  GL_FALSE,
							  sizeof(glm::vec4) * 3,
							  (GLvoid*)(sizeof(glm::vec4) + sizeof(glm::vec4)));


		// Unbind vertex array:
		glBindVertexArray(0);
	}

	if (0 < _textureImg.size())
	{
		_textureID = initTexture(_textureImg.c_str());
	}
}

void Wall::flickerLight(const bool & mode)
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

void Wall::_flickerLight(const bool & mode)
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

void Wall::draw(const glm::mat4 & projection, const glm::mat4 & view,
				const glm::vec3 camPos, Light* light)
{
	BEGIN_OPENGL;
	{
		_useMVP(projection, view); 
		setWorldUniforms(camPos, light);

		// Get a handle for our "gMaterialColor" uniform
 		GLuint materialID = glGetUniformLocation(_programID, MATERIAL_COLOR);
 		glUniform4f(materialID, _color.r, _color.g, _color.b, _color.a);

		GLuint flickerLightID = glGetUniformLocation(_programID, "lightFlicker");
		glUniform1f(flickerLightID, _flickerLightIndicator);

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

void Wall::update()
{
	// Update commands
	if (_commands[Commands::FLICKER_LIGHT]) { _flickerLight(true); }
	if (_commands[Commands::UNDO_FLICKER_LIGHT]) { _flickerLight(false); }
}
