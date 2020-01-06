#include "TPMaterial.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Scene.h"
#include <time.h>

float position;

TPMaterial::TPMaterial(std::string name):
	MaterialGL(name,"TPMaterial")
{
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
	
	coeff = fp->uniforms()->getGPUfloat("coeff");
	coeff->Set(1);
	
	transition = fp->uniforms()->getGPUint("transition");
	transition->Set(0);
	
	// Timer //

	timer = 0;
	coeffLumi = 0.05;
	position = 15;
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
	posCam->Set(Scene::getInstance()->camera()->convertPtFrom(glm::vec3(0, 0, 0), o->frame()));
	posLum->Set(Scene::getInstance()->frame()->convertPtTo(glm::vec3(0,position, 10), o->frame()));
	if (timer < 1600) {
		if (timer > 100) {
			if (timer % 25 == 24) {
				coeffLumi = coeffLumi * 1.15;
			}
		}
		if (timer % 7 == 6) {
			coeff->Set(coeff->getValue() + coeffLumi);
		}
	}
	
	if (timer == 1600) {
		coeff->Set(4);
		transition->Set(1);
		position = 4;

	}
	timer++;
}