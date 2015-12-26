#version 140 

uniform mat4 gMVP;
uniform mat4 gWorld;
uniform vec3 gDiffuse;
uniform sampler2D gSampler;

in vec3 inPosition;
in vec2 inTexCoord; 
in vec3 inNormal;
 
smooth out vec2 outTexCoord; 
smooth out vec3 outNormal;
smooth out vec3 outDiffuse;

void main() 
{ 
   gl_Position = gMVP * vec4(inPosition, 1.0);
   outNormal = (gWorld* vec4(inNormal,0.0f)).xyz;
   normalize(outNormal); 
   outTexCoord = inTexCoord;
   outDiffuse = gDiffuse;
}