#include "DynamicObject.h"

DynamicObject::DynamicObject()
{
}

DynamicObject::DynamicObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int kinds, int imageNumber, int interval, HBITMAP hBitmap) 
								: Obj(name, pos, size, hBitmap)
{
	this->kinds = kinds;
	this->imageNumber = imageNumber;
	this->interval = interval;
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
