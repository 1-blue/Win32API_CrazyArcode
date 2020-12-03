#include "DynamicObject.h"

DynamicObject::DynamicObject()
{
}

DynamicObject::DynamicObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int kinds, int number, int interval, HBITMAP hBitmap) : Obj(name, pos, size, kinds, number, interval, hBitmap)
{
}

DynamicObject::~DynamicObject()
{
	Obj::~Obj();
}

void DynamicObject::Input()
{
}

void DynamicObject::Update()
{
}

void DynamicObject::Render(HDC hDC, HDC memDc)
{
	SelectObject(memDc, hBitmap);

	//이미지를 자를방향을 구분해서 출력
	switch (kinds)
	{
	case ObjectData::HORIZONTAL:
		TransparentBlt(hDC,
			pos.x, pos.y,									//출력될 이미지 시작좌표
			size.width / imageNumber, size.height,			//출력될 이미지크기
			memDc,
			size.width / imageNumber * printImageNumber, 0,	//이미지에서 출력할 시작위치
			size.width / imageNumber, size.height,			//이미지에서 출력할 이미지의 크기
			RGB(255, 0, 255));
		break;

	case ObjectData::VERTICAL:
		TransparentBlt(hDC,
			pos.x, pos.y,										//출력될 이미지 시작좌표
			size.width, size.height / imageNumber,				//출력될 이미지크기
			memDc,
			0, size.height / imageNumber * printImageNumber,	//이미지에서 출력할 시작위치
			size.width, size.height / imageNumber,				//이미지에서 출력할 이미지의 크기
			RGB(255, 0, 255));
		break;

	default:
		TransparentBlt(hDC,
			pos.x, pos.y,				//출력될 이미지 시작좌표
			size.width, size.height,	//출력될 이미지크기
			memDc,
			0, 0,						//이미지에서 출력할 시작위치
			size.width, size.height,	//이미지에서 출력할 이미지의 크기
			RGB(255, 0, 255));
		break;
	}
}
