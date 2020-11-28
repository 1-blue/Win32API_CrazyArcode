#pragma once
#include "DataStruct.h"

namespace ObjectData
{
	typedef struct Position
	{
		int x;
		int y;

	}POSITION, * pPOSITION;

	typedef struct Size
	{
		int width;
		int height;

	}SIZE, * pSIZE;
}

class Obj
{
protected:
	ObjectData::POSITION pos{ 0 ,0 };
	ObjectData::SIZE size{ 0 ,0 };
	HBITMAP hBitmap;

public:
	Obj();
	virtual ~Obj() = 0;

	void SetPosition(ObjectData::POSITION pos);
	void SetSize(ObjectData::SIZE size);

	void Render(HDC hDC, HDC memDc);
	void SetHBitmap(HBITMAP hBitmap);
	HBITMAP GetHBitmap();
};