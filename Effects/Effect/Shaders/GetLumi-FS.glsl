#version 420


uniform sampler2D fboIn;

in vec3 texCoord;
layout (location = 0) out vec4 Color;

void main()
{		
		vec4 myColor = texture(fboIn,texCoord.xy);
		if ( myColor.r > 0.05&& myColor.g > 0.05 && myColor.b >0.05){
			Color = myColor;
		}else{
			Color = vec4(0.,0.,0.,1.);
		}
}


