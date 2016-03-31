#version 330
#define MY_PI 3.1415926
#define LIGHT_MAX_ANGLE (10.0f)

// Interpolated values from the vertex shaders
in vec3 PositionWorldPass;
in vec3 NormalViewPass;
in vec3 EyeDirectionViewPass;
in vec3 LightDirectionViewPass;
in vec3 LightPositionViewPass;
in vec2 TexCoordPass;

// Ouput data
out vec3 outColor;

// Values that stay constant for the whole mesh.
uniform sampler2D gTextureSampler;
uniform vec4 gMaterialColor;
uniform mat4 gView;
uniform mat4 gModel;
uniform vec4 gLightPosition; // light (in world)
uniform vec4 gLightColor;

void main()
{	
	vec3 gLightDirection = (gView * gModel * vec4(0,0,1, 1)).xyz; //SHOULD BE UNIFORM
	vec3 lightColor = gLightColor.rgb;
	// Material properties
	// texture2D <-> texture ??
	vec3 materialDiffuseColor = texture2D(gTextureSampler, TexCoordPass).rgb * gMaterialColor.rgb;
	vec3 materialAmbientColor = vec3(0.1,0.1,0.1) * materialDiffuseColor;
	vec3 materialSpecularColor = vec3(1.0,1.0,1.0);
	// Normal of the computed fragment, in camera space
	vec3 N = normalize(NormalViewPass);
	// Direction of the light (from the fragment to the light)
	vec3 L = normalize(LightDirectionViewPass);
	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp(dot(N, L), 0, 1);

	// Eye vector (towards the camera)
	vec3 V = normalize(EyeDirectionViewPass);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-L, N);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp(dot(V,R), 0, 1);

	float gLightAttenuation = 0.00001; //SHOULD BE UNIFORM
	vec3 temp = LightPositionViewPass - PositionWorldPass;
	float attenuation = 1.0 / (1.0 + gLightAttenuation * pow(length(temp), 2));

	float lightToSurfaceAngle = degrees(acos(dot(-normalize(temp), normalize(gLightDirection))));
	if(lightToSurfaceAngle > 10){
		attenuation = 0.0;
	}

	outColor = 
		// Diffuse : "color" of the object
		materialDiffuseColor * lightColor * cosTheta +
		// Specular : reflective highlight, like a mirror
		materialSpecularColor * lightColor * pow(cosAlpha,400);

	outColor = outColor * attenuation;

	outColor = outColor + materialAmbientColor; // Ambient : simulates indirect lighting
}