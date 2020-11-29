#pragma once
#include "Obj.h"

class StaticObject : public Obj
{
private:
	

public:
	StaticObject();
	StaticObject(const ObjectData::POSITION pos,const ObjectData::SIZE size, HBITMAP hBitmap);
	~StaticObject();

};

