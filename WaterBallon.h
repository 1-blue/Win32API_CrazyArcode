#pragma once
#include "DynamicObject.h"

class WaterBallon : public DynamicObject
{
private:


public:
	WaterBallon(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap);
	~WaterBallon();

	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);

};

