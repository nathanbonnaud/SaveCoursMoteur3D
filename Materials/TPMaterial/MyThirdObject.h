#ifndef _MYTHIRDOBJECT_H
#define _MYTHIRDOBJECT_H

#include "Engine/OpenGL/MaterialGL.h"
#include "Engine/OpenGL/Lighting/LightingModelGL.h"
#include <memory.h>

class MyThirdObject : public MaterialGL
{
	public:
		MyThirdObject(std::string name);
		~MyThirdObject();
		void setColor(glm::vec4 &c);

		virtual void render(Node *o);
		virtual void update(Node* o,const int elapsedTime);
		GPUmat4* modelViewProj;
		GPUvec3* color;
		GPUvec3* posLum;
		GPUvec3* posCam;
		GPUint* width;
		GPUint* height;
		GPUfloat* timer;
		
		GPUsampler* mySampler2;
		GPUsampler* mySampler;

};

#endif