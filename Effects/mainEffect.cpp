#include "mainEffect.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Engine.h"



mainEffect::mainEffect(std::string name) :
	EffectGL(name, "Effect")
{
	
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


	/*
		Samplers.	
	*/


	var1 = fp_action1->uniforms()->getGPUsampler("fboIn");
	var2 = fp_action2->uniforms()->getGPUsampler("fboIn");
	var3 = fp_simple->uniforms()->getGPUsampler("fboIn");
	var4 = fp_simple->uniforms()->getGPUsampler("fboBase");
	var1->Set(0);
	var2->Set(0);
	var3->Set(0);
	var4->Set(1);
	

	/*
		Bloom.
	*/
	effect_1 = Scene::getInstance()->getResource<GPUFBO>("FBO intérmédiaire 1");
	effect_1->createTexture2DAttachments(2048, 2048);
	effect_1_1 = Scene::getInstance()->getResource<GPUFBO>("FBO intérmédiaire 3");
	effect_1_1->createTexture2DAttachments(1024, 1024);
	effect_1_2 = Scene::getInstance()->getResource<GPUFBO>("FBO intérmédiaire 4");
	effect_1_2->createTexture2DAttachments(512, 512);
	effect_1_3 = Scene::getInstance()->getResource<GPUFBO>("FBO intérmédiaire 5");
	effect_1_3->createTexture2DAttachments(256, 256);
	
	effect_2 = Scene::getInstance()->getResource<GPUFBO>("FBO intérmédiaire 2");
	effect_2->createTexture2DAttachments(2048, 2048);


	
}
mainEffect::~mainEffect()
{

	
	
}

void mainEffect::apply(GPUFBO* in, GPUFBO* out)
{
	glDisable(GL_DEPTH_TEST);

	// On garde le même Vertex pour l'instant
	m_ProgramPipeline->useProgramStage(GL_VERTEX_SHADER_BIT, vp_Base);

	Bloom(in, out);
	
	glEnable(GL_DEPTH_TEST);

}
void mainEffect::displayInterface()
{

}


void mainEffect::Bloom(GPUFBO* in, GPUFBO* out) {

	m_ProgramPipeline->useProgramStage(GL_FRAGMENT_SHADER_BIT, fp_action1);

	effect_1->enable();

	in->bindColorTexture(0);
	m_ProgramPipeline->bind();
	drawQuad();
	m_ProgramPipeline->release();

	effect_1->disable();

	m_ProgramPipeline->useProgramStage(GL_FRAGMENT_SHADER_BIT, fp_action2);

	effect_2->enable();

	effect_1->bindColorTexture(0);
	m_ProgramPipeline->bind();
	drawQuad();
	m_ProgramPipeline->release();

	effect_2->disable();
	m_ProgramPipeline->useProgramStage(GL_FRAGMENT_SHADER_BIT, fp_action2);

	effect_1_1->enable();

	effect_2->bindColorTexture(0);
	m_ProgramPipeline->bind();
	drawQuad();
	m_ProgramPipeline->release();

	effect_1_1->disable();m_ProgramPipeline->useProgramStage(GL_FRAGMENT_SHADER_BIT, fp_action2);

	effect_1_2->enable();

	effect_1_1->bindColorTexture(0);
	m_ProgramPipeline->bind();
	drawQuad();
	m_ProgramPipeline->release();

	effect_1_2->disable();m_ProgramPipeline->useProgramStage(GL_FRAGMENT_SHADER_BIT, fp_action2);

	effect_1_3->enable();

	effect_1_2->bindColorTexture(0);
	m_ProgramPipeline->bind();
	drawQuad();
	m_ProgramPipeline->release();

	effect_1_3->disable();m_ProgramPipeline->useProgramStage(GL_FRAGMENT_SHADER_BIT, fp_action2);

	m_ProgramPipeline->useProgramStage(GL_FRAGMENT_SHADER_BIT, fp_simple);

	out->enable();

	effect_1_3->bindColorTexture(0);
	in->bindColorTexture(1);
	m_ProgramPipeline->bind();
	drawQuad();
	m_ProgramPipeline->release();

	out->disable();



}

