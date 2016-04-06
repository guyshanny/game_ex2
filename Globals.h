#pragma once

#define WRAPPING_CUBE_SIZE				100

#define PROGRAM_DEFAULT_ID				"default"
#define BEGIN_OPENGL					glUseProgram(_programID);
#define END_OPENGL						glUseProgram(0);

class Globals
{
public:
	static int WINDOW_WIDTH;
	static int WINDOW_HEIGHT;
};