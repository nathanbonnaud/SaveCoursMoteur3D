#version 420
ml
#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_bindless_texture : enable

uniform sampler2D my_sampler_blur;

in vec3 texCoord;
layout (location = 0) out vec4 Color;

void main()
{

	vec4 colBase = texture(my_sampler_blur,texCoord.xy);
	
	for (int i = -4; i < 4; i++) {
		for (int j = -4; j < 4; j++) {
			 colBase += texture(my_sampler_blur,vec2(texCoord.x + i * 1 / 1024, texCoord.y + j * 1 / 1024));
			
		}
	}
	colBase = colBase / 64;
	Color =  colBase;
}
