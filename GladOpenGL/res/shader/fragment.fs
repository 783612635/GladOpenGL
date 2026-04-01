#version 330 core
uniform vec4 setColor;
uniform float alpha;

in vec3 myColor;
in vec2 myTexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

void main()
{
    //不能直接取反，注意坐标范围，纹理坐标是[0,1]
   vec2 testTexCoord = vec2(1.0-myTexCoord.x,myTexCoord.y);
   FragColor = mix(texture(ourTexture, myTexCoord),texture(ourTexture2, testTexCoord),alpha);
}