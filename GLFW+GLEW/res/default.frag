#version 460

// In params
in vec4 color;

// Out params
out vec4 fragment;

void main()
{
    fragment = vec4(color);
}