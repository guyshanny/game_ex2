#version 330

#define M_PI 3.1415926
#define KERNEL_SIZE 3

uniform int textureMode;

// convolutionEffect effect
uniform mat3 convMatrix;

// waveEffect effect
uniform float offset;

// Swirl effect
uniform float swirlRadius = 0.4;
uniform float time;
uniform float shockWaveElapsedTime;

// ShockWave effect
uniform vec2 mousePos;
uniform vec3 shockParams = vec3(10.f, 0.8f, 0.1f);

// Action based effect
uniform vec3 teapotPos;
uniform sampler2D fbo_texture;

in vec2 UV;
out vec3 color;

// Conv & glow
#define TEXTURE_POS (UV + 1.0/textureDims * vec2(i,j))

// Based on ImageProcessing course & https://en.wikipedia.org/wiki/Kernel_(image_processing)
vec3 convolutionEffect()
{
	vec3 retColor = vec3(0, 0, 0);
	
	// Retrieving texture's data
	vec3[KERNEL_SIZE*KERNEL_SIZE] textureData;
	vec2 textureDims = textureSize(fbo_texture, 0) / 2.0;
	int padding = KERNEL_SIZE % 2;
	
	for(int i = -padding; i < KERNEL_SIZE - padding; i++)
	{
		for(int j = -padding; j < KERNEL_SIZE - padding; j++)
		{
			textureData[(i+1)*KERNEL_SIZE + (j+1)] = texture(fbo_texture, TEXTURE_POS).xyz;
		}
	}
	
	// Applying convolutionEffect
	for(int i = 0; i < KERNEL_SIZE; i++)	
	{
		for(int j = 0; j < KERNEL_SIZE; j++)
		{
			retColor += textureData[i*KERNEL_SIZE + j] * convMatrix[i][j];
		}
	}
	
	return retColor;
}

// Based on https://en.wikibooks.org/wiki/OpenGL_Programming/Post-Processing
vec3 waveEffect()
{
	vec3 retColor = vec3(0, 0, 0);
	vec2 texcoord = UV;
	texcoord.x += sin(texcoord.y * 4*2*3.14159 + offset) / 100;
	return texture(fbo_texture, texcoord);
}

// Based on http://www.geeks3d.com/20110428/shader-library-swirl-post-processing-filter-in-glsl/
vec3 swirlTimeBasedEffect()
{
	// Position swirl UV coord in the middle of the screen
	vec2 swirlUVcoord = UV - vec2(0.5, 0.5);
	float dist = length(swirlUVcoord);
	if (dist < swirlRadius)
	{
		// Time based
		float timeFactor = sin(0.06 * time);
		float swirlFactor = 0.f;
		if (timeFactor <= 0.5f) { swirlFactor = timeFactor / 0.5f; }
		else { swirlFactor = (1-timeFactor) / 0.5f; }			
		
		float percent = (swirlRadius - dist) / swirlRadius;
		float theta = percent * percent * swirlFactor * M_PI;
		float s = sin(theta);
		float c = cos(theta);
		swirlUVcoord = mat2(c, s, -s, c) * swirlUVcoord;
	}
	
	swirlUVcoord += vec2(0.5, 0.5);
	return texture(fbo_texture, swirlUVcoord).xyz;
}

// Based on http://www.learnopengl.com/#!Advanced-Lighting/Bloom
vec3 glowTimeBasedEffect()
{
	vec3 retColor = vec3(0, 0, 0);
	
	// radius depends on time (makes it time based)
	int radius = abs(int(round(time / 7)) % 4 - 3) * 2 + 4;
	int padding = (radius - 1) / 2;
	vec2 textureDims = textureSize(fbo_texture, 0) / 2.0;
	
	for (int i = -padding ; i < padding ; i++)
		for (int j = -padding ; j < padding ; j++)
			retColor += texture(fbo_texture, TEXTURE_POS).xyz;
	
	// Normalize
	retColor = retColor / pow(radius, 2);
	
	// Adding color of UV (compensate blurring)
	retColor += texture(fbo_texture, UV).xyz;
	
	return retColor;
}

// Based on http://www.geeks3d.com/20091116/shader-library-2d-shockwave-post-processing-filter-glsl/
vec3 shockwaveEffect()
{
	vec2 shockWaveCoord = UV;
	float distance = length(UV);
	if ((distance <= (time + 0.5)) && 
		(distance >= (time - 0.5)))
	{
		float diff = (distance - time); 
		float powDiff = 1.0 - pow(abs(diff*shockParams.x), shockParams.y); 
		float diffTime = diff  * powDiff; 
		vec2 diffUV = normalize(UV); 
		shockWaveCoord = UV + (diffUV * diffTime);
	}

	return texture(fbo_texture, shockWaveCoord).xyz;
}

void main()
{
	switch (textureMode)
	{
		case 0:	
			color = convolutionEffect();
		break;
		
		case 1:
			color = waveEffect();
		break;
		
		case 2:
			color = swirlTimeBasedEffect();
		break;
		
		case 3:
			color = shockwaveEffect();
		break;
		
		case 4:
			color = glowTimeBasedEffect();
		break;
		
		default:
			color = vec3(0, 0, 0);
		break;
	}
}