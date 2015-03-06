#version 140 

uniform sampler2D gSampler;		//from the app.

in vec2 outTexCoord;			//from the vertex shader

out vec4 outputColor; 

void main() 
{ 
   outputColor = texture(gSampler,outTexCoord); 
}