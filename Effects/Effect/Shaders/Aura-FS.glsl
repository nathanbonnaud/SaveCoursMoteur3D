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
	vec4 Tex1 = texture(fboIn,texCoord1.xy);
	vec4 Tex2 = texture(fboBase,texCoord2.xy);
	if (Tex2.xyz == vec3(1,1,1)){
		Color = Tex1;
	}else{
		Color = Tex2;
	}

}
