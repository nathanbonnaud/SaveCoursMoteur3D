#include "mainEffect.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Engine.h"

int coeff;

mainEffect::mainEffect(std::string name) :
	EffectGL(name, "Effect")
{
	coeff = 30;
	/*
		Vertex.
	*/
	vp_Base = new GLProgram(this->m_ClassName + "-Base", GL_VERTEX_SHADER);

	/*
		Fragments.
	*/

	//bloom
	fp_action1 = new GLProgram(this->m_ClassName + "-GetLumi", GL_FRAGMENT_SHADER);
	fp_action2 = new GLProgram(this->m_ClassName + "-Blur", GL_FRAGMENT_SHADER);
	fp_simple = new GLProgram(this->m_ClassName + "-FinBl", GL_FRAGMENT_SHADER);
	fp_lumi = new GLProgram(this->m_ClassName + "-SetLumi", GL_FRAGMENT_SHADER);
	//fp_aura = new GLProgram(this->m_ClassName + "-SetLumi", GL_FRAGMENT_SHADER);
	


	/*
		Samplers.	
	*/


	var1 = fp_action1->uniforms()->getGPUsampler("fboIn");
	var2 = fp_action2->uniforms()->getGPUsampler("fboIn");
	var3 = fp_simple->uniforms()->getGPUsampler("fboIn");
	var4 = fp_simple->uniforms()->getGPUsampler("fboBase");
	var5 = fp_simple->uniforms()->getGPUsampler("fboIn");
	var1->Set(0);
	var2->Set(0);
	var3->Set(0);
	var4->Set(1);
	var5->Set(0);
	
	timer = fp_simple->uniforms()->getGPUint("timer");
	timer->Set(0);
	coeffLumi = fp_lumi->uniforms()->getGPUfloat("coeff");
	coeffLumi->Set(1);

	/*
		Bloom.
		Toutes les effect_* suivant sont utlis�s pour accentu� l'effet de luminosit� du bloom
	*/
	effect_1 = Scene::getInstance()->getResource<GPUFBO>("FBO int�rm�diaire 1");
	effect_1->createTexture2DAttachments(2048, 2048);
	effect_2 = Scene::getInstance()->getResource<GPUFBO>("FBO int�rm�diaire 2");
	effect_2->createTexture2DAttachments(2048, 2048);
	effect_1_1 = Scene::getInstance()->getResource<GPUFBO>("FBO int�rm�diaire 3");
	effect_1_1->createTexture2DAttachments(2048, 2048);
	effect_1_2 = Scene::getInstance()->getResource<GPUFBO>("FBO int�rm�diaire 4");
	effect_1_2->createTexture2DAttachments(512, 512);
	effect_1_3 = Scene::getInstance()->getResource<GPUFBO>("FBO int�rm�diaire 5");
	effect_1_3->createTexture2DAttachments(256, 256);
	
	

	
}
mainEffect::~mainEffect()
{

	
	
}

void mainEffect::apply(GPUFBO* in, GPUFBO* out)
{
	glDisable(GL_DEPTH_TEST);

	// On garde le m�me Vertex pour l'instant
	m_ProgramPipeline->useProgramStage(GL_VERTEX_SHADER_BIT, vp_Base);

	/*
		Mon timer pour les animations.
	*/

	
	if (timer->getValue() > FBO_WIDTH) {
		timer->Set(0);
		coeff += coeff/6;

	}else {
		timer->Set(timer->getValue() + coeff);
	}

	if (timer->getValue() > FBO_WIDTH - 100) {
		coeffLumi->Set(coeffLumi->getValue()+0.2);
	}
	
	oneEffect(in, in,fp_lumi,NULL);
	Bloom1(in, out);

	glEnable(GL_DEPTH_TEST);

}
void mainEffect::displayInterface()
{

}

void mainEffect::oneEffect(GPUFBO* in, GPUFBO* out,GLProgram* effect,GPUFBO* bind ) {
	m_ProgramPipeline->useProgramStage(GL_FRAGMENT_SHADER_BIT, effect);

	out->enable();
	if (bind != NULL) {
		bind->bindColorTexture(1);
	}
	in->bindColorTexture(0);
	m_ProgramPipeline->bind();
	drawQuad();
	m_ProgramPipeline->release();

	out->disable();

}


void mainEffect::Bloom1(GPUFBO* in, GPUFBO* out) {
	oneEffect(in, effect_1, fp_action1,NULL);
	oneEffect(effect_1, effect_2, fp_action2,NULL);
	oneEffect(effect_2, effect_1_1, fp_action2,NULL);
	oneEffect(effect_1_1, effect_1_2, fp_action2,NULL);
	oneEffect(effect_1_2, effect_1_3, fp_action2,NULL);
	oneEffect(effect_1_3, out, fp_simple,in);
}

