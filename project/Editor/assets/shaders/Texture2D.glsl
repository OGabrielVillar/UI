#type vertex
#version 330 core
		
layout(location = 0) in vec2 a_Position;

uniform vec2 u_Resolution;
uniform vec2 u_RectPosition;
uniform vec2 u_RectSize;
			
out vec2 v_TexCoord;

void main()
{
	v_TexCoord.x =  a_Position.x;
	v_TexCoord.y = -a_Position.y;
	vec2 position = (a_Position * u_RectSize) + u_RectPosition;
	position = (position / u_Resolution) * 2.0 - 1.0;
	gl_Position = vec4(position.x, -position.y, 0.0, 1.0);
}
		
#type fragment
#version 330 core
		
layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	color = texture(u_Texture, v_TexCoord);
}
