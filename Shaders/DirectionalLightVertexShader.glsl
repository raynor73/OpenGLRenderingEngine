#version 330

layout(location = 0) in vec3 positionAttribute;
layout(location = 1) in vec3 normalAttribute;
//attribute vec2 uvAttribute;

uniform mat4 mvpMatrixUniform;
uniform mat4 modelMatrixUniform;
/*uniform mat4 lightMvpMatrixUniform;
uniform mat4 biasMatrixUniform;*/

//varying vec2 uvVarying;
varying vec3 normalVarying;
varying vec3 positionVarying;
//varying vec4 shadowMapUvVariying;

void main() {
    //uvVarying = uvAttribute;
    //shadowMapUvVariying = biasMatrixUniform * lightMvpMatrixUniform * vec4(vertexCoordinateAttribute, 1.0);

    normalVarying = (modelMatrixUniform * vec4(normalAttribute, 0.0)).xyz;
    vec4 position = vec4(positionAttribute, 1.0);
    gl_Position =  mvpMatrixUniform * position;
}
