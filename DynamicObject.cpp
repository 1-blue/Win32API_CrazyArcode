#include "DynamicObject.h"

DynamicObject::DynamicObject()
{
}

DynamicObject::DynamicObject(const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap) : Obj(pos, size, hBitmap)
{
}

DynamicObject::~DynamicObject()
{
	Obj::~Obj();
}
