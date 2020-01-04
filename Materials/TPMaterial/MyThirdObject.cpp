#include "MyThirdObject.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Scene.h"
#include <time.h>



MyThirdObject::MyThirdObject(std::string name):
	MaterialGL(name,"TPMaterial")
{	
	vp = new GLProgram(this->m_ClassName + "-FMarchepas", GL_VERTEX_SHADER);
	fp = new GLProgram(this->m_ClassName + "-AMarchepas", GL_FRAGMENT_SHADER);
	m_ProgramPipeline->useProgramStage(GL_FRAGMENT_SHADER_BIT, fp);
	m_ProgramPipeline->useProgramStage(GL_VERTEX_SHADER_BIT, vp);

	
	/*1ere Texture*/
	GPUTexture2D* myTexture = new GPUTexture2D(ressourceTexPath + "BrickL.png");
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
	posCam->Set(Scene::getInstance()->camera()->convertPtFrom(glm::vec3(0, 0, 0), o->frame()));
	posLum->Set(Scene::getInstance()->frame()->convertPtTo(glm::vec3(0, 7, 10), o->frame()));
	
}
