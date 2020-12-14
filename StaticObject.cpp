#include "StaticObject.h"

StaticObject::StaticObject()
{
}

StaticObject::StaticObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap)
						: Obj(name, pos, size, hBitmap)
{
	this->name = name;
	this->pos = pos;
	this->size = size;
	this->hBitmap = hBitmap;
}

StaticObject::~StaticObject()
{
	Obj::~Obj();
}

void StaticObject::Input()
{
}

void StaticObject::Update()
{
}

void StaticObject::Render(HDC hDC, HDC memDc)
{
	SelectObject(memDc, hBitmap);

	TransparentBlt(hDC,
		pos.x, pos.y,					//출력될 이미지 시작좌표
		size.width, size.height,		//출력될 이미지크기
		memDc,
		0, 0,							//이미지에서 출력할 시작위치
		size.width, size.height,		//이미지에서 출력할 이미지의 크기
		RGB(255, 0, 255));
}