﻿/*
EngineGL overloaded for custom rendering
*/
#include "SampleEngine.h"
#include "Engine/OpenGL/v4/GLProgram.h"
#include "Engine/OpenGL/SceneLoaderGL.h"
#include "Engine/Base/NodeCollectors/MeshNodeCollector.h"
#include "Engine/Base/NodeCollectors/FCCollector.h"

#include "Materials/TPMaterial/TPMaterial.h"
#include "Materials/TPMaterial/Aura.h"


#include "GPUResources/GPUInfo.h"


SampleEngine::SampleEngine(int width, int height) :
EngineGL (width, height)
{
	LOG_INFO << "# - " << __FUNCTION__ << std::endl;
	
}

SampleEngine::~SampleEngine()
{


}


bool SampleEngine::init(std::string filename)
{


	//Création d'un materiau de Base
	TPMaterial* material = new TPMaterial("TPMaterial");
	Aura* material2 = new Aura("Aura");
	fbo_in = Scene::getInstance()->getResource<GPUFBO>("FBO entré");
	fbo_in->createTexture2DAttachments(2048, 2048);
	fbo_inter = Scene::getInstance()->getResource<GPUFBO>("FBO entrée");
	fbo_inter->createTexture2DAttachments(2048, 2048);
	fbo_out = Scene::getInstance()->getResource<GPUFBO>("FBO sortie");
	fbo_out->createTexture2DAttachments(2048, 2048);
	fbo_out2 = Scene::getInstance()->getResource<GPUFBO>("FBO sortiee");
	fbo_out2->createTexture2DAttachments(2048, 2048);
	
	main_Effect = new mainEffect("Main");
	//Création d'un objet, méthode condensée
	//addObject("Bunny",ressourceObjPath + "Bunny.obj",material);

	//Création d'un objet, méthode détaillée
	bunny = scene->getNode("bunny");
	bunny->setModel(scene->m_Models.get<ModelGL>(ressourceCoreObjPath + "Golem.obj"));
	bunny2 = scene->getNode("bunny2");
	bunny2->setModel(scene->m_Models.get<ModelGL>(ressourceCoreObjPath + "Golem.obj"));

	/*
		Golem
	*/
	
	bunny->frame()->scale(glm::vec3(1.50));
	bunny->frame()->translate(glm::vec3(0, -2.8, 0));

	bunny2->frame()->scale(glm::vec3(1.65,1.55,1.68));
	bunny2->frame()->translate(glm::vec3(0,-2.85,0));


	bunny->setMaterial(material);
	bunny2->setMaterial(material2);
	scene->getSceneNode()->adopt(bunny);
	scene->getSceneNode()->adopt(bunny2);
	

	setUpEngine();
	LOG_INFO << "initialisation complete" << std::endl;
	return(true);
}


void SampleEngine::render ()
{
	fbo_in->enable();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderedNodes->nodes[1]->render();
	main_Effect->Flou(fbo_in, fbo_in);
	
	drawBBAndLight();

	fbo_in->disable();
	
	
	fbo_inter->enable();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	fbo_in->display();
	renderedNodes->nodes[0]->render();

	drawBBAndLight();

	fbo_inter->disable();
	
	if (timer > 650) {
		fbo_out->enable();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		fbo_inter->display();
		main_Effect->Circle1(fbo_inter, fbo_out);

		drawBBAndLight();

		fbo_out->disable();

		if (timer > 1300) {
			fbo_out2->enable();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			fbo_out->display();
			main_Effect->Transition(fbo_out, fbo_out2,false);

			drawBBAndLight();

			fbo_out2->disable();
			fbo_out2->display();

		}
		else {
			fbo_out->display();

		}
	}
	else {
		fbo_inter->display();
	}
	
	timer++;

}

void SampleEngine::animate (const int elapsedTime)
{
	// Animate each node
	for (unsigned int i = 0; i < allNodes->nodes.size (); i++)
		allNodes->nodes[i]->animate (elapsedTime);
	// force update of lighting model
	lightingModel->update (true);
	Scene::getInstance()->camera()->updateBuffer();
}

