#include "Item.h"

Item::Item(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap, int ramdomNumber)
	: DynamicObject(name, pos, size, hNumber, vNumber, hBitmap)
{
	srand((unsigned int)time(NULL));
	printNumber = (rand() * ramdomNumber) % 3;

	this->name = printNumber + 19;		//임시로 +19
}

Item::~Item()
{

}

void Item::Render(HDC hDC, HDC memDc)
{
	SelectObject(memDc, hBitmap);
	TransparentBlt(hDC,
		pos.x, pos.y,				//출력될 이미지 시작좌표
		imageWidth, imageHeight,	//출력될 이미지크기
		memDc,
		printNumber * imageWidth, 0,		//이미지에서 출력할 시작위치
		imageWidth, imageHeight,	//이미지에서 출력할 이미지의 크기
		RGB(255, 0, 255));
}
