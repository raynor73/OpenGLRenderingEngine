#version 150

attribute vec3 positionAttribute;
//attribute vec2 uvAttribute;

uniform mat4 mvpMatrixUniform;

//varying vec2 uvVarying;

void main() {
    //uvVarying = uvAttribute;

    vec4 position = vec4(positionAttribute, 1.0);
    gl_Position =  mvpMatrixUniform * position;
}
