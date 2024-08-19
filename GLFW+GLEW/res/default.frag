#version 460

// In params
in vec4 frag_color;
in float frag_time;

// Out params
out vec4 fragment;

void main()
{
    fragment = vec4(frag_color.r, sin(frag_time) * 0.5 + 0.5, frag_color.g, frag_color.a);
}