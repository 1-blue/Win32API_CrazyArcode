#pragma once
#include "DynamicObject.h"

class BtnObj : public DynamicObject
{
private:
	POINT cursorPos{ 0,0 };

	bool isOverlap{ false };
	bool isClicked{ false };

public:
	BtnObj();
	BtnObj(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap);
	~BtnObj();

	virtual void Input();
	virtual void Update();


};

