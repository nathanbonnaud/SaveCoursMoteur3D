#include "TPMaterial.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Scene.h"
#include <time.h>

/*
	Cette classe est le material de mon objet de base.
*/
TPMaterial::TPMaterial(std::string name):
	MaterialGL(name,"TPMaterial")
{
	/* 
		Le Fragment et Vertex Shader de cette classe sont Main-VS et Main-FS.
		C'est dans le Main-FS que tous les effets de lumières sont réalisés.
	*/

	/*1ere Texture*/
	GPUTexture2D* myTexture = new GPUTexture2D(ressourceTexPath + "golemtex2.jpeg");
	mySampler = fp->uniforms()->getGPUsampler("my_sampler");
	mySampler->Set(myTexture->getHandle());

	/* 2eme Texture*/
	GPUTexture2D* myTexture2 = new GPUTexture2D(ressourceTexPath + "golemnormal.png");
	mySampler2 = fp->uniforms()->getGPUsampler("my_sampler2");
	mySampler2->Set(myTexture2->getHandle());


	
	modelViewProj = vp->uniforms()->getGPUmat4("MVP");
	posLum = fp->uniforms()->getGPUvec3("pos_lum");
	posCam=fp->uniforms()->getGPUvec3("pos_cam");
	
	coeff = fp->uniforms()->getGPUfloat("coeff");
	coeff->Set(1);
	transition = fp->uniforms()->getGPUint("transition");
	transition->Set(0);
	
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