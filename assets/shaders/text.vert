#version 450

layout (location = 0) in vec2 a_Pos; 
layout (location = 1) in vec2 a_TexCoords; 
layout (location = 2) in vec3 a_Color; 

layout(std140) uniform CameraInfo {
    mat4 u_ProjectionView;
};

out VS_OUT {
    vec2 TexCoords;
    vec3 Color;
} vs_out;

void main()
{
    gl_Position = u_ProjectionView * vec4(a_Pos, 0.0, 1.0);
    vs_out.TexCoords = a_TexCoords;
    vs_out.Color = a_Color;
}  