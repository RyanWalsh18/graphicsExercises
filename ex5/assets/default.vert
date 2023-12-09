#version 410

// Input attributes
layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec3 iColor;
layout( location = 2 ) in vec3 iNormal; 

// Uniform variable (no location qualifier needed for uniforms)
uniform mat4 uProjCameraWorld;
uniform mat3 uNormalMatrix;

// Output attributes
out vec3 v2fColor;
out vec3 v2fNormal; 

// Main function, run for each vertex processed
void main()
{
    // Copy input color to output color attribute
    v2fColor = iColor;

    // Copy position to built-in gl_Position attribute
    gl_Position = uProjCameraWorld * vec4(iPosition, 1.0);
    
    v2fNormal = normalize(uNormalMatrix * iNormal); 
}

