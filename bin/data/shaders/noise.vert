

attribute vec4 position;
attribute vec4 color;
attribute vec4 normal;
attribute vec2 texcoord;
varying vec2 texCoordVarying;

uniform mat4 modelViewProjectionMatrix;


void main() {

    //get our current vertex position so we can modify it

   // gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;//NORMAL SHADER
    
    
    //
   vec4 pos = modelViewProjectionMatrix * position;  //GLES AND WEB
    gl_Position = pos;
}
