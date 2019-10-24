#version 430

#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_bindless_texture : enable

#include "/Materials/Common/Lighting/Lighting"
#line 6 

/* r�cup�re les textures dans le GPU */
layout(std140) uniform CPU{
	sampler2D my_sampler;
	sampler2D my_sampler2;
	vec3 pos_lum;
	vec3 pos_cam;
};

layout (location = 0) out vec4 Color;
in vec3 v_Pos;
in vec2 coord;



void main()
{
	
	vec4 colorTmp1 = texture(my_sampler, coord);
	vec4 colorTmp2 = texture(my_sampler2, coord);
	vec3 tempo = (colorTmp2.w * colorTmp2.xyz + (1.0 - colorTmp2.w) * colorTmp1.xyz);
	
	vec3 v_Normal = colorTmp2.xyz/colorTmp2.w * 2 - 1;
	//vec4 pixel = gl_FragCoord/(v_screenSize.x);
	//Color = (pixel); 
	vec3 v_Lum = normalize(pos_lum - v_Pos);

	// "dot" calcule de cosinus entre 2 vecteurs //
	float cosAngle = dot(v_Lum, v_Normal);

	// Reflection parfaite de ma lumi�re //
	vec3 R = reflect(v_Lum, v_Normal);

	/// Point de vue de la camera //
	vec3 V = normalize(pos_cam - v_Pos);

	float cosAngle2 = dot(R, V);


	/// Lumi�re de l' "objet" avec la lumi�re envoy�//
	vec3 v_Diff = tempo * max(cosAngle, 0);

	// Reflet de la lumiere par rapport � la camera //
	vec3 v_Final = vec3(0.9, 0.9, 0.8) * pow(max(cosAngle2, 0), 100);

	/// Ombre de l' "objet" de la lumi�re envoy� //

	vec3 Lumi = vec3(0.1, 0.1, 0) + v_Diff + v_Final;

	
	Color = vec4(Lumi, 1.0);

	//Color = vec4(1.0, 0.0, 1.0, 1.0);

}