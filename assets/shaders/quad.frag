#version 450

in VS_OUT {
    vec2 TexCoords;
    vec3 Color;
    flat int TexID;
} fs_in;

uniform sampler2D u_Textures[32];
out vec4 FragColor;
void main() {
   vec4 color = vec4(fs_in.Color, 1.0);

    vec4 texColor = (fs_in.TexID > 0) ? texture(u_Textures[fs_in.TexID], fs_in.TexCoords) : vec4(1.0);

    FragColor = (fs_in.TexID > 0) ? texColor * color : color;

    if (FragColor.a < 0.01) discard; // Discard if alpha is close to 0
}



 