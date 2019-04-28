#version core 3.3

/* layout(location = 0) in vec3 vPos; */
layout(location = 0) out vec4 vColor;

void main()
{
    /* gl_Position = vec4(vPos, 1.0); */
    vColor = vec4(0.0, 0.0, 1.0, 1.0);
}
