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

	/*
		Bloom.
	*/
	fp_action1 = new GLProgram(this->m_ClassName + "-GetLumi", GL_FRAGMENT_SHADER);
	fp_action2 = new GLProgram(this->m_ClassName + "-Blur", GL_FRAGMENT_SHADER);


	/*
		Samplers.	
	*/
	var1 = fp_action1->uniforms()->getGPUsampler("fboIn");
	var2 = fp_action2->uniforms()->getGPUsampler("fboIn");
	//var3 = fp_simple->uniforms()->getGPUsampler("fboIn");
	var1->Set(0);
	var2->Set(0);
	//var3->Set(0);
	

	effect_1 = Scene::getInstance()->getResource<GPUFBO>("FBO intérmédiaire1");;
	effect_1->createTexture2DAttachments(2048, 2048);


	
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
	m_ProgramPipeline->useProgramStage(GL_FRAGMENT_SHADER_BIT, fp_action2);

	effect_1->enable();

	in->bindColorTexture(0);
	m_ProgramPipeline->bind();
	drawQuad();
	m_ProgramPipeline->release();

	effect_1->disable();

	m_ProgramPipeline->useProgramStage(GL_FRAGMENT_SHADER_BIT, fp_action1);

	out->enable();

	effect_1->bindColorTexture(0);
	m_ProgramPipeline->bind();
	drawQuad();
	m_ProgramPipeline->release();

	out->disable();


}

