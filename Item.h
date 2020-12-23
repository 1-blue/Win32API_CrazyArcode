#pragma once
#include "DynamicObject.h"
#include <ctime>

class Item : public DynamicObject
{
private:
	int printNumber;

public:
	Item(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap, int ramdomNumber);
	~Item();

	virtual void Render(HDC hDC, HDC memDc);
};