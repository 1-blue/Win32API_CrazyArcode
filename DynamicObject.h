#pragma once
#include "Obj.h"

class DynamicObject : public Obj
{
protected:
	int hNumber{ 0 };		//가로이미지수
	int vNumber{ 0 };		//세로이미지수

	int imageNumber{ 0 };	//연속된 이미지중에 출력할 이미지 번호

	int imageWidth{ 0 };	//이미지 하나의 가로 길이
	int imageHeight{ 0 };	//이미지 하나의 세로 길이

	int printhNumber{ 0 };	//출력될 이미지 가로 번호
	int printvNumber{ 0 };	//출력될 이미지 세로 번호
public:
	DynamicObject();
	DynamicObject(string name);		//이거 나중에 삭제
	DynamicObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap);
	virtual ~DynamicObject();
	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);

	void SetImageNumber(const int imageNumber);
};

