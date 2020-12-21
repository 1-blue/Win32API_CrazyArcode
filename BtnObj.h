#pragma once
#include "DynamicObject.h"

class BtnObj : public DynamicObject
{
private:
	POINT cursorPos{ 0,0 };

	bool isOverlap{ false };
	bool isLClicked{ false };
	bool isRClicked{ false };

	ULONGLONG clickDelayTick{ 0 };
public:
	BtnObj();
	BtnObj(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap);
	~BtnObj();

	virtual void Input();
	virtual void Update();

	const bool CheckmDelay(const int delayTime);
};

