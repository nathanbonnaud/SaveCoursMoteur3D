#version 430

#extension GL_ARB_shading_language_include : enable
#include "/Materials/Common/Common"
#line 6 


layout(std140) uniform CPU
{
	int w;
	int h;

	vec3 CPU_color;
	mat4 MVP;
	//float timer;
};

 out gl_PerVertex {
        vec4 gl_Position;
        float gl_PointSize;
        float gl_ClipDistance[];
    };
layout (location = 0) in vec3 Position;
layout(location = 2) in vec3 Normal;
layout(location = 3) in vec3 Texture;
layout(location = 4) in vec3 Tangent;

out vec3 v_Pos ;
out vec2 coord;
out vec3 v_Tangent1;
out vec3 v_Normal2;


void main()
{	
	
	coord = Texture.xy;
	vec3 newPosition = Position;
	gl_Position = MVP * vec4(newPosition, 1.0);
	v_Tangent1 = Tangent;
	v_Normal2 = Normal;
	// vecteur direction de la lumi�re ///
	v_Pos = newPosition;
	
	//v_Color = vec4(Texture,1.0);

	/// BI GOUT //

	/*
	if (Position.z < 0) {

		vec3 newPosition = Position;
		newPosition += vec3(0.5,0,0);
		gl_Position = MVP * vec4(newPosition, 1.0);
		v_Color = vec4(gl_Position.xyz/gl_Position.w, 1.0);
	}
	else {
		v_Color = vec4(abs(Normal),1.0);

	}
	*/

}


