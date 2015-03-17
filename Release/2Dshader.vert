#version 140

uniform mat4 gMVP;
uniform vec2 gTranslation;
uniform vec2 gScaling;
uniform vec2 gRotation;

in vec3 inPosition; 
in vec2 inTexCoord;

out vec2 outTexCoord;

void main() 
{ 
	vec3 ScaledPos =  vec3(gScaling, 1.0f) * inPosition ;
	vec3 correctedPos = ScaledPos + vec3(-1.0f,1.0f,0.0f);
	vec3 translatedPos = correctedPos + vec3(gTranslation,0.0f);
	gl_Position = vec4(translatedPos, 1.0f);
	outTexCoord = inTexCoord;
}