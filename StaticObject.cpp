#include "StaticObject.h"

StaticObject::StaticObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int kinds, int number, int interval, HBITMAP hBitmap) : Obj(name, pos, size, kinds, number, interval, hBitmap)
{
}

StaticObject::~StaticObject()
{
	Obj::~Obj();
}