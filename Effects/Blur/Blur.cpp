
#include "Blur.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Engine.h"



Blur::Blur(std::string name):
	EffectGL(name,"Blur")
{
	/*
		initialise le fragments et vertex shader (liaison).
	*/
	vp = new GLProgram(this->m_ClassName+"-Base",GL_VERTEX_SHADER);
	fp = new GLProgram(this->m_ClassName+"-Pass", GL_FRAGMENT_SHADER);
	m_ProgramPipeline->useProgramStage(GL_VERTEX_SHADER_BIT,vp);
	m_ProgramPipeline->useProgramStage(GL_FRAGMENT_SHADER_BIT, fp);
	m_ProgramPipeline->link();
	blur = fp->uniforms()->getGPUsampler("my_sampler_blur");
	blur->Set(0);


}
Blur::~Blur()
{
	
	delete vp;
	delete fp;
	delete blur;
}

/*
	Applique le blur sur le FBO
*/
void Blur::apply(GPUFBO *in)
{
	glDisable(GL_DEPTH_TEST);
	in->getColorTexture(0)->bind(0);
	m_ProgramPipeline->bind();
	drawQuad();
	m_ProgramPipeline->release();
	glEnable(GL_DEPTH_TEST);
}
void Blur::displayInterface()
{

}

