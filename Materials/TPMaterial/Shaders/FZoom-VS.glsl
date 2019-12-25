#version 430

#extension GL_ARB_shading_language_include : enable
#line 6 


layout(std140) uniform CPU
{
	int w;
	int h;

	vec3 CPU_color;
	mat4 MVP;
	float timer;
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
out vec4 v_Color;

void main()
{	
	
	coord = Texture.xy;
	vec3 newPosition = Position;
	v_Tangent1 = Tangent;
	v_Normal2 = Normal;
	v_Pos = newPosition;
	
	//v_Color = vec4(Texture,1.0);

	/// BI GOUT //
	if ( Position.y > timer -0.25 && Position.y < timer+0.25) {
		v_Color = vec4(vec3(1,0,5),0.5);
		if(v_Pos.x < 0){
			newPosition.x = newPosition.x -0.2;
		}else{
			newPosition.x = newPosition.x +0.2;

		}
		}
	else {
		v_Color = vec4(vec3(0,0.8,1),0.5);

	}
		gl_Position = MVP * vec4(newPosition, 1.0);


}


