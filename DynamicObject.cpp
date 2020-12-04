#include "DynamicObject.h"

DynamicObject::DynamicObject()
{
}

DynamicObject::DynamicObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, int hInterval, int vInterval, HBITMAP hBitmap)
								: Obj(name, pos, size, hBitmap)
{
	this->hNumber = hNumber;
	this->vNumber = vNumber;
	this->hInterval = hInterval;
	this->vInterval = vInterval;
}

DynamicObject::~DynamicObject()
{
	Obj::~Obj();
}

void DynamicObject::Input()
{
}

void DynamicObject::Update()
{
}

void DynamicObject::Render(HDC hDC, HDC memDc)
{
}
