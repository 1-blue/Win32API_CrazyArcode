#include "Obj.h"

Obj::Obj()
{
}

Obj::Obj(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int kinds, int number, int interval, HBITMAP hBitmap)
{
	this->name = name;
	this->pos = pos;
	this->size = size;
	this->kinds = kinds;
	this->imageNumber = number;
	this->interval = interval;
	this->hBitmap = hBitmap;
}

Obj::~Obj()
{
}

void Obj::Input()
{



}

void Obj::Render(HDC hDC, HDC memDc)
{
	SelectObject(memDc, hBitmap);

	TransparentBlt(hDC,
		pos.x, pos.y,				//출력될 이미지 시작좌표
		size.width, size.height,	//출력될 이미지크기
		memDc,
		0, 0,						//이미지에서 출력할 시작위치
		size.width, size.height,	//이미지에서 출력할 이미지의 크기
		RGB(255, 0, 255));
}

void Obj::SetPosition(ObjectData::POSITION pos)
{
	this->pos = pos;
}

void Obj::SetSize(ObjectData::SIZE size)
{
	this->size = size;
}

void Obj::SetHBitmap(HBITMAP hBitmap)
{
	this->hBitmap = hBitmap;
}

HBITMAP Obj::GetHBitmap()
{
	return hBitmap;
}
