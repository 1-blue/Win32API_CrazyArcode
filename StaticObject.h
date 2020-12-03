#pragma once
#include "Obj.h"

class StaticObject : public Obj
{
private:


public:
	StaticObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap);

	StaticObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int kinds, int number, int interval, HBITMAP hBitmap);
	~StaticObject();
	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);

};

