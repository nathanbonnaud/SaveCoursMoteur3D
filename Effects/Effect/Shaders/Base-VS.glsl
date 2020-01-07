#version 420

#extension GL_ARB_shading_language_include : enable
/*
	Ce Vextex Shader sert de Vertex Shaders pour tous les effets.
*/

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

out vec3 texCoord;

void main()
{
	
	gl_Position = vec4(Position,1.0);
	texCoord = 0.5*(Position.xyz+1.0);
}
