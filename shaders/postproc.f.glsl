#version 330

#define KERNEL_SIZE 3

uniform float textureMode;
uniform mat3 convMatrix;
uniform sampler2D fbo_texture;

in vec2 UV;
out vec3 color;

void main()
{
	color = vec3(0, 0, 0);
	
	// Convolution
	if (0 == textureMode)
	{
		// Retrieving texture's data
		vec3[KERNEL_SIZE*KERNEL_SIZE] textureData;
		vec2 textureDims = textureSize(fbo_texture, 0) / 2.0;
		int padding = KERNEL_SIZE % 2;
		
		for(int i = -padding; i < KERNEL_SIZE - padding; i++)
		{
			for(int j = -padding; j < KERNEL_SIZE - padding; j++)
			{
				textureData[(i+1)*KERNEL_SIZE + (j+1)] = texture(fbo_texture, UV + 1.0/textureDims * vec2(i, j)).xyz;
			}
		}
		
		// Applying convolution
		for(int i = 0; i < KERNEL_SIZE; i++)	
		{
			for(int j = 0; j < KERNEL_SIZE; j++)
			{
				color.xyz += textureData[i*KERNEL_SIZE + j] * convMatrix[i][j];
			}
		}
	}
	//else if ()
}