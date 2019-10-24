
#ifndef _GOBLIM_BUR_EFFECT
#define _GOBLIM_BUR_EFFECT

#include "Engine/OpenGL/EffectGL.h"
class Blur : public EffectGL
{
	public:
		Blur(std::string name);
		~Blur();

		virtual void apply(GPUFBO *in);
		virtual void displayInterface();

		


	
	protected:
		
		GLProgram *vp;
		

};
#endif
