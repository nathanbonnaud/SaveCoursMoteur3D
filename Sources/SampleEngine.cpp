/*
EngineGL overloaded for custom rendering
*/
#include "SampleEngine.h"
#include "Engine/OpenGL/v4/GLProgram.h"
#include "Engine/OpenGL/SceneLoaderGL.h"
#include "Engine/Base/NodeCollectors/MeshNodeCollector.h"
#include "Engine/Base/NodeCollectors/FCCollector.h"

#include "Materials/TPMaterial/TPMaterial.h"

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
	fbo_in = Scene::getInstance()->getResource<GPUFBO>("FBO entré");
	fbo_in->createTexture2DAttachments(2048, 2048);
	fbo_out = Scene::getInstance()->getResource<GPUFBO>("FBO sortie");
	fbo_out->createTexture2DAttachments(2048, 2048);
	
	main_Effect = new mainEffect("Main");
	//Création d'un objet, méthode condensée
	//addObject("Bunny",ressourceObjPath + "Bunny.obj",material);

	//Création d'un objet, méthode détaillée
	Node* bunny = scene->getNode("bunny");
	bunny->setModel(scene->m_Models.get<ModelGL>(ressourceCoreObjPath + "Death2.obj"));
	/*
		Golem
	*/
	//bunny->frame()->scale(glm::vec3(1.65));
	//bunny->frame()->translate(glm::vec3(0, -3.0, 0));

	/*
		DeathStroke
	*/
	bunny->frame()->scale(glm::vec3(7));


	bunny->setMaterial(material);
	scene->getSceneNode()->adopt(bunny);

	setUpEngine();
	LOG_INFO << "initialisation complete" << std::endl;
	return(true);
}


void SampleEngine::render ()
{
	fbo_in->enable();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (unsigned int i = 0; i < renderedNodes->nodes.size(); i++)
		renderedNodes->nodes[i]->render();
	
	drawBBAndLight();
	

	fbo_in->disable();
	fbo_out->display();
	main_Effect->apply(fbo_in, fbo_out);

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

