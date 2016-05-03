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
#include "PPBuffer.h"

#include <mmsystem.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
//												Globals											  //
////////////////////////////////////////////////////////////////////////////////////////////////////
World* _world;
GameEvents* _gameEvents;
PPBuffer* _ppbuffer;


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

		// PP controls
		KEY_NO_EFFECT = ('0'),
		KEY_BLUR = ('1'),
		KEY_EDGE_DETACTION = ('2'),
		KEY_SHARPING = ('3'),
		KEY_MEAN = ('4'),
		KEY_WAVE = ('5'),
		KEY_SWIRL = ('6'),
		KEY_GLOW = ('7'),
		KEY_SHOCKWAVE = ('8'),

	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void init( void )
{
	// TODO::REMOVE NEXT LINE
// 	glDepthFunc(GL_LESS);

	// Creating the world
	_world = new World();
	_world->init();

	// Creating game event manager
	_gameEvents = GameEvents::instance();
	_gameEvents->init(_world);

	// Creating post-processing buffer
	_ppbuffer = new PPBuffer();
	_ppbuffer->init(Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT);
}

void display( void )
{
	_ppbuffer->setup();

	// Clear the window & the screen buffer
	glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_world->draw();
	_ppbuffer->render();

	// Swap those buffers so someone will actually see the results
	glutSwapBuffers();
}

void keyboard( unsigned char key, int x, int y )
{
	switch (tolower(key))
	{    
		// Game's control
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
		case Controls::KEY_COLOR_CHANGE:
			_world->changeColorKeyPressed();
			break;
		case Controls::KEY_RESET:
		{
			_world->resetKeyPressed();
			_ppbuffer->reset();
		}
			
			break;
			// TODO::ADD NEXT IN THE NEXT EX
// 		case Controls::KEY_RELOAD:
// 		{
// 			_world->loadShaders();
// 			_ppbuffer->loadShaders();
// 		}
// 		break;

		// PP controls
		/* Kernels - https://en.wikipedia.org/wiki/Kernel_(image_processing)
					 http://homepages.inf.ed.ac.uk/rbf/HIPR2/log.htm
					 Our code in image processing course
		*/
		case Controls::KEY_NO_EFFECT:	// Identity matrix
			_ppbuffer->setConvolutionMatrix(glm::mat3(0.f, 0.f, 0.f,
													  0.f, 1.f, 0.f,
													  0.f, 0.f, 0.f));
			break;
		case Controls::KEY_BLUR:		// Gaussian blur
			_ppbuffer->setConvolutionMatrix(glm::mat3(1.f, 2.f, 1.f,
													  2.f, 4.f, 2.f, 
													  1.f, 2.f, 1.f) / 16.f);
			break;
		case Controls::KEY_EDGE_DETACTION:
			_ppbuffer->setConvolutionMatrix(glm::mat3(0.f, 1.f, 0.f,
													  1.f, -4.f, 1.f, 
													  0.f, 1.f, 0.f));
			break;
		case Controls::KEY_SHARPING:
			_ppbuffer->setConvolutionMatrix(glm::mat3(-1.f, -1.f, -1.f,
													  -1.f, 8.f, -1.f, 
													  -1.f, -1.f, -1.f));
			break;
		case Controls::KEY_MEAN:
			_ppbuffer->setConvolutionMatrix(glm::mat3(1.f) / 9.f);
			break;

		// Add-ons
		case Controls::KEY_WAVE:
			_ppbuffer->wave();
			break;
		case Controls::KEY_SWIRL:
			_ppbuffer->swirl();
			break;
		case Controls::KEY_GLOW:
			_ppbuffer->glow();
			break;
		case Controls::KEY_SHOCKWAVE:
			_ppbuffer->shockwave();
			break;

// 		case Controls::KEY_ACTION_BASED:
// 			_ppbuffer->setDestPos(_world->getDestPos());
// 			break;

		// Window's control
		case Controls::KEY_ESC:
			exit(0);
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
	_ppbuffer->updateMousePos(x, y);
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

void windowResize(int width, int height)
{
	// Updating buffer and the world correspondingly
	_ppbuffer->resize(width, height);
	_world->resize(width, height);

	glViewport(0, 0, width, height);
	glutPostRedisplay();
}

void timer(int value)
{
	glutTimerFunc(25, timer, value++);

	_ppbuffer->updateTime();
	glutPostRedisplay();
}

int main( int argc, char **argv )
{
	glutInit(&argc, argv);

#ifdef __APPLE__
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_3_3_CORE_PROFILE);
#else
	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#endif
	glutInitWindowSize(Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT);
    glutCreateWindow(argv[0]);
	glEnable(GL_DEPTH_TEST);
    
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	int glewStatus = glewInit();
	if (glewStatus != GLEW_OK) 
	{
		std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
		exit(1);
	}

	// Callback functions
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
	glutMouseFunc( mouse );
	glutMouseWheelFunc( mouseWheel );
	glutPassiveMotionFunc( mouseMove );
	glutSpecialFunc( specialkey );
	glutIdleFunc( update );
	glutReshapeFunc( windowResize );
	glutTimerFunc(150, timer, 0);
	
	PlaySound("sounds\\ScarySound.wav", NULL, SND_ASYNC | SND_LOOP);
	init();
    glutMainLoop();

	if (NULL != _world) { delete _world; }
	if (NULL != _gameEvents) { delete _gameEvents; }
	if (NULL != _ppbuffer) { delete _ppbuffer; }

    return 0;
}
