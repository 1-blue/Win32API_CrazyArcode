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
