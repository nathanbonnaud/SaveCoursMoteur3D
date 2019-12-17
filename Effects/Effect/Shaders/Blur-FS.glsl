#version 420

#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_bindless_texture : enable

uniform sampler2D fboIn;
layout(std140) uniform CPU{
		int n;
};
in vec3 texCoord;
layout (location = 0) out vec4 Color;


void main()
{	
	
	vec4 colBase = texture(fboIn,texCoord.xy);
	vec3 somme = colBase.xyz;
		somme = vec3(0.,0.,0.);
		for(float x =-n/2; x<n/2;x++){
			for(float y = -n/2; y<n/2;y++){

				vec4 colBase = texture(fboIn,vec2(texCoord.x +x/1024,texCoord.y + y/1024));
				somme += colBase.xyz;
			}
		}
		somme /= n*n;
	
	Color = vec4(somme,1);
}
