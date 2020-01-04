

#ifndef _SAMPLE_ENGINE_H
#define _SAMPLE_ENGINE_H

#include <map>
#include <string>
#include "Engine/OpenGL/EngineGL.h"

#include "mainEffect.h"


class SampleEngine : public EngineGL
{
	public:
		SampleEngine(int width, int height);
		~SampleEngine();

		virtual bool init(std::string filename = "");
		virtual void render();
		virtual void animate(const int elapsedTime);
		Node* bunny;
		Node* bunny2;
		Node* bunny3;
		
		GPUFBO* fbo_in;
		GPUFBO* fbo_inter;
		GPUFBO* fbo_out;
		GPUFBO* fbo_out2;
		mainEffect* main_Effect;
		int timer = 0;
	protected:
	

};
#endif