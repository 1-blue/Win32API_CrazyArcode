#pragma once
#include <list>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

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
	HBITMAP hBitmap{ NULL };

public:
	Obj();
	Obj(const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap);
	virtual ~Obj() = 0;

	void SetPosition(ObjectData::POSITION pos);
	void SetSize(ObjectData::SIZE size);

	void Render(HDC hDC, HDC memDc);
	void Rendert(HDC hDC, HDC memDc);//테스트용
	void SetHBitmap(HBITMAP hBitmap);
	HBITMAP GetHBitmap();
};