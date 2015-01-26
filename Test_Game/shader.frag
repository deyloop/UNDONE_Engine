#version 140 

smooth in vec3 theColor; 
out vec4 outputColor; 

void main() 
{ 
   outputColor = vec4(theColor + vec3(0.5f), 1.0); 
}