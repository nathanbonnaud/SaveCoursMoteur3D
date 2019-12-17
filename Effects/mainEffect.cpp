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
	vp_Zoom = new GLProgram(this->m_ClassName + "-Zoom", GL_VERTEX_SHADER);

	/*
		Fragments.
	*/

	//bloom
	fp_action1 = new GLProgram(this->m_ClassName + "-GetLumi", GL_FRAGMENT_SHADER);
	fp_action2 = new GLProgram(this->m_ClassName + "-Blur", GL_FRAGMENT_SHADER);
	fp_simple = new GLProgram(this->m_ClassName + "-FinBl", GL_FRAGMENT_SHADER);
	fp_lumi = new GLProgram(this->m_ClassName + "-SetLumi", GL_FRAGMENT_SHADER);
	


	/*
		Samplers.	
	*/


	var1 = fp_action1->uniforms()->getGPUsampler("fboIn");
	var2 = fp_action2->uniforms()->getGPUsampler("fboIn");
	var3 = fp_simple->uniforms()->getGPUsampler("fboIn");
	var4 = fp_simple->uniforms()->getGPUsampler("fboBase");

	coeffBlur1 = fp_action2->uniforms()->getGPUint("n");
	var1->Set(0);
	var2->Set(0);
	var3->Set(0);
	var4->Set(1);

	
	timer = fp_simple->uniforms()->getGPUint("timer");
	timer->Set(0);
	coeffLumi = fp_lumi->uniforms()->getGPUfloat("coeff");
	coeffLumi->Set(1);

	/*
		Bloom.
		Toutes les effect_* suivant sont utlisés pour accentué l'effet de luminosité du bloom
	*/
	effect_1 = Scene::getInstance()->getResource<GPUFBO>("FBO intérmédiaire 1");
	effect_1->createTexture2DAttachments(2048, 2048);
	effect_2 = Scene::getInstance()->getResource<GPUFBO>("FBO intérmédiaire 2");
	effect_2->createTexture2DAttachments(2048, 2048);
	effect_1_1 = Scene::getInstance()->getResource<GPUFBO>("FBO intérmédiaire 3");
	effect_1_1->createTexture2DAttachments(2048, 2048);
	effect_1_2 = Scene::getInstance()->getResource<GPUFBO>("FBO intérmédiaire 4");
	effect_1_2->createTexture2DAttachments(512, 512);
	effect_1_3 = Scene::getInstance()->getResource<GPUFBO>("FBO intérmédiaire 5");
	effect_1_3->createTexture2DAttachments(256, 256);
	
	

	
}
mainEffect::~mainEffect()
{

	
	
}

void mainEffect::apply(GPUFBO* in, GPUFBO* out)
{
	glDisable(GL_DEPTH_TEST);
	// On garde le même Vertex pour l'instant
	m_ProgramPipeline->useProgramStage(GL_VERTEX_SHADER_BIT, vp_Base);

	/*
		Mon timer pour les animations.
	*/
	/*
	if (coeff < 1500) {
		if (timer->getValue() > FBO_WIDTH) {
			timer->Set(0);
			coeff += coeff / 7;

		}
		else {
			timer->Set(timer->getValue() + coeff);
		}

		if (timer->getValue() > FBO_WIDTH - 100) {
			coeffLumi->Set(coeffLumi->getValue() + 0.1);
		}
	}
	*/
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
	coeffBlur1->Set(8);
	oneEffect(in, effect_1, fp_action1,NULL);
	oneEffect(effect_1, effect_2, fp_action2,NULL);
	oneEffect(effect_2, effect_1_1, fp_action2,NULL);
	oneEffect(effect_1_1, effect_1_2, fp_action2,NULL);
	oneEffect(effect_1_2, effect_1_3, fp_action2,NULL);
	oneEffect(effect_1_3, out, fp_simple,in);
}

void mainEffect::Aura(GPUFBO* in, GPUFBO* out) {
	glDisable(GL_DEPTH_TEST);
	m_ProgramPipeline->useProgramStage(GL_VERTEX_SHADER_BIT, vp_Base);

	coeffBlur1->Set(16);
	oneEffect(in, out, fp_action2, NULL);
	glEnable(GL_DEPTH_TEST);

}


