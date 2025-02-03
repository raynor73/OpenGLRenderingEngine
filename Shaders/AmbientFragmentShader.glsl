#version 330 core

#include "./Shaders/BaseLight.glsl"

//uniform sampler2D textureUniform;
uniform vec4 diffuseColorUniform;
//uniform bool useDiffuseColorUniform;

//uniform vec3 ambientColorUniform;
uniform BaseLight ambientColorUniform;

//varying vec2 uvVarying;

out vec4 fragColor;

void main() {
    //if (useDiffuseColorUniform) {
        fragColor = diffuseColorUniform * vec4(ambientColorUniform.color, 1) * ambientColorUniform.intensity;
    /*} else {
        gl_FragColor = texture2D(textureUniform, uvVarying) * vec4(ambientColorUniform, 1);
    }*/
}
