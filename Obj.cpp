#include "Obj.h"

Obj::Obj()
{
}

Obj::Obj(const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap)
{
	this->pos = pos;
	this->size = size;
	this->hBitmap = hBitmap;
}

Obj::~Obj()
{
}

void Obj::SetPosition(ObjectData::POSITION pos)
{
	this->pos = pos;
}

void Obj::SetSize(ObjectData::SIZE size)
{
	this->size = size;
}
void Obj::Render(HDC hDC, HDC memDc)
{
	SelectObject(memDc, hBitmap);

	TransparentBlt(hDC, pos.x, pos.y, size.width, size.height, memDc, 0, 0, size.width, size.height, RGB(255, 0, 255));
}

void Obj::Rendert(HDC hDC, HDC memDc)
{
	SelectObject(memDc, hBitmap);

	//TransparentBlt(hDC, pos.x, pos.y, size.width, size.height, memDc, 0, 0, size.width, size.height, RGB(255, 0, 255));
	//TransparentBlt(hDC, pos.x, pos.y, size.width, size.height / imageNumber, memDc, 0, imageAnimNum *56, size.width, size.height / imageNumber, RGB(255, 0, 255));

	TransparentBlt(hDC, pos.x, pos.y, size.width, size.height/2, memDc, 0, 56, size.width, size.height/2, RGB(255, 0, 255));
}

void Obj::SetHBitmap(HBITMAP hBitmap)
{
	this->hBitmap = hBitmap;
}

HBITMAP Obj::GetHBitmap()
{
	return hBitmap;
}
