#version 460

// In params
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec3 a_texcoord;

// Out params
out vec4 color;

// Uniforms
layout(std140, binding = 0) uniform MatrixBlock
{
    mat4 MVP;
};

void main()
{
    gl_Position = MVP * vec4(a_position.x, a_position.y, a_position.z, 1.0);
    color = a_color;
}
