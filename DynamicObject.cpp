#include "DynamicObject.h"

DynamicObject::DynamicObject()
{
}

DynamicObject::DynamicObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap)
								: Obj(name, pos, size, hBitmap)
{
	this->hNumber = hNumber;
	this->vNumber = vNumber;

	this->imageWidth = size.width / hNumber;
	this->imageHeight = size.height / vNumber;
}

DynamicObject::~DynamicObject()
{
	Obj::~Obj();
}