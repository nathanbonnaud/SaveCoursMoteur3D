#include "MyThirdObject.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Scene.h"
#include <time.h>

/*
	Cette fonction créer le material pour le sol.
*/

MyThirdObject::MyThirdObject(std::string name):
	MaterialGL(name,"TPMaterial")
{	
	vp = new GLProgram(this->m_ClassName + "-FThird", GL_VERTEX_SHADER);
	fp = new GLProgram(this->m_ClassName + "-AThird", GL_FRAGMENT_SHADER);
	m_ProgramPipeline->useProgramStage(GL_FRAGMENT_SHADER_BIT, fp);
	m_ProgramPipeline->useProgramStage(GL_VERTEX_SHADER_BIT, vp);


	
	
	color = vp->uniforms()->getGPUvec3("CPU_color");
	modelViewProj = vp->uniforms()->getGPUmat4("MVP");
	color->Set(glm::vec3(0.2, 0.8, 0.6));

	timer = fp->uniforms()->getGPUfloat("timer");
	timer->Set(0);
	coeff = fp->uniforms()->getGPUfloat("coeff");
	coeff->Set(0.2);

	
	
}
MyThirdObject::~MyThirdObject()
{

}

void MyThirdObject::setColor(glm::vec4 &c)
{
	
}

void MyThirdObject::render(Node *o)
{

	modelViewProj->Set(o->frame()->getTransformMatrix());
	
	if (m_ProgramPipeline)
	{		
		m_ProgramPipeline->bind();
		o->drawGeometry(GL_TRIANGLES);
		m_ProgramPipeline->release();
	}
}

void MyThirdObject::update(Node* o,const int elapsed_Time)
{
	timer->Set(timer->getValue()+0.01);
	if (coeff->getValue() < 2.8) {
		coeff->Set(coeff->getValue() + 0.001);

	}
}
