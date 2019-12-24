
#include "Engine/OpenGL/MaterialGL.h"
#include "Engine/OpenGL/Lighting/LightingModelGL.h"
#include <memory.h>

class Aura : public MaterialGL
{
	public:
		Aura(std::string name);
		~Aura();
		void setColor(glm::vec4 &c);

		virtual void render(Node *o);
		virtual void update(Node* o,const int elapsedTime);
		GPUmat4* modelViewProj;
		GPUvec3* color;
		GPUvec3* posLum;
		GPUvec3* posCam;
		GPUfloat* timer;
		GPUint* width;
		GPUint* height;
		
		GPUsampler* mySampler2;
		GPUsampler* mySampler;

		float coeff;

};
