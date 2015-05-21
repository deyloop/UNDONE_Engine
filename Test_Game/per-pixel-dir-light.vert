#version 140

uniform mat4 gMVP;
uniform mat4 gWorld;
uniform vec3 gDiffuse;

in vec3 inPosition; 
in vec3 inNormal;
 
smooth out vec3 outDiffuse; 
smooth out vec3 outNormal;

void main() 
{ 
   gl_Position = gMVP * vec4(inPosition, 1.0);
   outNormal = (gWorld* vec4(inNormal,0.0f)).xyz;
   normalize(outNormal); 
   outDiffuse = gDiffuse;
}