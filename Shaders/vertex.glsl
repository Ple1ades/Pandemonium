#version 330 core
layout (location = 0) in vec4 vert;
layout (location = 1) in vec2 _uv;

out vec2 uv;

void main()
{
    uv = _uv;
    gl_Position = vec4(vert.x / 1920.0, vert.y / 1080.0, 0.0, 1.0);
}