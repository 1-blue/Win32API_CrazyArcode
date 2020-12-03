#pragma once
#include "Obj.h"

class DynamicObject : public Obj
{
protected:
	int kinds{ 0 };
	int imageNumber{ 0 };			//연속된 이미지일경우 이미지수
	int interval{ 0 };				//연속된 이미지일경우 이미지간의 간격
	POINT cursorPos{ 0,0 };			//현재 마우스위치값저장할변수
	int printImageNumber{ 0 };		//연속된 이미지중에 출력할 이미지 번호

public:
	DynamicObject();
	DynamicObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int kinds, int imageNumber, int interval, HBITMAP hBitmap);
	virtual ~DynamicObject();
	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);

};

