#version 430

#extension GL_ARB_shading_language_include : enable
#include "/Materials/Common/Common"
#line 6 


layout(std140) uniform CPU
{
	mat4 MVP;
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
	// vecteur direction de la lumière ///
	v_Pos = newPosition;
	
}


