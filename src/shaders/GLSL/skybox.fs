#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{    
    vec4 texColor = texture(skybox, TexCoords);

    if(texColor == vec4(0.0, 0.0, 0.0, 1.0)) 
    {
        FragColor = vec4(TexCoords, 1.0); // if all black turn to rgb
    } 

    else 
    {
        FragColor = texColor; // Otherwise, use the sampled texture color
    }
}


