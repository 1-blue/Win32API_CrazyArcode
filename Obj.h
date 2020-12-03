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
	HBITMAP hBitmap{ NULL };

public:
	Obj();
	Obj(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap);
	virtual ~Obj() = 0;

	virtual void Input() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hDC, HDC memDc) = 0;

	void SetPosition(ObjectData::POSITION pos);
	void SetSize(ObjectData::SIZE size);
	void SetHBitmap(HBITMAP hBitmap);
	HBITMAP GetHBitmap();
};