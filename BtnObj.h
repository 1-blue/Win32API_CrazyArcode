#pragma once
#include "DynamicObject.h"

namespace ClickedState
{
	enum
	{
		DEFAULT,
		LMOUSEDOWN,
		RMOUSEDOWN,
	};
}

class BtnObj : public DynamicObject
{
private:
	POINT cursorPos{ 0,0 };

	bool isOverlap{ false };
	bool playingSound{ false };
	int state{ ClickedState::DEFAULT };
public:
	BtnObj();
	BtnObj(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap);
	~BtnObj();

	virtual void Input();
	virtual void Update();
};