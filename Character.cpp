#include "Character.h"

Character::Character(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap, CharacterStatsData characterStats)
					: DynamicObject(name, pos, size, hNumber, vNumber, hBitmap)
{
	if (name.find("Red"))
		color = CharacterColor::RED;
	else if (name.find("Blue"))
		color = CharacterColor::BLUE;

	this->characterStats = characterStats;
}

Character::~Character()
{

}

void Character::Input()
{
	if (CharacterColor::RED == color)	//red character move
	{
		if (GetAsyncKeyState(VK_UP))
		{
			dir = Diraction::TOP;
			pos.y -= 5;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			dir = Diraction::BOTTOM;
			pos.y += 5;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			dir = Diraction::LEFT;
			pos.x -= 5;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			dir = Diraction::RIGHT;
			pos.x += 5;
		}
	}
	if (CharacterColor::BLUE == color)	//blue character move
	{
		if (GetAsyncKeyState('W'))
		{
			dir = Diraction::TOP;
			pos.y -= 5;
		}
		if (GetAsyncKeyState('S'))
		{
			dir = Diraction::BOTTOM;
			pos.y += 5;
		}
		if (GetAsyncKeyState('A'))
		{
			dir = Diraction::LEFT;
			pos.x -= 5;
		}
		if (GetAsyncKeyState('D'))
		{
			dir = Diraction::RIGHT;
			pos.x += 5;
		}
	}
}

void Character::Update()
{
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
	SelectObject(memDc, hBitmap);

	TransparentBlt(hDC,
		pos.x, pos.y,				//출력될 이미지 시작좌표
		imageWidth, imageHeight,	//출력될 이미지크기
		memDc,
		printPos.x, printPos.y,		//이미지에서 출력할 시작위치
		imageWidth, imageHeight,	//이미지에서 출력할 이미지의 크기
		RGB(255, 0, 255));
}