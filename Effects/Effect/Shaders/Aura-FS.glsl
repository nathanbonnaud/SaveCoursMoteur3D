#version 420

#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_bindless_texture : enable

uniform sampler2D fboIn;
uniform sampler2D fboBase;

layout (location = 0) out vec4 Color;
in vec3 texCoord1;

in vec3 texCoord2;


void main()
{
	Color = vec4(1,0,0,1);

}
