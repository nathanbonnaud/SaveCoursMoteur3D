#version 430

#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_bindless_texture : enable

/* récupère les textures dans le GPU */
layout(std140) uniform CPU{
	sampler2D my_sampler;
	sampler2D my_sampler2;
	float coeff;
	int transition;
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
	
	vec4 colorTmp1 = texture(my_sampler, coord);
	vec4 colorTmp2 = texture(my_sampler2, coord);
	
	vec3 v_Normal = normalize(v_Normal2);
	vec3 v_Tangent = normalize(v_Tangent1);
	//vec3 v_Normal = colorTmp3.xyz*2-1;
	vec3 v_Normal1 = normalize(vec3(0,0,colorTmp2));
	//vec4 pixel = gl_FragCoord/(v_screenSize.x);
	//Color = (pixel); 

	vec3 v_BiTangent = cross(v_Normal, v_Tangent);
	mat3 new_Repere = mat3(v_Tangent, v_BiTangent,v_Normal);

	vec3 v_Lum = normalize(pos_lum -v_Pos);

	vec3 new_Normal =v_Normal1;

	vec3 new_vLum = transpose(new_Repere) * v_Lum;

	// "dot" calcule de cosinus entre 2 vecteurs //
	float cosAngle = dot(new_vLum, new_Normal);

	// Reflection parfaite de ma lumière //
	vec3 R = reflect(new_vLum, new_Normal);
	
	/// Point de vue de la camera //
	vec3 v_Cam = normalize(pos_cam - v_Pos);

	//Changement de repère

	vec3 new_V =v_Cam;

	float cosAngle2 = dot(R, new_V);


	/// Lumière de l' "objet" avec la lumière envoyé//
	vec3 v_Diff = colorTmp1.xyz * max(cosAngle, 0);

	// Reflet de la lumiere par rapport à la camera //
	vec3 v_Final = vec3(1.0, 1.0, 1.0) * pow(max(cosAngle2, 0), 50);

	/// Ombre de l' "objet" de la lumière envoyé //

	vec3 Lumi;
	if(transition ==0){
		Lumi = (0.1,0.1,0) + v_Diff + v_Final*0.45;
	}else{
		Lumi = (0.1,0.1,0) + v_Diff + v_Final;
	}

	
	Color = vec4(Lumi, 1.0)*coeff;


}