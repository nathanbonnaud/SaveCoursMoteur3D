
#include "Blur.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Engine.h"



Blur::Blur(std::string name):
	EffectGL(name,"Blur")
{
	
	vp = new GLProgram(this->m_ClassName+"-Base",GL_VERTEX_SHADER);

	

	m_ProgramPipeline->useProgramStage(GL_VERTEX_SHADER_BIT,vp);
	

}
Blur::~Blur()
{
	
	delete vp;
}


void Blur::apply(GPUFBO *in)
{
	


}
void Blur::displayInterface()
{

}

