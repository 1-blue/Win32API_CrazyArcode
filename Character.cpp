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
	//+20해주는 이유는 맵의 시작위치가 (20,47)이라 +20을 해줘야 값이맞음
	int interval = 0;
	if ((attack.pos.x + 20) % BLOCK_X != 0)
	{
		interval = (attack.pos.x + 20) % BLOCK_X;
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
			attack.isColor = CharacterColor::BLUE;
			attack.pos.x = pos.x;
			attack.pos.y = pos.y + imageHeight / 2;
			SettingAttackPos();		//물풍선 놓는위치 지정
			OverlapChack();			//물풍선 중복설치금지를 위한 코드
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
			attack.isColor = CharacterColor::RED;
			attack.pos.x = pos.x;
			attack.pos.y = pos.y + imageHeight / 2;
			SettingAttackPos();		//물풍선 놓는위치 지정
			OverlapChack();			//물풍선 중복설치 금지를 위한
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

	RECT characterRect{ pos.x, pos.y, pos.x + BLOCK_X, pos.y + BLOCK_Y };
	RECT objRect{ 0,0,0,0 };

	//블록과 벽이동범위제한..
	//IntersectRect()안쓴이유는 나중에 물풍선 터지는거 처리할때 현재조건에서 조건을 조금바꿔서 충돌처리하기위해
	for (const auto& tempObj : inGameObjectVector)
	{
		if (tempObj->GetName() == "background")
			continue;
		else if (tempObj->GetName() == "Block")
		{
			objRect.left = tempObj->GetPosition().x;
			objRect.top = tempObj->GetPosition().y - SIZE_TUNING;
			objRect.right = tempObj->GetPosition().x + BLOCK_X;
			objRect.bottom = tempObj->GetPosition().y + BLOCK_Y - SIZE_TUNING;
		}
		else if (tempObj->GetName() == "Wall")
		{
			objRect.left = tempObj->GetPosition().x;
			objRect.top = tempObj->GetPosition().y;
			objRect.right = tempObj->GetPosition().x + BLOCK_X;
			objRect.bottom = tempObj->GetPosition().y + BLOCK_Y;
		}

		if (characterRect.left < objRect.right && characterRect.right > objRect.left
			&& characterRect.top < objRect.bottom && characterRect.bottom > objRect.top)
		{
			if (name.find("Red") != string::npos)
			{
				//끝에 조금 스치면 빗겨서 앞으로나가게 만드는 구문
				//이것때문에 statiObject에 부딪힐경우 제자리에서 왔다갔다하는 버그생김 수정필요..
				//15는 좌측, 우측에서 15이내로 떨어져있을경우에만 서서히 좌측/우측으로 이동할때 값으로 사용
				if (objRect.right > characterRect.left && objRect.right - characterRect.left <= 15)
					prevRedPos.x++;
				else if (objRect.left < characterRect.right && characterRect.right - objRect.left <= 15)
					prevRedPos.x--;
				if (objRect.bottom > characterRect.top&& objRect.bottom - characterRect.top <= 15)
					prevRedPos.y++;
				else if (objRect.top < characterRect.bottom && characterRect.bottom - objRect.top <= 15)
					prevRedPos.y--;
				pos = prevRedPos;
			}
			else if (name.find("Blue") != string::npos)
			{
				if (objRect.right > characterRect.left&& objRect.right - characterRect.left <= 15)
					prevBluePos.x++;
				else if (objRect.left < characterRect.right && characterRect.right - objRect.left <= 15)
					prevBluePos.x--;
				if (objRect.bottom > characterRect.top&& objRect.bottom - characterRect.top <= 15)
					prevBluePos.y++;
				else if (objRect.top < characterRect.bottom && characterRect.bottom - objRect.top <= 15)
					prevBluePos.y--;
				pos = prevBluePos;
			}
		}
	}

	int waterBallonLastIndex = 0;

	//물풍선 이동범위 제한
	for (const auto& wbPos : waterBallonPos)
	{
		waterBallonLastIndex++;

		objRect.left = wbPos.x;
		objRect.top = wbPos.y;
		objRect.right = wbPos.x + BLOCK_X;
		objRect.bottom = wbPos.y + BLOCK_Y - SIZE_TUNING;

		if (waterBallonLastIndex == waterBallonPos.size() && isRevisit)
		{
			if (!(characterRect.left < objRect.right && characterRect.right > objRect.left
				&& characterRect.top < objRect.bottom && characterRect.bottom > objRect.top))
			{
				isRevisit = false;
			}
			else
				continue;
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

void Character::GetWaterBallonList(vector<ObjectData::Position> waterBallonPos)
{
	this->waterBallonPos = waterBallonPos;
}

void Character::OverlapChack()
{
	//중복설치금지를 위한 코드
	if (waterBallonPos.empty())
		attack.isAttack = true;

	bool isExist = false;
	for (const auto& wbPos : waterBallonPos)
	{
		if (attack.pos.x == wbPos.x && attack.pos.y == wbPos.y)
			isExist = true;
	}
	if (!isExist)
	{
		attack.isAttack = true;
		if (isRevisit == false)
			isRevisit = true;
	}
}