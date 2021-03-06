#ifndef _TPMATERIAL_H
#define _TPMATERIAL_H


#include "Engine/OpenGL/MaterialGL.h"
#include "Engine/OpenGL/Lighting/LightingModelGL.h"
#include <memory.h>

class TPMaterial : public MaterialGL
{
	public:
		TPMaterial(std::string name);
		~TPMaterial();
		void setColor(glm::vec4 &c);

		virtual void render(Node *o);
		virtual void update(Node* o,const int elapsedTime);
		GPUmat4* modelViewProj;
		GPUvec3* color;
		GPUvec3* posLum;
		GPUvec3* posCam;
		GPUfloat* coeff;
		GPUint* width;
		GPUint* height;
		GPUint* transition;
		
		GPUsampler* mySampler2;
		GPUsampler* mySampler;

		int timer = 0;
		float position = 15;
		float coeffLumi = 0.05;
};

#endif