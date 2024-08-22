#version 460

// In params
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_texcoord;

// Out params
out vec4 frag_color;
out float frag_time;
out vec2 frag_texcoord;

// Uniforms
layout(std140, binding = 0) uniform MatrixBlock
{
    mat4 MVP;
    float time;
};

void main()
{
    gl_Position = MVP * vec4(a_position.x, a_position.y, a_position.z, 1.0);
    frag_color = a_color;
    frag_time = time;
}
