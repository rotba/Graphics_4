#version 330

uniform sampler2D tex;
uniform vec3 lightDirection;
uniform vec3 lightColor;
varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 color0;




void main()
{
    vec3 tmp = dot(-lightDirection, normal0) * color0 ;
	gl_FragColor =  clamp(vec4(color0,1.0), 0.0, 1.0)*texture(tex,texCoord0);
}
