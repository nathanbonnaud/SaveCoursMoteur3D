

#include "../../../Core/Engine/OpenGL/EffectGL.h"
class mainEffect : public EffectGL
{
public:
	mainEffect(std::string name);
	~mainEffect();

	virtual void apply(GPUFBO* in,GPUFBO* out);
	virtual void displayInterface();
	void Bloom1(GPUFBO* in, GPUFBO* out);
	void Flou(GPUFBO* in, GPUFBO* out);
	void GetLumi(GPUFBO* in, GPUFBO* out);
	void FinLumi(GPUFBO* in, GPUFBO* out, GPUFBO* tmp);
	void Circle1(GPUFBO* in, GPUFBO* out);
	void Transition(GPUFBO* in, GPUFBO* out, bool sens);
	void oneEffect(GPUFBO* in, GPUFBO* out,GLProgram* effect, GPUFBO* bind);
	



protected:
	GPUint* timer;
	GPUint* coeffBlur1;
	GPUfloat* timecircle;
	GPUfloat* coeffLumi;
	GPUfloat* transp;
	GPUfloat* transp1;
	GPUfloat* timeTrans;

	GLProgram* vp_Base;
	GLProgram* fp_action1;
	GLProgram* fp_action2;
	GLProgram* fp_simple;
	GLProgram* fp_circle;
	GLProgram* fp_trans;
	GPUFBO* effect_1;
	GPUFBO* effect_1_1;
	GPUFBO* effect_1_2;
	GPUFBO* effect_1_3;
	GPUFBO* effect_1_4;
	GPUFBO* effect_2;
	GPUFBO* effect_3;
	GPUsampler* var1;
	GPUsampler* var2;
	GPUsampler* var3;
	GPUsampler* var4;
	
};
