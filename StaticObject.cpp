#include "StaticObject.h"

StaticObject::StaticObject()
{
}

StaticObject::StaticObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap)
						: Obj(name, pos, size, hBitmap)
{
	this->name = name;
	this->pos = pos;
	this->size = size;
	this->hBitmap = hBitmap;
}

StaticObject::~StaticObject()
{
	Obj::~Obj();
}