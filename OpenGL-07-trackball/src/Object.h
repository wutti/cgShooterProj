#include "cgmath.h"
#pragma once
class Object
{
private:
	vec3 position;
	float scale;
	unsigned char* image;
public:
	Object(){

	}
	Object(float pScale, vec3 pPosition, unsigned char* pImage)
	{
		scale = pScale;
		position = pPosition;
		image = pImage;
	}

	~Object(){

	}

	virtual unsigned char* getImage(){
		return image;
	}
	virtual vec3 getPosition(){
		return position;
	}
	virtual float getScale(){
		return scale;
	}
	virtual void setPosition(vec3 pPos){
		position = pPos;
	}
};

