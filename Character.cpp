#include "Character.h"

Character::Character(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap, CharacterStatsData characterStats)
					: DynamicObject(name, pos, size, hNumber, vNumber, hBitmap)
{
	if (name.find("Red") != string::npos)
		color = CharacterColor::RED;
	else if (name.find("Blue") != string::npos)
		color = CharacterColor::BLUE;

	this->characterStats = characterStats;
}

Character::~Character()
{

}

void Character::Input()
{
	if (CharacterColor::RED == color)	//red character move, attack
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
		if (GetAsyncKeyState(VK_RSHIFT))		//공격
		{
			attack.isAttack = true;
			attack.isColor = CharacterColor::BLUE;
			attack.pos.x = pos.x;
			attack.pos.y = pos.y + imageHeight / 2;
		}
	}
	if (CharacterColor::BLUE == color)	//blue character move, attack
	{
		if (GetAsyncKeyState('R'))
		{
			dir = Diraction::TOP;
			pos.y -= 5;
		}
		if (GetAsyncKeyState('F'))
		{
			dir = Diraction::BOTTOM;
			pos.y += 5;
		}
		if (GetAsyncKeyState('D'))
		{
			dir = Diraction::LEFT;
			pos.x -= 5;
		}
		if (GetAsyncKeyState('G'))
		{
			dir = Diraction::RIGHT;
			pos.x += 5;
		}
		if (GetAsyncKeyState(VK_LSHIFT))		//공격
		{
			attack.isAttack = true;
			attack.isColor = CharacterColor::RED;
			attack.pos.x = pos.x;
			attack.pos.y = pos.y + imageHeight / 2;
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

	//테스트용 현재 플레이어 위치좌표출력
	//static char c[255];
	//if (color == CharacterColor::RED)
	//{
	//	sprintf_s(c, "RED : %d, %d", pos.x, pos.y);
	//	TextOut(hDC, 10, 10, c, sizeof(c));
	//}
	//if (color == CharacterColor::BLUE)
	//{
	//	sprintf_s(c, "BLUE : %d, %d", pos.x, pos.y);
	//	TextOut(hDC, 10, 50, c, sizeof(c));
	//}
}

Attack& Character::GetAttack()
{
	return this->attack;
}