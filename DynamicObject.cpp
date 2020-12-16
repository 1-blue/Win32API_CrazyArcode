#include "DynamicObject.h"

DynamicObject::DynamicObject()
{
}

DynamicObject::DynamicObject(string name)
{
	this->name = name;
}

DynamicObject::DynamicObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap)
								: Obj(name, pos, size, hBitmap)
{
	this->hNumber = hNumber;
	this->vNumber = vNumber;

	this->imageWidth = size.width / hNumber;
	this->imageHeight = size.height / vNumber;
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
	
	if (hNumber <= vNumber)	
	{
		printhNumber = imageNumber % hNumber;
		printvNumber = imageNumber / hNumber;
	}
	else
	{
		printvNumber = imageNumber % vNumber;
		printhNumber = imageNumber / vNumber;
	}
	
	TransparentBlt(hDC,
		pos.x, pos.y,						//출력될 이미지 시작좌표
		imageWidth, imageHeight,			//출력될 이미지크기
		memDc,
		printhNumber * imageWidth, printvNumber * imageHeight,	//이미지에서 출력할 시작위치
		imageWidth, imageHeight,			//이미지에서 출력할 이미지의 크기
		RGB(255, 0, 255));
}

void DynamicObject::SetImageNumber(const int imageNumber)
{
	if ((imageNumber > (hNumber * vNumber)) || imageNumber < 0)
		return;

	this->imageNumber = imageNumber;
}

const int DynamicObject::GetImageNumber()
{
	return this->imageNumber;
}
