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
	fp_action1 = new GLProgram(this->m_ClassName + "-Blur", GL_FRAGMENT_SHADER);
	fp_action2 = new GLProgram(this->m_ClassName + "-Bloom", GL_FRAGMENT_SHADER);


	/*
		Samplers.	
	*/
	var1 = fp_action1->uniforms()->getGPUsampler("my_sampler_blur");
	var1->Set(0);
	var2 = fp_action2->uniforms()->getGPUsampler("fboIn");
	var2->Set(0);
	var3 = fp_action2->uniforms()->getGPUsampler("fboIn1");
	var3->Set(0);
	var4 = fp_action2->uniforms()->getGPUsampler("fboIn2");
	var4->Set(0);
	var5 = fp_action2->uniforms()->getGPUsampler("fboIn");
	var5->Set(0);


	effect_1 = Scene::getInstance()->getResource<GPUFBO>("FBO intérmédiaire1");;
	effect_1->createTexture2DAttachments(1024, 1024);

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

	out->enable();

	effect_1->bindColorTexture(0);
	m_ProgramPipeline->bind();
	drawQuad();
	m_ProgramPipeline->release();

	out->disable();
}

