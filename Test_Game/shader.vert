#version 140 

uniform mat4 gMVP;
uniform mat4 gWorld;
uniform vec3 gDiffuse;

in vec3 inPosition; 
in vec3 inNormal;
 
smooth out vec3 theColor; 

void main() 
{ 
   gl_Position = gMVP * vec4(inPosition, 1.0);
   vec3 transNormal = (gWorld* vec4(inNormal,0.0f)).xyz;
   normalize(transNormal); 
   vec3 lightdir = vec3(0.5f,0.5f,-0.5f);
   vec3 light2dir = vec3(0.5,-0.5,5.0f);
   vec3 Ambient = vec3(0.1,0.1,0.1);
   float mag = dot(normalize(lightdir),transNormal);
   theColor = Ambient + (gDiffuse*(mag));
}