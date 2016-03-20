#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "World.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//												Globals											  //
////////////////////////////////////////////////////////////////////////////////////////////////////
World* _world;

int g_colormode = 0;

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

// Create a NULL-terminated string by reading the provided file
static char* readShaderSource(const char* shaderFile)
{
    FILE* fp = fopen(shaderFile, "rb");

    if ( fp == NULL ) { return NULL; }

    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);

    fseek(fp, 0L, SEEK_SET);
    char* buf = new char[size + 1];
    fread(buf, 1, size, fp);

    buf[size] = '\0';
    fclose(fp);

    return buf;
}

// Create a GLSL program object from vertex and fragment shader files
GLuint InitShader(const char* vShaderFile, const char* fShaderFile)
{
    struct Shader {
	const char*  filename;
	GLenum       type;
	GLchar*      source;
    }  shaders[2] = {
	{ vShaderFile, GL_VERTEX_SHADER, NULL },
	{ fShaderFile, GL_FRAGMENT_SHADER, NULL }
    };

    GLuint program = glCreateProgram();
    
    for ( int i = 0; i < 2; ++i ) {
	Shader& s = shaders[i];
	s.source = readShaderSource( s.filename );
	if ( shaders[i].source == NULL ) {
	    std::cerr << "Failed to read " << s.filename << std::endl;
	    exit( EXIT_FAILURE );
	}

	GLuint shader = glCreateShader( s.type );

	glShaderSource( shader, 1, (const GLchar**) &s.source, NULL );
	glCompileShader( shader );

	GLint  compiled;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
	if ( !compiled ) {
	    std::cerr << s.filename << " failed to compile:" << std::endl;
	    GLint  logSize;
	    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
	    char* logMsg = new char[logSize];
	    glGetShaderInfoLog( shader, logSize, NULL, logMsg );
	    std::cerr << logMsg << std::endl;
	    delete [] logMsg;

	    exit( EXIT_FAILURE );
	}

	delete [] s.source;

	glAttachShader( program, shader );
    }

    /* link  and error check */
    glLinkProgram(program);

    GLint  linked;
    glGetProgramiv( program, GL_LINK_STATUS, &linked );
    if ( !linked ) {
	std::cerr << "Shader program failed to link" << std::endl;
	GLint  logSize;
	glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
	char* logMsg = new char[logSize];
	glGetProgramInfoLog( program, logSize, NULL, logMsg );
	std::cerr << logMsg << std::endl;
	delete [] logMsg;

	exit( EXIT_FAILURE );
    }

    /* use program object */
    glUseProgram(program);

    return program;
}

void init( void )
{
    // Load shaders and use the resulting shader program
    GLuint programID = InitShader( "phong.vert", "phong.frag" );
	glUseProgram(programID);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor( 0.0, 0.0, 0.0, 1.0 );

	// Creating the world
	_world = new World(programID);
	_world->init();
}

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );     // clear the window

	_world->draw();
}

void keyboard( unsigned char key, int x, int y )
{
	switch (tolower(key))
	{    
		case Controls::KEY_FORWARD:
		{
			_world->forwardKeyPressed();
		}
		break;
		case Controls::KEY_BACKWARD:
		{
			_world->backwardKeyPressed();
		}
		break;
		case Controls::KEY_TURN_RIGHT:
		{
			_world->turnRightKeyPressed();
		}
		break;
		case Controls::KEY_TURN_LEFT:
		{
			_world->turnLeftKeyPressed();
		}
		break;
		case Controls::KEY_ESC:
		{
			exit(0);
		}
		break;
		case Controls::KEY_COLOR_CHANGE:
		{
			_world->changeColorKeyPressed();
		}
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

    // translate & rotate around x/y axis
	static float angle = 0.0f;
	angle += 0.1f;
	glm::mat4 xTranslate, xRotation;

	// 1st geometry translate & rotate in x & rotate in y
	xTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0, -1, 0)); 
	xRotation = glm::rotate(xTranslate, angle, glm::vec3(1, 0, 0));
// 	Model = glm::rotate(xRotation, angle, glm::vec3(0, 1, 0));

	glutPostRedisplay();
}

int main( int argc, char **argv )
{
	glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WRAPPING_CUBE_SIZE, WRAPPING_CUBE_SIZE);
    glutCreateWindow(argv[0]);
    
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
