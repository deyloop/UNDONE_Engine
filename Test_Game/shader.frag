#version 140 

uniform sampler2D gSampler;
smooth in vec3 theColor; 
smooth in vec2 outTexCoord;
out vec4 outputColor; 

void main() 
{ 
   //outputColor = vec4(theColor,1);
   outputColor = mix(texture(gSampler,outTexCoord),vec4(theColor,1.0f),vec4(0.5f)); 
}