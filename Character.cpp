#include "Character.h"


Character::Character(CHARTERDATA data)
{
	this->data = data;
}

Character::Character(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, int hInterval, int vInterval, HBITMAP hBitmap)
					: DynamicObject(name, pos, size, hNumber, vNumber, hInterval, vInterval, hBitmap)
{
}

Character::~Character()
{

}

void Character::Input()
{
	//red character move
	if (GetAsyncKeyState(VK_UP) && (name == "RedBazzi" || name == "RedDizni"))
	{
		dir = Diraction::TOP;
		pos.y -= 5;
	}
	if (GetAsyncKeyState(VK_DOWN) && (name == "RedBazzi" || name == "RedDizni"))
	{
		dir = Diraction::BOTTOM;
		pos.y += 5;
	}
	if (GetAsyncKeyState(VK_LEFT) && (name == "RedBazzi" || name == "RedDizni"))
	{
		dir = Diraction::LEFT;
		pos.x -= 5;
	}
	if (GetAsyncKeyState(VK_RIGHT) && (name == "RedBazzi" || name == "RedDizni"))
	{
		dir = Diraction::RIGHT;
		pos.x += 5;
	}

	//blue character move
	if (GetAsyncKeyState('W') && (name == "BlueBazzi" || name == "BlueDizni"))
	{
		dir = Diraction::TOP;
		pos.y -= 5;
	}
	if (GetAsyncKeyState('S') && (name == "BlueBazzi" || name == "BlueDizni"))
	{
		dir = Diraction::BOTTOM;
		pos.y += 5;
	}
	if (GetAsyncKeyState('A') && (name == "BlueBazzi" || name == "BlueDizni"))
	{
		dir = Diraction::LEFT;
		pos.x -= 5;
	}
	if (GetAsyncKeyState('D') && (name == "BlueBazzi" || name == "BlueDizni"))
	{
		dir = Diraction::RIGHT;
		pos.x += 5;
	}
}

void Character::Update()
{
	int imageWidth = size.width / hNumber;
	int imageHeight = size.height / vNumber;

	switch (dir)
	{
	case Diraction::LEFT:
		printPos.x += imageWidth;
		printPos.y = 0;
		if (printPos.x >= size.width)
			printPos.x = 0;
		break;
	case Diraction::TOP:
		printPos.x += imageWidth;
		printPos.y = imageHeight;
		if (printPos.x >= size.width)
			printPos.x = 0;
		break;

	case Diraction::RIGHT:
		printPos.x += imageWidth;
		printPos.y = imageHeight * 2;
		if (printPos.x >= size.width)
			printPos.x = 0;
		break;

	case Diraction::BOTTOM:
		printPos.x += imageWidth;
		printPos.y = imageHeight * 3;
		if (printPos.x >= size.width)
			printPos.x = 0;
		break;
	}
	dir = -1;
}

void Character::Render(HDC hDC, HDC memDc)
{
	int imageWidth = size.width / hNumber;
	int imageHeight = size.height / vNumber;

	SelectObject(memDc, hBitmap);

	TransparentBlt(hDC,
		pos.x, pos.y,				//출력될 이미지 시작좌표
		imageWidth, imageHeight,	//출력될 이미지크기
		memDc,
		printPos.x, printPos.y,		//이미지에서 출력할 시작위치
		imageWidth, imageHeight,	//이미지에서 출력할 이미지의 크기
		RGB(255, 0, 255));
}
