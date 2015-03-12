#version 140

uniform mat4	gMVP;
uniform float	gRect[8];

in vec3 inPosition; 
in vec2 inTexCoord;
in int inVertIndices;

out vec2 outTexCoord;

void main() 
{	
	gl_Position = gMVP*vec4(inPosition/*.x+gRect[inVertIndices],
							inPosition.y+gRect[inVertIndices+1],
							inPosition.z*/,
							1.0f);

	outTexCoord = inTexCoord;
	//outTexCoord = vec2(gRect[inVertIndices],
	//				   gRect[inVertIndices+1]);
}