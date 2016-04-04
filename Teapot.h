#pragma once

#include "OpenMeshObject.h"

class Teapot : public OpenMeshObject
{
public:
	enum Commands
	{
		CHANGE_COLOR,
		FLICKER_LIGHT,
		UNDO_FLICKER_LIGHT,

		// Number of commands
		NUM_OF_COMMANDS = 3
	};

	Teapot(const char* vShaderFile, const char* fShaderFile, const std::string textureIMG, const char*  meshPath);

	void draw(const glm::mat4& projection, const glm::mat4& view,
			  const glm::vec3 camPos, Light* light);
	void update();
	void init();

	// Events
	void changeColor();
	void flickerLight(const bool& mode);

private:
	int _colorIndicator;
	float _angle;
	bool _commands[Commands::NUM_OF_COMMANDS];
	float _flickerLightIndicator;

	void _updateCommands();
	void _changeColor();
	void _flickerLight(const bool& mode);

	//std::vector<GLuint> _triangles;
};