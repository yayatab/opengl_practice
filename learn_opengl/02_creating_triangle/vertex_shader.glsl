#version 330 core
//right now we only use position. so we only need a vector of three points (a position)
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}