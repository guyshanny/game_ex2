#pragma once

#include "Object.h"
#include <vector>
#include <string>

class Wall : public Object
{
public:
	enum Commands
	{
		FLICKER_LIGHT,
		UNDO_FLICKER_LIGHT,

		NUM_OF_COMMANDS = 2
	};

	Wall(const char* vShaderFile,
		 const char* fShaderFile,
		 const float& width,
		 const float& height,
		 const std::string textureIMG);

	void draw(const glm::mat4& projection, const glm::mat4& view,
			  const glm::vec3 camPos, Light* light);
	void update();
	void init();

	// Events
	void flickerLight(const bool& mode);

private:
	bool _commands[Commands::NUM_OF_COMMANDS];
	float _flickerLightIndicator;
	float _width;
	float _height;

	void _flickerLight(const bool& mode);
};
