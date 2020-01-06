#version 420

#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_bindless_texture : enable

uniform sampler2D fboIn;
uniform	sampler2D fboBase;
layout(std140) uniform CPU{
		int timer;
};
in vec3 texCoord;
layout (location = 0) out vec4 Color;


void main()
{
	
	vec4 color =(texture(fboBase, texCoord.xy)+texture(fboIn, texCoord.xy)); 
	color = vec4(color.x*0.75,color.y*0.5,color.z*1.4,1);

	if (color.xyz == vec3(1,1,1)){
		color = vec4(0.5,0,0.5,1);	
	}

	Color = color;
}
