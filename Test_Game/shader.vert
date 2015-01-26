#version 140 

uniform mat4 gMVP;

in vec3 inPosition; 
in vec3 inNormal;
 
smooth out vec3 theColor; 

void main() 
{ 
   gl_Position = gMVP * vec4(inPosition, 1.0); 
   theColor = inPosition + gl_Position.xyz; 
}