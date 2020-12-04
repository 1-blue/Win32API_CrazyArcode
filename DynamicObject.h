#pragma once
#include "Obj.h"

class DynamicObject : public Obj
{
protected:
	int hNumber;		//가로이미지수
	int vNumber;		//세로이미지수
	int hInterval;		//가로간격
	int vInterval;		//세로간격
	POINT cursorPos{ 0,0 };			//현재 마우스위치값저장할변수
	int printImageNumber{ 0 };		//연속된 이미지중에 출력할 이미지 번호

public:
	DynamicObject();
	DynamicObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, int hInterval, int vInterval, HBITMAP hBitmap);
	virtual ~DynamicObject();
	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);

};

