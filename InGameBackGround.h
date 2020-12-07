#pragma once
#include "StaticObject.h"

class InGameBackGround : public StaticObject
{

public:
	InGameBackGround(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap);
	~InGameBackGround();

	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);
};

