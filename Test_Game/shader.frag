#version 140 

uniform sampler2D gSampler;

smooth in vec3 outDiffuse; 
smooth in vec3 outNormal;
smooth in vec2 outTexCoord;

out vec4 outputColor; 

void main() 
{ 
	vec3 lightdir = vec3(0.5f,0.5f,-0.5f);
	vec3 Ambient = vec3(0.1,0.1,0.1);
	float mag = dot(normalize(lightdir),normalize(outNormal));
	outputColor = vec4(Ambient + (texture(gSampler,outTexCoord).rgb*outDiffuse*(mag)),1); 
}