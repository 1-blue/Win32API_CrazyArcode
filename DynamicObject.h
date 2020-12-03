#pragma once
#include "Obj.h"

class DynamicObject : public Obj
{
private:

public:
	DynamicObject();
	DynamicObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int kinds, int number, int interval, HBITMAP hBitmap);
	virtual ~DynamicObject();
	virtual void Input() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hDC, HDC memDc) = 0;

};

