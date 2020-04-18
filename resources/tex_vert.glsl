#version 330 core
layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertNor;
layout(location = 2) in vec2 vertTex;
uniform mat4 P;
uniform mat4 M;
uniform mat4 V;

out vec2 vTexCoord;

void main() {
    /* First model transforms */
    gl_Position = P * V * M * vec4(vertPos.xyz, 1.0);

    /* pass through the texture coordinates to be interpolated */
    vTexCoord = vertTex;
}
