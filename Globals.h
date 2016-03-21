#ifndef __GLOBALS_H
#define __GLOBALS_H

#define GRID_SIZE						30			// The mesh grid's size
#define WRAPPING_CUBE_SIZE				512
#define WINDOW_BOUNDARY				    vec3(WRAPPING_CUBE_SIZE/2, WRAPPING_CUBE_SIZE/2, 15.f)

#define PROGRAM_DEFAULT_ID				"default"
#define BEGIN_OPENGL					glUseProgram(_programID);
#define END_OPENGL						glUseProgram(0);

#endif