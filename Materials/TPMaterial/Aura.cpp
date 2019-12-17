#include "Aura.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Scene.h"
#include <time.h>



Aura::Aura(std::string name):
	MaterialGL(name,"TPMaterial")
{
	
	vp = new GLProgram(this->m_ClassName + "-FZoom", GL_VERTEX_SHADER);
	fp = new GLProgram(this->m_ClassName + "-AZoom", GL_FRAGMENT_SHADER);
	m_ProgramPipeline->useProgramStage(GL_FRAGMENT_SHADER_BIT, fp);
	m_ProgramPipeline->useProgramStage(GL_VERTEX_SHADER_BIT, vp);
	

	/*1ere Texture*/
	GPUTexture2D* myTexture = new GPUTexture2D(ressourceTexPath + "golemtex2.jpeg");
	mySampler = fp->uniforms()->getGPUsampler("my_sampler");
	mySampler->Set(myTexture->getHandle());

	/* 2eme Texture*/
	GPUTexture2D* myTexture2 = new GPUTexture2D(ressourceTexPath + "golemnormal.png");
	mySampler2 = fp->uniforms()->getGPUsampler("my_sampler2");
	mySampler2->Set(myTexture2->getHandle());


	
	color = vp->uniforms()->getGPUvec3("CPU_color");
	modelViewProj = vp->uniforms()->getGPUmat4("MVP");
	color->Set(glm::vec3(0.2, 0.8, 0.6));
	width = vp->uniforms()->getGPUint("w");
	height = vp->uniforms()->getGPUint("h");
	width->Set(1025);
	height->Set(1025);
	posLum = fp->uniforms()->getGPUvec3("pos_lum");
	posCam=fp->uniforms()->getGPUvec3("pos_cam");



	// Timer //

	//timer = vp->uniforms()->getGPUfloat("timer");
}
Aura::~Aura()
{

}

void Aura::setColor(glm::vec4 &c)
{
	
}

void Aura::render(Node *o)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	modelViewProj->Set(o->frame()->getTransformMatrix());
	
	if (m_ProgramPipeline)
	{		
		m_ProgramPipeline->bind();
		o->drawGeometry(GL_TRIANGLES);
		m_ProgramPipeline->release();
	}
	glDisable(GL_CULL_FACE);

	glDisable(GL_BLEND);
}

void Aura::update(Node* o,const int elapsed_Time)
{
	posCam->Set(Scene::getInstance()->camera()->convertPtFrom(glm::vec3(0, 0, 0), o->frame()));
	posLum->Set(Scene::getInstance()->frame()->convertPtTo(glm::vec3(0, 30, 0), o->frame()));

	/*
	t = (int)time(NULL);
	timer->Set(t);
	*/
}
