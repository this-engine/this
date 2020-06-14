layout(location = 0) in vec4 vertex;
layout(location = 1) in vec3 normal;
out vec3 vert;
out vec3 vertNormal;
out vec3 color;
uniform mat4 projMatrix;
uniform mat4 camMatrix;
uniform mat4 worldMatrix;
uniform mat4 myMatrix;

void main() 
{
   ivec2 pos = ivec2(gl_InstanceID % 32, gl_InstanceID / 32);
   vec2 t = vec2(float(-16 + pos.x) * 0.8, float(-18 + pos.y) * 0.6);
   mat4 wm = myMatrix * worldMatrix;
   color = vec3(0.4, 1.0, 0.0);
   vert = vec3(wm * vertex);
   vertNormal = mat3(transpose(inverse(wm))) * normal;
   gl_Position = projMatrix * camMatrix * wm * vertex;
};
