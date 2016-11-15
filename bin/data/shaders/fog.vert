attribute vec4 position;
uniform mat4 modelViewProjectionMatrix;
varying vec2 texCoordVarying;
attribute vec2 texcoord;

void main(){
texCoordVarying=texcoord;
gl_Position=modelViewProjectionMatrix * position;
}
