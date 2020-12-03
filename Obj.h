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
	//============= dynamic
	int kinds{ 0 };
	int imageNumber{ 0 };			//연속된 이미지일경우 이미지수
	int interval{ 0 };				//연속된 이미지일경우 이미지간의 간격
	HBITMAP hBitmap{ NULL };
	POINT cursorPos{ 0,0 };			//현재 마우스위치값저장할변수	???????????????????????
	int printImageNumber{ 0 };		//연속된 이미지중에 출력할 이미지 번호

public:
	Obj();
	Obj(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int kinds, int number, int interval, HBITMAP hBitmap);
	virtual ~Obj() = 0;

	virtual void Input() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hDC, HDC memDc) = 0;

	void SetPosition(ObjectData::POSITION pos);
	void SetSize(ObjectData::SIZE size);
	void SetHBitmap(HBITMAP hBitmap);
	HBITMAP GetHBitmap();
};