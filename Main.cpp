#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "World.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//												Globals											  //
////////////////////////////////////////////////////////////////////////////////////////////////////
World* _world;

int g_colormode = 0;

glm::vec4 lightPos = glm::vec4(4, 4, 4, 1);
glm::vec4 teapotColor = glm::vec4(1, 1, 1, 1);

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

GLuint InitTexture(char* fName) {
	cv::Mat img = cv::imread(fName);
	//cv::imshow("CV debug", img);

	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, img.cols, img.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, img.ptr());

	return texture;
}

void init( void )
{
    // Load shaders and use the resulting shader program
    GLuint programID = InitShader( "phong.vert", "phong.frag" );
	glUseProgram(programID);

	GLuint texture = InitTexture("texture.jpg");
	glBindTexture(GL_TEXTURE_2D, texture);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor( 0.0, 0.0, 0.0, 1.0 );

	// Creating the world
	_world = new World(programID, texture);
}

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );     // clear the window

	_world->draw();

	GLuint programID = _world->getProgramID();

    glUseProgram(programID);

	// Get a handle for our "gEyePosition" uniform
	vec3 cameraPosition = _world->getCamera()->getPosition();
	GLuint cameraID = glGetUniformLocation(programID, "gEyePosition");
	glUniform3f(cameraID, cameraPosition.x, cameraPosition.y, cameraPosition.z);
	// Get a handle for our "gLightPosition" uniform
	GLuint lightID = glGetUniformLocation(programID, "gLightPosition");
	glUniform4f(lightID, lightPos.x, lightPos.y, lightPos.z, lightPos.w);

	glUseProgram(0);
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
			std::cerr << "Key " << tolower(key)<< " undefined\n";
			break;
	}

	glutPostRedisplay();
}

void specialkey(int key, int x, int y )
{
	switch (key)  
	{    
	case GLUT_KEY_LEFT:
		lightPos[0] -= 0.5f;
		break;  
	case GLUT_KEY_RIGHT:    
		lightPos[0] += 0.5f;
		break;  
	case GLUT_KEY_UP:      
		lightPos[1] += 0.5f;
		break;  
	case GLUT_KEY_DOWN:
		lightPos[1] -= 0.5f;
		break;  
	case GLUT_KEY_PAGE_UP:      
		lightPos[2] -= 0.5f;
		break;  
	case GLUT_KEY_PAGE_DOWN:
		lightPos[2] += 0.5f;
		break;  
	}
	printf("lightPos %f %f %f\n", lightPos[0], lightPos[1], lightPos[2]);
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
    glutInitWindowSize( 512, 512 );
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
