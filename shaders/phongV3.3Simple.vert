#version 330

layout(location = 0) in vec4 position;

out vec4 fragColor;

uniform mat4 gModel, gView, gProjection;
//uniform vec4 gLightPosition; // light (in world)
//uniform vec3 gEyePosition; // camera (in world)

uniform bool isTeapot;

void main()
{
	mat4 MVP = gProjection * gView * gModel;
	
	// Output position of the vertex, in clip space : gMVP * position
	gl_Position =  MVP * position;

	if (isTeapot)
	{
		fragColor = vec4(0.8, 0.3, 0.1, 1.0);
	}
	else
	{
		fragColor = vec4(0.4, 0.0, 0.2, 1.0);
	}
	
}
