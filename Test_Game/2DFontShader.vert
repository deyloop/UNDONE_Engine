#version 140

uniform mat4	gMVP;

in vec2 inPosition; 
in vec2 inTexCoord;
in int inVertIndices;

out vec2 outTexCoord;

void main() 
{	
	gl_Position = gMVP * vec4(inPosition,0.0f,1.0f);
	

	outTexCoord = inTexCoord;
}