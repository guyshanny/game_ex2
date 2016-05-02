#pragma once

#include <string>

// Program globals
#ifdef _WIN32
	#define SHADERS_DIR "shaders\\"
#else
	#define SHADERS_DIR "shaders/"
#endif

// Game globals
#define WRAPPING_CUBE_SIZE				100

// Code macros
#define PROGRAM_DEFAULT_ID				"default"
#define BEGIN_OPENGL					glUseProgram(_programID);
#define END_OPENGL						glUseProgram(0);


class Globals
{
public:
	static int WINDOW_WIDTH;
	static int WINDOW_HEIGHT;
};