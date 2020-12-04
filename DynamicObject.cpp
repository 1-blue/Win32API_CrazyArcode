#include "DynamicObject.h"

DynamicObject::DynamicObject()
{
}

DynamicObject::DynamicObject(ImageData2 test) : Obj(test.name, { test.x, test.y }, {test.vInterval, test.hInterval}, test.hBitmap)
{
	this->test = test;
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
