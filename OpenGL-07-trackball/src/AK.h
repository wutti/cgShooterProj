#pragma once
#include "cgmath.h"
#include "Object.h"
class AK : public Object
{
public:
	AK(){

	}
	AK(float pScale, vec3 pPosition, unsigned char* pImage) :Object(pScale,pPosition,pImage)
	{

	}

	~AK()
	{
		//free(image);
	}
};

