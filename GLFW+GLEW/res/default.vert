#version 460
layout(std140, binding = 0) uniform MatrixBlock
{
    mat4 MVP;
};
in vec2 vPos;
in vec3 vCol;
out vec3 color;

void main()
{
    gl_Position = MVP * vec4(vPos, 0.0, 1.0);
    color = vCol;
}
