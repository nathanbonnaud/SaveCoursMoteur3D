#version 420

#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_bindless_texture : enable

uniform sampler2D fboIn;

in vec3 texCoord;
layout (location = 0) out vec4 Color;


void main()
{	
	
	vec4 colBase = texture(fboIn,texCoord.xy);
	vec3 somme = colBase.xyz;
	//if (gl_FragCoord.y < 1024/2){
		somme = vec3(0.,0.,0.);
		for(float x =-4; x<4;x++){
			for(float y = -4; y<4;y++){

				vec4 colBase = texture(fboIn,vec2(texCoord.x +x/1024,texCoord.y + y/1024));
				somme += colBase.xyz;
			}
		}
		somme /= 64;
		//}
	
	Color = vec4(somme,1.0);
}
