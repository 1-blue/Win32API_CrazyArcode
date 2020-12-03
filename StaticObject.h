#pragma once
#include "Obj.h"

class StaticObject : public Obj
{
private:


public:
	StaticObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int kinds, int number, int interval, HBITMAP hBitmap);
	~StaticObject();
	virtual void Input() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hDC, HDC memDc) = 0;

};

