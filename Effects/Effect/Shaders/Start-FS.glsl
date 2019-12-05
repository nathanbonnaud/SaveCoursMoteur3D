#version 420

#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_bindless_texture : enable

uniform sampler2D fboIn;

in vec3 texCoord;
layout (location = 0) out vec4 Color;


void main()
{
	Color =texture(fboIn, texCoord.xy);

}
