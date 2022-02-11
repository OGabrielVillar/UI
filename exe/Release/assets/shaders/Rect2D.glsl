#type vertex
#version 330 core
		
layout(location = 0) in vec2 a_Position;

uniform vec2 u_Resolution;
uniform vec2 u_RectPosition;
uniform vec2 u_RectSize;
uniform vec4 u_Color;
			
out vec4 v_Color;

void main()
{
	v_Color = u_Color;
	vec2 position = (a_Position * u_RectSize) + u_RectPosition;
	position = (position / u_Resolution) * 2.0 - 1.0;
	gl_Position = vec4(position.x, -position.y, 0.0, 1.0);
}

#type fragment
#version 330 core
		
layout(location = 0) out vec4 color;

in vec4 v_Color;

void main()
{
	color = vec4(v_Color.x, v_Color.y, v_Color.z, 1.0);
}
