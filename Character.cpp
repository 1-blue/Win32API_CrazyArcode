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
	Manual();	//조작 입력
}

void Character::Update()
{
	switch (dir)
	{
	case Diraction::LEFT:
		pos.x -= characterStats.speed + 4;

		if (!CheckmDelay(100) && (prevDir == dir))
			break;

		printPos.x += imageWidth;
		printPos.y = 0;
		if (printPos.x >= size.width)
			printPos.x = 0;

		prevDir = Diraction::LEFT;
		break;
	case Diraction::TOP:
		pos.y -= characterStats.speed + 4;

		if (!CheckmDelay(100) && (prevDir == dir))
			break;

		printPos.x += imageWidth;
		printPos.y = imageHeight;
		if (printPos.x >= size.width)
			printPos.x = 0;

		prevDir = Diraction::TOP;
		break;
	case Diraction::RIGHT:
		pos.x += characterStats.speed + 4;

		if (!CheckmDelay(100) && (prevDir == dir))
			break;

		printPos.x += imageWidth;
		printPos.y = imageHeight * 2;
		if (printPos.x >= size.width)
			printPos.x = 0;

		prevDir = Diraction::RIGHT;
		break;
	case Diraction::BOTTOM:
		pos.y += characterStats.speed + 4;

		if (!CheckmDelay(100) && (prevDir == dir))
			break;

		printPos.x += imageWidth;
		printPos.y = imageHeight * 3;
		if (printPos.x >= size.width)
			printPos.x = 0;

		prevDir = Diraction::BOTTOM;
		break;
	}
	dir = -1;

	ImmovableArea();
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
	static char c[255];
	if (color == CharacterColor::RED)
	{
		sprintf_s(c, "RED : %d, %d", pos.x, pos.y);
		TextOut(hDC, 10, 10, c, sizeof(c));
	}
	if (color == CharacterColor::BLUE)
	{
		sprintf_s(c, "BLUE : %d, %d", pos.x, pos.y);
		TextOut(hDC, 10, 50, c, sizeof(c));
	}
}

Attack& Character::GetAttack()
{
	return this->attack;
}

void Character::Manual()
{
	if (CharacterColor::RED == color)	//red character move, attack
	{
		if (GetAsyncKeyState(VK_UP))
		{
			dir = Diraction::TOP;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			dir = Diraction::BOTTOM;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			dir = Diraction::LEFT;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			dir = Diraction::RIGHT;
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
		if (GetAsyncKeyState('W'))
		{
			dir = Diraction::TOP;
		}
		if (GetAsyncKeyState('S'))
		{
			dir = Diraction::BOTTOM;
		}
		if (GetAsyncKeyState('A'))
		{
			dir = Diraction::LEFT;
		}
		if (GetAsyncKeyState('D'))
		{
			dir = Diraction::RIGHT;
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

bool Character::CheckmDelay(const int delayTime)
{
	if (GetTickCount64() > charAnimationTick + delayTime)
	{
		charAnimationTick = GetTickCount64();
		return true;
	}
	return false;
}
	
void Character::ImmovableArea()
{
	if (pos.x <= MOVE_MIN_X)
		pos.x = MOVE_MIN_X;
	else if (pos.x >= MOVE_MAX_X)
		pos.x = MOVE_MAX_X;

	if (pos.y <= MOVE_MIN_Y)
		pos.y = MOVE_MIN_Y;
	else if (pos.y >= MOVE_MAX_Y)
		pos.y = MOVE_MAX_Y;

}
