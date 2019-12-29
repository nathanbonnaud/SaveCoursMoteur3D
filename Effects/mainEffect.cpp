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
	fp_circle = new GLProgram(this->m_ClassName + "-Circle", GL_FRAGMENT_SHADER);
	fp_trans = new GLProgram(this->m_ClassName + "-Transition", GL_FRAGMENT_SHADER);
	


	/*
		Samplers.	
	*/


	var1 = fp_action1->uniforms()->getGPUsampler("fboIn");
	var2 = fp_action2->uniforms()->getGPUsampler("fboIn");
	var3 = fp_simple->uniforms()->getGPUsampler("fboIn");
	var4 = fp_simple->uniforms()->getGPUsampler("fboBase");
	timecircle = fp_circle->uniforms()->getGPUfloat("time");
	transp = fp_circle->uniforms()->getGPUfloat("trans");
	transp1 = fp_trans->uniforms()->getGPUfloat("trans");
	timeTrans = fp_trans->uniforms()->getGPUfloat("timer");
	
	coeffBlur1 = fp_action2->uniforms()->getGPUint("n");
	var1->Set(0);
	var2->Set(0);
	var3->Set(0);
	var4->Set(1);
	timecircle->Set(0);
	transp->Set(0);
	transp1->Set(0);
	timeTrans->Set(0);


	
	timer = fp_simple->uniforms()->getGPUint("timer");
	timer->Set(0);
	

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
	oneEffect(in, out, fp_circle, NULL);
	glEnable(GL_DEPTH_TEST);


}
void mainEffect::displayInterface()
{

}

void mainEffect::oneEffect(GPUFBO* in, GPUFBO* out, GLProgram* effect, GPUFBO* bind) {
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
	oneEffect(in, effect_1, fp_action1, NULL);
	oneEffect(effect_1, effect_2, fp_action2, NULL);
	oneEffect(effect_2, effect_1_1, fp_action2, NULL);
	oneEffect(effect_1_1, effect_1_2, fp_action2, NULL);
	oneEffect(effect_1_2, effect_1_3, fp_action2, NULL);
	oneEffect(effect_1_3, out, fp_simple, in);
}

void mainEffect::Flou(GPUFBO* in, GPUFBO* out) {
	glDisable(GL_DEPTH_TEST);
	m_ProgramPipeline->useProgramStage(GL_VERTEX_SHADER_BIT, vp_Base);
	coeffBlur1->Set(8);
	oneEffect(in, out, fp_action2, NULL);
	glEnable(GL_DEPTH_TEST);

}

void mainEffect::GetLumi(GPUFBO* in, GPUFBO* out) {
	glDisable(GL_DEPTH_TEST);
	m_ProgramPipeline->useProgramStage(GL_VERTEX_SHADER_BIT, vp_Base);
	oneEffect(in, out, fp_action1, NULL);
	glEnable(GL_DEPTH_TEST);

}

void mainEffect::FinLumi(GPUFBO* in, GPUFBO* out, GPUFBO* tmp) {
	glDisable(GL_DEPTH_TEST);
	m_ProgramPipeline->useProgramStage(GL_VERTEX_SHADER_BIT, vp_Base);
	oneEffect(in, out, fp_simple, tmp);
	glEnable(GL_DEPTH_TEST);

}

void mainEffect::Circle1(GPUFBO* in, GPUFBO* out) {

	if (transp->getValue() < 0.45) {
		if ((int)timecircle->getValue() % 5 == 1) {
			transp->Set(transp->getValue() + 0.005);
		}
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	timecircle->Set(timecircle->getValue() + 0.005);
	m_ProgramPipeline->useProgramStage(GL_VERTEX_SHADER_BIT, vp_Base);
	oneEffect(in, out, fp_circle, NULL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

}

void mainEffect::Transition(GPUFBO* in, GPUFBO* out, bool sens) {
	if( sens == false){
		if (transp1->getValue() < 1.) {
			if ((int)timeTrans->getValue() % 5 == 1) {
				transp1->Set(transp1->getValue() + 0.02);
			}
		}
		if (timeTrans->getValue() < 225) {
			timeTrans->Set(timeTrans->getValue() + 0.75);
		}
	}
	
	glDisable(GL_DEPTH_TEST);
	
	m_ProgramPipeline->useProgramStage(GL_VERTEX_SHADER_BIT, vp_Base);
	oneEffect(in, out, fp_trans, NULL);
	glEnable(GL_DEPTH_TEST);

}


