#include "DynamicObject.h"

DynamicObject::DynamicObject()
{
}

DynamicObject::DynamicObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int kinds, int number, int interval, HBITMAP hBitmap) : Obj(name, pos, size, kinds, number, interval, hBitmap)
{
}

DynamicObject::~DynamicObject()
{
	Obj::~Obj();
}
