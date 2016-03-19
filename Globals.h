#ifndef __GLOBALS_H
#define __GLOBALS_H

#define GRID_SIZE						30			// The mesh grid's size
#define WINDOW_BOUNDARY				    vec3(GRID_SIZE/2-2.0f, -5.0f, GRID_SIZE/2-2.0f)		// The grid size's limit

#define PROGRAM_DEFAULT_ID				"default"
#define BEGIN_OPENGL					glUseProgram(_programID);
#define END_OPENGL						glUseProgram(0);



#endif