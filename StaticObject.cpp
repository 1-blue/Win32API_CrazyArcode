#include "StaticObject.h"

StaticObject::StaticObject()
{
}

StaticObject::StaticObject(const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap) : Obj(pos, size, hBitmap)
{
}

StaticObject::~StaticObject()
{
	Obj::~Obj();
}
