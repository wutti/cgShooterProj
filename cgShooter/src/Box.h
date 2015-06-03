#include "Object.h"
#include "cgmath.h"
#pragma once
class Box : public Object
{

public:
	Box(){

	}
	Box(float pScale, vec3 pPosition, unsigned char* pImage) :Object(pScale, pPosition, pImage)
	{

	}

	~Box()
	{
	}
};

