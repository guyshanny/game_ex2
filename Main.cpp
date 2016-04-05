#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "World.h"
#include "GameEvents.h"

#define SHADERS_VERTEX "shaders\\phongV3.3.vert"
#define SHADERS_FRAGMENT "shaders\\phongV3.3.frag"


////////////////////////////////////////////////////////////////////////////////////////////////////
//												Globals											  //
////////////////////////////////////////////////////////////////////////////////////////////////////
World* _world;
GameEvents* _gameEvents;

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

	_gameEvents = GameEvents::instance();
	_gameEvents->init(_world);
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

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN) 
			{
				_world->mouseLeftDown(x, y);
			}
			else {
				_world->mouseLeftUp(x, y);
			}
			break;
// 		case GLUT_RIGHT_BUTTON:
// 			if (state == GLUT_DOWN) 
// 			{
// 				_model.begin_translation(x, y);
// 			}
// 			else {
// 				_model.end_translation();
// 			}
// 			break;
		default:
			break;
	}
}

void mouseWheel(int wheel, int direction, int x, int y)
{
	// ZoomIn
	if (direction > 0)
	{
		_world->mouseWheelForward(x, y);
	}
	else // ZoomOut
	{
		_world->mouseWheelBackWard();
	}
}

void mouseMove(int x, int y)
{
	_world->moveLightUsingMouse(x, y);
	glutPostRedisplay();
}

void specialkey(int key, int x, int y )
{
	_world->moveLightUsingArrows(key);
	glutPostRedisplay();
}

void update()
{
	static int currentTime, deltaTime, prevTime = 0; 
	static int startTime, elapsedTime = 0;
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = currentTime - prevTime;
	prevTime = currentTime;

	_gameEvents->update();
	_world->update();

	glutPostRedisplay();
}

int main( int argc, char **argv )
{
	glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(argv[0]);
    
	glewExperimental = GL_TRUE;
	glewInit();
    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
	glutMouseFunc(mouse);
	glutMouseWheelFunc(mouseWheel);
	glutPassiveMotionFunc(mouseMove);
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
