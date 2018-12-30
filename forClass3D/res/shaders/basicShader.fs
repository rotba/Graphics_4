#version 130

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 color0;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform sampler2D tex;

void main()
{
	float epsilon = 0.1;
    vec3 tmp = dot(-lightDirection, normal0) * color0 ;
	gl_FragColor =  clamp(vec4(color0,1.0), 0.0, 1.0)*texture(tex,texCoord0);
}
