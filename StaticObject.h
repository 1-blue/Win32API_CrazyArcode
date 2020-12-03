#pragma once
#include "Obj.h"

class StaticObject : public Obj
{

public:
	StaticObject();
	StaticObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap);
	~StaticObject();
	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);

};

