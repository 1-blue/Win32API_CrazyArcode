#pragma once
#include <list>
#include <vector>
#include "DataStruct.h"

using namespace std;

class Obj
{
protected:
	string name;
	ObjectData::POSITION pos{ 0 ,0 };
	ObjectData::SIZE size{ 0 ,0 };
	int kinds{ 0 };
	int imageNumber{ 0 };
	int interval{ 0 };
	HBITMAP hBitmap{ NULL };
	POINT cursorPos{ 0,0 };		//현재 마우스위치값저장할변수
	int printImageNumber{ 0 };		//연속된 이미지중에 출력할 이미지 번호

public:
	Obj();
	Obj(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int kinds, int number, int interval, HBITMAP hBitmap);
	virtual ~Obj() = 0;

	virtual void Input();
	virtual void Render(HDC hDC, HDC memDc);

	void SetPosition(ObjectData::POSITION pos);
	void SetSize(ObjectData::SIZE size);
	void SetHBitmap(HBITMAP hBitmap);
	HBITMAP GetHBitmap();
};