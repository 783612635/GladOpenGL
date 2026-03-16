#version 330 core
uniform vec4 setColor;
out vec4 FragColor;
void main()
{
   FragColor = setColor;
}