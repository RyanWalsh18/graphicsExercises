#version 410

// Input variables from the vertex shader
in vec3 v2fColor;
in vec3 v2fNormal;

// Uniform variables
uniform vec3 uBaseColor;
uniform vec3 uLightDir; 
uniform vec3 uLightDiffuse; 
uniform vec3 uSceneAmbient;  

// Output attribute
layout(location = 0) out vec3 oColor;

void main()
{
    vec3 normal = normalize(v2fNormal);
    
    float nDotL = max(0.0, dot(normal, uLightDir)); 
    oColor = (uSceneAmbient + nDotL * uLightDiffuse) * v2fColor; 
}
