#include "TPMaterial.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Scene.h"
#include <time.h>



TPMaterial::TPMaterial(std::string name):
	MaterialGL(name,"TPMaterial")
{
	/*1ere Texture*/
	GPUTexture2D* myTexture = new GPUTexture2D(ressourceTexPath + "bricks2_color.jpg");
	mySampler = fp->uniforms()->getGPUsampler("my_sampler");
	mySampler->Set(myTexture->getHandle());

	/* 2eme Texture*/
	GPUTexture2D* myTexture2 = new GPUTexture2D(ressourceTexPath + "Bunny2.png");
	mySampler2 = fp->uniforms()->getGPUsampler("my_sampler2");
	mySampler2->Set(myTexture2->getHandle());

	/* 3eme Texture*/
	GPUTexture2D* myTexture3 = new GPUTexture2D(ressourceTexPath + "Bunny_nm.jpg");
	mySampler3 = fp->uniforms()->getGPUsampler("my_sampler3");
	mySampler3->Set(myTexture3->getHandle());

	/* 4eme Texture*/
	GPUTexture2D* myTexture4 = new GPUTexture2D(ressourceTexPath + "brick2_parallax.png");
	mySampler4 = fp->uniforms()->getGPUsampler("my_sampler4");
	mySampler4->Set(myTexture4->getHandle());

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
TPMaterial::~TPMaterial()
{

}

void TPMaterial::setColor(glm::vec4 &c)
{
	
}

void TPMaterial::render(Node *o)
{

	modelViewProj->Set(o->frame()->getTransformMatrix());
	
	if (m_ProgramPipeline)
	{		
		m_ProgramPipeline->bind();
		o->drawGeometry(GL_TRIANGLES);
		m_ProgramPipeline->release();
	}
}

void TPMaterial::update(Node* o,const int elapsed_Time)
{
	posCam->Set(Scene::getInstance()->camera()->getFrame()->convertPtFrom(glm::vec3(0, 0, 0), o->frame()));
	posLum->Set(Scene::getInstance()->getSceneNode()->frame()->convertPtTo(glm::vec3(0, 30, 0), o->frame()));

	/*
	t = (int)time(NULL);
	timer->Set(t);
	*/
}
