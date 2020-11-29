#pragma once
#include "Obj.h"

class DynamicObject : public Obj
{
private:


public:
	DynamicObject();
	DynamicObject(const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap);
	virtual ~DynamicObject();

};

