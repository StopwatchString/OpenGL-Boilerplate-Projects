#version 460

// In params
in vec4 frag_color;
in float frag_time;
in vec2 frag_texcoord;

uniform sampler2D tex;

// Out params
out vec4 fragment;

void main()
{
    fragment = texture(tex, frag_texcoord);
    //fragment = vec4(frag_color.r, frag_color.b, frag_color.g, frag_color.a);
}