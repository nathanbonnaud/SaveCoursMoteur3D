#version 430

#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_bindless_texture : enable

/* récupère les textures dans le GPU */
layout(std140) uniform CPU{
	
	vec3 pos_lum;
	vec3 pos_cam;
};

layout (location = 0) out vec4 Color;
in vec3 v_Pos;
in vec2 coord;
in vec3 v_Tangent1;
in vec3 v_Normal2;
in vec4 v_Color;


void main()
{	
	
	Color = v_Color;

}