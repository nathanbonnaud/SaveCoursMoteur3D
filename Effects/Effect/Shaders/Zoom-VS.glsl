#version 420

#extension GL_ARB_shading_language_include : enable

layout(std140) uniform CPU
{
	mat4 MVP;
	vec3 color;
};
 out gl_PerVertex {
        vec4 gl_Position;
        float gl_PointSize;
        float gl_ClipDistance[];
    };

layout (location = 0) in vec3 Position;

out vec3 texCoord1;
out vec3 texCoord2;

void main()
{
	
	gl_Position = vec4(Position,1.0);
	texCoord2 = 0.5*(Position.xyz+1.0);
	vec3 newPosition = vec3(texCoord2.x*0.98-100/2048,texCoord2.y*0.98,texCoord2.z*0.98);
	texCoord1 = newPosition;
}
