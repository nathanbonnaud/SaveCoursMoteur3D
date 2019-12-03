

#include "../../../Core/Engine/OpenGL/EffectGL.h"
class mainEffect : public EffectGL
{
public:
	mainEffect(std::string name);
	~mainEffect();

	virtual void apply(GPUFBO* in,GPUFBO* out);
	virtual void displayInterface();
	void Bloom(GPUFBO* in, GPUFBO* out);




protected:

	GLProgram* vp_Base;
	GLProgram* fp_action1;
	GLProgram* fp_action2;
	GPUFBO* effect_1;
	GPUFBO* effect_2;
	GPUsampler* var1;
	GPUsampler* var2;
	GPUsampler* var3;
	GPUsampler* var4;
	GPUsampler* var5;
	
	



};