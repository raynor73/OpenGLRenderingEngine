#version 330 core

//uniform sampler2D textureUniform;
uniform vec4 diffuseColorUniform;
//uniform bool useDiffuseColorUniform;

//varying vec2 uvVarying;

out vec4 fragColor;

void main() {
    //if (useDiffuseColorUniform) {
        fragColor = diffuseColorUniform;
    /*} else {
        gl_FragColor = texture2D(textureUniform, uvVarying) * vec4(ambientColorUniform, 1);
    }*/
}
