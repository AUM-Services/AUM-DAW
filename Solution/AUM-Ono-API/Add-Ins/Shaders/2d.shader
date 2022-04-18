Read shader vertex
#version 330 core

attribute vec2 coord2d;

void main()
{
	gl_Position = vec4(coord2d, 0.0, 1.0);
}

Read shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 UNIFORM_COLOR = vec4(.81, 0.81, 0.81, .81);

void main()
{
	color = UNIFORM_COLOR;
}