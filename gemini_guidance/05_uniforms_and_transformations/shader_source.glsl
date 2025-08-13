#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;

uniform mat4 model, view, projection;


void main()
{
    // multipication of marices is not commutative. so order matters
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourColor = aColor;
}