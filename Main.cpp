#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "World.h"

#define SHADERS_VERTEX "shaders\\phongV3.3.vert"
#define SHADERS_FRAGMENT "shaders\\phongV3.3.frag"


////////////////////////////////////////////////////////////////////////////////////////////////////
//												Globals											  //
////////////////////////////////////////////////////////////////////////////////////////////////////
World* _world;

////////////////////////////////////////////////////////////////////////////////////////////////////
//												Controls										  //
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Controls
{
	enum KeyControls
	{
		KEY_ESC = (27),
		KEY_RESET = ('r'),
		KEY_RELOAD = ('l'),

		// Teapot controls
		KEY_COLOR_CHANGE = (' '),

		// Camera controls
		KEY_FORWARD = ('w'),
		KEY_BACKWARD = ('s'),
		KEY_TURN_LEFT = ('a'),
		KEY_TURN_RIGHT = ('d'),
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void init( void )
{
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor( 0.0, 0.0, 0.0, 1.0 );

	// Creating the world
	_world = new World();
	_world->init();
}

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );     // clear the window

	_world->draw();

	// Swap those buffers so someone will actually see the results... //
	glutSwapBuffers();
}

void keyboard( unsigned char key, int x, int y )
{
	switch (tolower(key))
	{    
		case Controls::KEY_FORWARD:
			_world->forwardKeyPressed();
			break;
		case Controls::KEY_BACKWARD:
			_world->backwardKeyPressed();
			break;
		case Controls::KEY_TURN_RIGHT:
			_world->turnRightKeyPressed();
			break;
		case Controls::KEY_TURN_LEFT:
			_world->turnLeftKeyPressed();
			break;
		case Controls::KEY_ESC:
			exit(0);
			break;
		case Controls::KEY_COLOR_CHANGE:
			_world->changeColorKeyPressed();
			break;
		default:
			std::cerr << "Key " << tolower(key) << " undefined\n";
			break;
	}
	glutPostRedisplay();
}

void specialkey(int key, int x, int y )
{
	_world->moveLight(key);
	glutPostRedisplay();
}

void update()
{
	static int currentTime, deltaTime, prevTime = 0; 
	static int startTime, elapsedTime = 0;
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = currentTime - prevTime;
	prevTime = currentTime;
	_world->update();

	glutPostRedisplay();
}

int main( int argc, char **argv )
{
	glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutCreateWindow(argv[0]);
    
	glewExperimental = GL_TRUE;
	glewInit();
    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutSpecialFunc( specialkey );
	glutIdleFunc( update );

    glutMainLoop();

	if (NULL != _world)
	{
		delete _world;
		_world = NULL;
	}
    return 0;
}
