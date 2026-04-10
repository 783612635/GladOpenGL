#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec2 myTexCoord;
out vec3 FragPos;
out vec3 Normal;

void main()
{
	gl_Position = Projection*View*Model*vec4(aPos.x, aPos.y, aPos.z, 1.0);
	myTexCoord = aTexCoord;
	FragPos = vec3(Model*vec4(aPos,1.0));
	Normal = mat3(transpose(inverse(Model))) *aNormal;
	//Normal =aNormal;
}