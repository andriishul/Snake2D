#version 450

in VS_OUT {
    vec2 TexCoords;
    vec3 Color;
} fs_in;

uniform sampler2D u_Texture;

void main()
{    
   vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_Texture, fs_in.TexCoords).r);
   gl_FragColor = sampled * vec4(fs_in.Color, 1.0);
}  