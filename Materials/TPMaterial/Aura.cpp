#include "Aura.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Scene.h"
#include <time.h>

/*
	Cette classe est la classe du material de l'aura du personnage.
*/


Aura::Aura(std::string name):
	MaterialGL(name,"TPMaterial")
{
	vp = new GLProgram(this->m_ClassName + "-FZoom", GL_VERTEX_SHADER);
	fp = new GLProgram(this->m_ClassName + "-AZoom", GL_FRAGMENT_SHADER);
	m_ProgramPipeline->useProgramStage(GL_FRAGMENT_SHADER_BIT, fp);
	m_ProgramPipeline->useProgramStage(GL_VERTEX_SHADER_BIT, vp);
	
	modelViewProj = vp->uniforms()->getGPUmat4("MVP");
	
	// Timer //
	timer = vp->uniforms()->getGPUfloat("timer");
	timer->Set(0);
}
Aura::~Aura()
{

}

void Aura::setColor(glm::vec4 &c)
{
	
}


void Aura::render(Node *o)
{
	/* GL_BLEND et glBlendFunc(..) sont utilisés pour autorisé la transparence sur le canal alpha*/

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	modelViewProj->Set(o->frame()->getTransformMatrix());
	
	if (m_ProgramPipeline)
	{		
		m_ProgramPipeline->bind();
		o->drawGeometry(GL_TRIANGLES);
		m_ProgramPipeline->release();
	}

	glDisable(GL_BLEND);
}

void Aura::update(Node* o,const int elapsed_Time)
{
	if (timer->getValue() > 9) {
		timer->Set(0);
		if (coeff < 0.5) {
			coeff = coeff + 0.02;
		}
	}
	else {
		timer->Set(timer->getValue() + coeff);
	}

	
	}

