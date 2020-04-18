#version 330 core
uniform sampler2D Texture0;

in vec2 vTexCoord;
out vec4 Outcolor;

void main() { 
    vec3 tex = vec3(texture(Texture0, vTexCoord));
    Outcolor = vec4(tex, 1.0);
}