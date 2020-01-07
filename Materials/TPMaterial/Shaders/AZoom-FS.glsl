#version 430

#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_bindless_texture : enable


layout (location = 0) out vec4 Color;

in vec4 v_Color;


void main()
{	
	
	Color = v_Color;

}