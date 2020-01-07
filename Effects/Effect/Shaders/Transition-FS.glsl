#version 420


#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_bindless_texture : enable

/*
	C'est la même fonction que Circle-FS avec quelques variables adaptées.
*/

layout(std140) uniform CPU{
		float timer;
		float trans;
};

layout (location =0) out vec4 Color;
in vec3 texCoord;


void main( void ) {
	float time = 1.;
	vec2 resolution = vec2(2048,2048);

	vec2 p = (gl_FragCoord.xy - 0.275 * resolution) / min(resolution.x-500., resolution.y);
	vec3 c = vec3(0., 0., 0.);
	vec3 lightCol = vec3(1 + 0.09 * tan (6.), 0.23, 1. + 0.04 * tan (3.));
    
	for(int i = 0; i < 0+timer; ++i) {
        	float t = 0.8 * 3.14 * float(i) / 4. * fract(time * .1);
        	float x = cos(t);
        	float y = sin(t);
        	vec2 o = .5 * vec2(x  * fract( .1) - sin (0.4) * y*2.0, y);
        	c += 0.02 / (length(p-0.3)) * lightCol * 0.6;
	}

	
	Color = vec4(c,1*trans);
}