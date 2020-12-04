#pragma once
#include "Obj.h"

class DynamicObject : public Obj
{
protected:
	ImageData2 test;
	POINT cursorPos{ 0,0 };			//현재 마우스위치값저장할변수
	int printImageNumber{ 0 };		//연속된 이미지중에 출력할 이미지 번호

public:
	DynamicObject();
	DynamicObject(ImageData2 test);
	virtual ~DynamicObject();
	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);

};

