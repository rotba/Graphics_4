#version 330 core

// Ouput data
uniform sampler2D tex;
uniform vec3 lightDirection;
uniform vec3 lightColor;
varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 color0;

// Values that stay constant for the whole mesh.
uniform vec4 PickingColor;
out vec4 color;

void main(){
	
	color = PickingColor;

}