#include "Obj.h"

Obj::Obj()
{
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
	SelectObject(hDC, hBitmap);

	BitBlt(hDC, pos.x, pos.y, size.width, size.height, memDc, 0, 0, SRCCOPY);
}

void Obj::SetHBitmap(HBITMAP hBitmap)
{
	this->hBitmap = hBitmap;
}

HBITMAP Obj::GetHBitmap()
{
	return hBitmap;
}
