#version 330 core
out vec4 FragColor;

void main()
{
    // High Red (1.0), Medium Green (0.5), No Blue (0.0), Solid Alpha (1.0)
    FragColor = vec4(1.0f, 0.5f, 0.0f, 1.0f); // Real Orange color
}