#include "DynamicObject.h"

DynamicObject::DynamicObject()
{
}

DynamicObject::DynamicObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap)
								: Obj(name, pos, size, hBitmap)
{
	this->hNumber = hNumber;
	this->vNumber = vNumber;

	imageWidth = size.width / hNumber;
	imageHeight = size.height / vNumber;
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
	printhNumber = imageNumber % vNumber;
	printvNumber = imageNumber / vNumber;

	SelectObject(memDc, hBitmap);

	TransparentBlt(hDC,
		pos.x, pos.y,						//출력될 이미지 시작좌표
		imageWidth, imageHeight,			//출력될 이미지크기
		memDc,
		printhNumber * imageWidth, printvNumber * imageHeight,	//이미지에서 출력할 시작위치
		imageWidth, imageHeight,			//이미지에서 출력할 이미지의 크기
		RGB(255, 0, 255));
}
