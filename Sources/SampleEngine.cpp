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
	myFilter = Scene::getInstance()->getResource<GPUFBO>("filter");
	myFilter->createTexture2DAttachments(1024, 1024);
	//Création d'un objet, méthode condensée
	//addObject("Bunny",ressourceObjPath + "Bunny.obj",material);

	//Création d'un objet, méthode détaillée
	Node* bunny = scene->getNode("bunny");
	bunny->setModel(scene->m_Models.get<ModelGL>(ressourceCoreObjPath + "Bunny.obj"));
	bunny->frame()->scale(glm::vec3(30.0));
	bunny->setMaterial(material);
	scene->getSceneNode()->adopt(bunny);


	setUpEngine();
	LOG_INFO << "initialisation complete" << std::endl;
	return(true);
}


void SampleEngine::render ()
{
	myFilter->enable();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (unsigned int i = 0; i < renderedNodes->nodes.size(); i++)
		renderedNodes->nodes[i]->render();
	
	drawBBAndLight();
	

	myFilter->disable();
	myFilter->display();
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

