#version 430

#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_bindless_texture : enable

/* récupère les textures dans le GPU */
layout(std140) uniform CPU{
	sampler2D my_sampler;
	sampler2D my_sampler2;
	float timer;
	float coeff;
	vec3 pos_lum;
	vec3 pos_cam;
};

layout (location = 0) out vec4 Color;
in vec3 v_Pos;
in vec2 coord;
in vec3 v_Tangent1;
in vec3 v_Normal2;


void main()
{
	vec4 color= texture(my_sampler,coord);
    vec2 p = (v_Pos.xz / vec2(20,20)) - 0.1;	
	p.x = dot(p,p)*2.5;
    float sx = .65 * (p.x * p.x * 1. - .6) * sin(69. * p.x - 9.  *timer* coeff);
    Color = vec4(40. / (800. * abs(p.y - sx)), 0.25, (40. / (420. * abs(p.y - sx))), 1);


}