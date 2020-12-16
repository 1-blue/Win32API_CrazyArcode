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

void Character::SettingAttackPos()
{
	int interval = 0;
	if (attack.pos.x % BLOCK_X != 0)
	{
		interval = attack.pos.x % BLOCK_X;
		if (interval >= BLOCK_X / 2)
			attack.pos.x = attack.pos.x + (BLOCK_X - interval);
		else
			attack.pos.x = attack.pos.x - interval;
	}
	if (attack.pos.y % BLOCK_Y != 0)
	{
		interval = attack.pos.y % BLOCK_Y;
		if (interval >= BLOCK_Y / 2)
			attack.pos.y = attack.pos.y + (BLOCK_Y - interval);
		else
			attack.pos.y = attack.pos.y - interval;
	}
	attack.pos.x -= 20;		//이거는 맵이 (0, 0)부터 시작이 아니라서 맵시작위치만큼 연산해주는거
}

void Character::Manual()
{
	if (CharacterColor::RED == color)	//red character move, attack
	{
		prevRedPos = pos;
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
		if (GetAsyncKeyState(VK_RSHIFT) & 0x0001)		//공격
		{
			attack.isAttack = true;
			attack.isColor = CharacterColor::BLUE;
			attack.pos.x = pos.x;
			attack.pos.y = pos.y + imageHeight / 2;
			SettingAttackPos();		//물풍선 놓는위치 지정
		}
	}

	if (CharacterColor::BLUE == color)	//blue character move, attack
	{
		prevBluePos = pos;
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

		if (GetAsyncKeyState(VK_LSHIFT) & 0x0001)		//공격
		{
			attack.isAttack = true;
			attack.isColor = CharacterColor::RED;
			attack.pos.x = pos.x;
			attack.pos.y = pos.y + imageHeight / 2;
			SettingAttackPos();		//물풍선 놓는위치 지정
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
	
void Character::ImmovableArea(const list<Obj*>& inGameObjectVector)
{
	//맵전체 이동범위제한
	if (pos.x <= MOVE_MIN_X)
		pos.x = MOVE_MIN_X;
	else if (pos.x >= MOVE_MAX_X)
		pos.x = MOVE_MAX_X;

	if (pos.y <= MOVE_MIN_Y)
		pos.y = MOVE_MIN_Y;
	else if (pos.y >= MOVE_MAX_Y)
		pos.y = MOVE_MAX_Y;

	//블록과 벽이동범위제한..
	//IntersectRect()안쓴이유는 나중에 물풍선 터지는거 처리할때 현재조건에서 조건을 조금바꿔서 충돌처리하기위해
	RECT characterRect{ pos.x, pos.y, pos.x + BLOCK_X, pos.y + BLOCK_Y };
	RECT objRect{ 0,0,0,0 };
	for (const auto& temp : inGameObjectVector)
	{
		if (temp->GetName() == "background")
			continue;
		else if (temp->GetName() == "Block")
		{
			objRect.left = temp->GetPosition().x;
			objRect.top = temp->GetPosition().y;
			objRect.right = temp->GetPosition().x + BLOCK_X;
			objRect.bottom = temp->GetPosition().y + BLOCK_Y - SIZE_TUNING;
		}
		else if (temp->GetName() == "Wall")
		{
			objRect.left = temp->GetPosition().x;
			objRect.top = temp->GetPosition().y;
			objRect.right = temp->GetPosition().x + BLOCK_X;
			objRect.bottom = temp->GetPosition().y + BLOCK_Y;
		}

		if (characterRect.left < objRect.right
			&& characterRect.right > objRect.left
			&& characterRect.top < objRect.bottom
			&& characterRect.bottom > objRect.top)
		{
			if (name.find("Red") != string::npos)
				pos = prevRedPos;
			else if (name.find("Blue") != string::npos)
				pos = prevBluePos;
		}
	}
}
