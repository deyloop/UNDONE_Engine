#version 140

smooth in vec3 outDiffuse;
smooth in vec3 outNormal;

out vec4 outColor;

void main(){
	vec3 lightdir = vec3(0.5f,0.5f,-0.5f);
	vec3 light2dir = vec3(0.5,-0.5,5.0f);
	vec3 Ambient = vec3(0.1,0.1,0.1);
	float mag = dot(normalize(light2dir),normalize(outNormal));
	outColor = vec4(Ambient + (outDiffuse*(mag)),1);
}