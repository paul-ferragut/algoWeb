precision highp float;
uniform vec4 u_fogColor;
uniform float u_fogMinDist;
varying vec2 texCoordVarying;

void main()
{
float distance=u_fogMinDist;
const float LOG2=1.442695;
float z = gl_FragCoord.z / gl_FragCoord.w;
float fogFactor=exp2(-distance*distance*z*z*LOG2);
fogFactor=clamp(fogFactor,0.0,1.0);
    vec4 frag_color =u_fogColor;
    frag_color.a=0.0;
    vec4 fog_color=u_fogColor;
    gl_FragColor=mix(fog_color,frag_color,fogFactor);
}
