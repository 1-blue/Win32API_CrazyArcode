#include "Character.h"
#include "MessageQueue.h"

Character::Character(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap, CharacterStatsData characterStats)
	: DynamicObject(name, pos, size, hNumber, vNumber, hBitmap)
{

	switch (name)
	{
	case EnumObj::RedBazzi:
		color = CharacterColor::RED;
		characterName = CharacterName::BAZZI;
		break;
	case EnumObj::RedDizni:
		color = CharacterColor::RED;
		characterName = CharacterName::DIZNI;
		break;
	case EnumObj::BlueBazzi:
		color = CharacterColor::BLUE;
		characterName = CharacterName::BAZZI;
		break;
	case EnumObj::BlueDizni:
		color = CharacterColor::BLUE;
		characterName = CharacterName::DIZNI;
		break;
	}

	this->characterStats = characterStats;

	Init();
}

Character::~Character()
{

}

void Character::Init()
{
	redValue.state = State::NORMAL;		//현재상태
	redValue.isAttackPossible = true;	//공격가능여부
	redValue.isMoveable = true;			//이동가능여부

	blueValue.state = State::NORMAL;
	blueValue.isAttackPossible = true;
	blueValue.isMoveable = true;
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

		if (!CheckmDelay(charAnimationTick, 100) && (prevDir == dir))
			break;

		printPos.x += imageWidth;
		printPos.y = 0;
		if (printPos.x >= size.width)
			printPos.x = 0;

		prevDir = Diraction::LEFT;
		break;
	case Diraction::TOP:
		pos.y -= characterStats.speed + 4;

		if (!CheckmDelay(charAnimationTick, 100) && (prevDir == dir))
			break;

		printPos.x += imageWidth;
		printPos.y = imageHeight;
		if (printPos.x >= size.width)
			printPos.x = 0;

		prevDir = Diraction::TOP;
		break;
	case Diraction::RIGHT:
		pos.x += characterStats.speed + 4;

		if (!CheckmDelay(charAnimationTick, 100) && (prevDir == dir))
			break;

		printPos.x += imageWidth;
		printPos.y = imageHeight * 2;
		if (printPos.x >= size.width)
			printPos.x = 0;

		prevDir = Diraction::RIGHT;
		break;
	case Diraction::BOTTOM:
		pos.y += characterStats.speed + 4;

		if (!CheckmDelay(charAnimationTick, 100) && (prevDir == dir))
			break;

		printPos.x += imageWidth;
		printPos.y = imageHeight * 3;
		if (printPos.x >= size.width)
			printPos.x = 0;

		prevDir = Diraction::BOTTOM;
		break;
	}
	order = pos.y;

	//갇힌상태라면 실행
	if (redValue.state == State::TRAPPED)
	{
		//if(바늘사용하면)
		//{
		//	redValue.state = State::NORMAL;
		//	redValue.trappedPrinthNumber = 0;
		//}
		if (CheckmDelay(redValue.time, 150))
		{
			redValue.trappedPrinthNumber++;
			if (redValue.trappedPrinthNumber > trappedImage.hNumber)
			{
				redValue.state = State::DIE;
				redValue.isMoveable = false;
			}
		}
	}
	else if (blueValue.state == State::TRAPPED)
	{
		if (CheckmDelay(blueValue.time, 150))
		{
			blueValue.trappedPrinthNumber++;
			if (blueValue.trappedPrinthNumber > trappedImage.hNumber)
			{
				blueValue.state = State::DIE;
				blueValue.isMoveable = false;
			}
		}
	}

	//죽을상태라면
	if (redValue.state == State::DIE)
	{
		if (CheckmDelay(redValue.time, 150))
		{
			redValue.diePrinthNumber++;
			if (redValue.diePrinthNumber > dieImage.hNumber)
			{
				//게임종료UI띄우기
			}
		}
	}
	else if (blueValue.state == State::DIE)
	{
		if (CheckmDelay(blueValue.time, 150))
		{
			blueValue.diePrinthNumber++;
			if (blueValue.diePrinthNumber > dieImage.hNumber)
			{
				//게임종료UI띄우기
			}
		}
	}
}

void Character::LateUpdate(const list<Obj*>& inGameObjectVector)
{
	//이동제한
	MapImmovableArea();
	StaticObjectmmovableArea(inGameObjectVector);
	WaterBallonImmovableArea();
	dir = -1;
}

void Character::Render(HDC hDC, HDC memDc)
{
	switch (color)
	{
	case CharacterColor::RED:
		switch (redValue.state)
		{
		case State::NORMAL:
			SelectObject(memDc, hBitmap);
			TransparentBlt(hDC,
				pos.x, pos.y,				//출력될 이미지 시작좌표
				imageWidth, imageHeight,	//출력될 이미지크기
				memDc,
				printPos.x, printPos.y,		//이미지에서 출력할 시작위치
				imageWidth, imageHeight,	//이미지에서 출력할 이미지의 크기
				RGB(255, 0, 255));
			break;

		case State::TRAPPED:
			SelectObject(memDc, trappedImage.hBitmap);
			TransparentBlt(hDC,
				pos.x, pos.y,				//출력될 이미지 시작좌표
				trappedImage.imageWidth, trappedImage.imageHeight,	//출력될 이미지크기
				memDc,
				trappedImage.imageWidth * redValue.trappedPrinthNumber, trappedImage.imageHeight * redValue.trappedPrintvNumber,		//이미지에서 출력할 시작위치
				trappedImage.imageWidth, trappedImage.imageHeight,	//이미지에서 출력할 이미지의 크기
				RGB(255, 0, 255));
			break;

		case State::DIE:
			SelectObject(memDc, dieImage.hBitmap);
			TransparentBlt(hDC,
				pos.x, pos.y,				//출력될 이미지 시작좌표
				dieImage.imageWidth, dieImage.imageHeight,	//출력될 이미지크기
				memDc,
				dieImage.imageWidth * redValue.diePrinthNumber, dieImage.imageHeight * redValue.diePrintvNumber,		//이미지에서 출력할 시작위치
				dieImage.imageWidth, dieImage.imageHeight,	//이미지에서 출력할 이미지의 크기
				RGB(255, 0, 255));
			break;
		}
		break;
	case CharacterColor::BLUE:
		switch (blueValue.state)
		{
		case State::NORMAL:
			SelectObject(memDc, hBitmap);
			TransparentBlt(hDC,
				pos.x, pos.y,				//출력될 이미지 시작좌표
				imageWidth, imageHeight,	//출력될 이미지크기
				memDc,
				printPos.x, printPos.y,		//이미지에서 출력할 시작위치
				imageWidth, imageHeight,	//이미지에서 출력할 이미지의 크기
				RGB(255, 0, 255));
			break;

		case State::TRAPPED:
			SelectObject(memDc, trappedImage.hBitmap);
			TransparentBlt(hDC,
				pos.x, pos.y,				//출력될 이미지 시작좌표
				trappedImage.imageWidth, trappedImage.imageHeight,	//출력될 이미지크기
				memDc,
				trappedImage.imageWidth * blueValue.trappedPrinthNumber, trappedImage.imageHeight * blueValue.trappedPrintvNumber,		//이미지에서 출력할 시작위치
				trappedImage.imageWidth, trappedImage.imageHeight,	//이미지에서 출력할 이미지의 크기
				RGB(255, 0, 255));
			break;

		case State::DIE:
			SelectObject(memDc, dieImage.hBitmap);
			TransparentBlt(hDC,
				pos.x, pos.y,				//출력될 이미지 시작좌표
				dieImage.imageWidth, dieImage.imageHeight,	//출력될 이미지크기
				memDc,
				dieImage.imageWidth * blueValue.diePrinthNumber, dieImage.imageHeight * blueValue.diePrintvNumber,		//이미지에서 출력할 시작위치
				dieImage.imageWidth, dieImage.imageHeight,	//이미지에서 출력할 이미지의 크기
				RGB(255, 0, 255));
			break;
		}
	}

	//테스트용 현재 플레이어 위치좌표출력
	static char c[255];
	if (CharacterColor::RED == color)
	{
		sprintf_s(c, "RED : %d, %d", pos.x, pos.y);
		TextOut(hDC, 10, 10, c, sizeof(c));
	}
	if (CharacterColor::BLUE == color)
	{
		sprintf_s(c, "BLUE : %d, %d", pos.x, pos.y);
		TextOut(hDC, 10, 50, c, sizeof(c));
	}
}

void Character::GetDefaultImage(const pImageData trappedImage, const pImageData dieImage)
{
	//trapped, die저장
	BITMAP bmp;
	GetObject(trappedImage->hBitmap, sizeof(BITMAP), &bmp);

	this->trappedImage.name = trappedImage->name;							//이름
	this->trappedImage.hBitmap = trappedImage->hBitmap;						//비트맵
	this->trappedImage.hNumber = trappedImage->hNumber;						//가로이미지수
	this->trappedImage.vNumber = trappedImage->vNumber;						//세로이미지
	this->trappedImage.imageWidth = bmp.bmWidth / trappedImage->hNumber;	//이미지크기/가로이미지수
	this->trappedImage.imageHeight = bmp.bmHeight / trappedImage->vNumber;	//이미지크기/세로이미지수

	GetObject(dieImage->hBitmap, sizeof(BITMAP), &bmp);

	this->dieImage.name = dieImage->name;
	this->dieImage.hBitmap = dieImage->hBitmap;
	this->dieImage.hNumber = dieImage->hNumber;
	this->dieImage.vNumber = dieImage->vNumber;
	this->dieImage.imageWidth = bmp.bmWidth / dieImage->hNumber;
	this->dieImage.imageHeight = bmp.bmHeight / dieImage->vNumber;

	//캐릭터마다 출력될 위치값 지정
	//여기밑에 코드정리할때 0~3은 전부 enum으로 만들고 이미지 보면서 만들기
	switch (color)
	{
	case CharacterColor::RED:
		redValue.trappedPrinthNumber = 0;			//trapped 가로 출력될 이미지 번호
		redValue.diePrinthNumber = 0;				//die 가로 출력될 이미지 번호
		switch (characterName)
		{
		case CharacterName::BAZZI:
			redValue.trappedPrintvNumber = 0;		//trapped 세로 출력될 이미지 번호
			redValue.diePrintvNumber = 0;			//die 세로 출력될 이미지 번호
			break;
		case CharacterName::DIZNI:
			redValue.trappedPrintvNumber = 1;
			redValue.diePrintvNumber = 2;
			break;
		}
		break;
	case CharacterColor::BLUE:
		blueValue.trappedPrinthNumber = 0;
		blueValue.diePrinthNumber = 0;
		switch (characterName)
		{
		case CharacterName::BAZZI:
			blueValue.trappedPrintvNumber = 0;
			blueValue.diePrintvNumber = 1;
			break;
		case CharacterName::DIZNI:
			blueValue.trappedPrintvNumber = 1;
			blueValue.diePrintvNumber = 3;
			break;
		}
		break;
	}
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
			attack.pos.y = attack.pos.y + (BLOCK_Y - interval) - 2;
		else
			attack.pos.y = attack.pos.y - interval - 2;		//이거 물풍선과 블럭사이의 y좌표에 2만큼오차가 생겨서 빼주는건데 원인찾아서 고치기
	}
}

void Character::Manual()
{
	switch (color)
	{
	case CharacterColor::RED:
		if (redValue.isMoveable)
		{
			redValue.prevPos = pos;
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
			if (redValue.isAttackPossible)
			{
				if (GetAsyncKeyState(VK_RSHIFT) & 0x0001)		//공격
				{
					attack.isColor = CharacterColor::BLUE;
					attack.pos.x = pos.x;
					attack.pos.y = pos.y + imageHeight / 2;
					SettingAttackPos();		//물풍선 놓는위치 지정
					OverlapChack();			//물풍선 중복설치금지를 위한 코드
					redValue.lastWaterBallonPos = attack.pos;	//마지막물풍선위치저장
				}
			}
			//테스트용
			if (GetAsyncKeyState('P'))
				Trapped();
		}
		break;
	case CharacterColor::BLUE:
		if (blueValue.isMoveable)
		{
			blueValue.prevPos = pos;
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
			if (blueValue.isAttackPossible)
			{
				if (GetAsyncKeyState(VK_LSHIFT) & 0x0001)		//공격
				{
					attack.isColor = CharacterColor::RED;
					attack.pos.x = pos.x;
					attack.pos.y = pos.y + imageHeight / 2;
					SettingAttackPos();		//물풍선 놓는위치 지정
					OverlapChack();			//물풍선 중복설치 금지를 위한
					blueValue.lastWaterBallonPos = attack.pos;
				}
			}

			//테스트용
			if (GetAsyncKeyState('Q'))
				Trapped();
		}
		break;
	}
}

bool Character::CheckmDelay(ULONGLONG& animationTick, const int delayTime)
{
	if (GetTickCount64() > animationTick + delayTime)
	{
		animationTick = GetTickCount64();
		return true;
	}
	return false;
}

void Character::SetWaterBallonList(list<ObjectData::Position> waterBallonPos)
{
	this->waterBallonPos = waterBallonPos;
}

Attack& Character::GetAttack()
{
	return this->attack;
}

void Character::OverlapChack()
{
	if (waterBallonPos.empty())
		attack.isAttack = true;

	bool isExist = false;
	for (const auto& wbPos : waterBallonPos)
	{
		if (attack.pos.x == wbPos.x && attack.pos.y == wbPos.y)
			isExist = true;
	}
	if (isExist)
		return;

	attack.isAttack = true;
	switch (color)
	{
	case CharacterColor::RED:
		if (redValue.isRevisit == false)
			redValue.isRevisit = true;
		break;
	case CharacterColor::BLUE:
		if (blueValue.isRevisit == false)
			blueValue.isRevisit = true;
		break;
	}
}

void Character::MapImmovableArea()
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
}

//벡터를 받는게 아니라, 배열에 저장되어있는 숫자값을 받아가지고 하는게 더 빠를듯
void Character::StaticObjectmmovableArea(const list<Obj*>& inGameObjectVector)
{
	RECT characterRect{ pos.x, pos.y, pos.x + BLOCK_X, pos.y + BLOCK_Y };
	RECT objRect{ 0,0,0,0 };

	//블록과 벽이동범위제한..
	for (const auto& tempObj : inGameObjectVector)
	{
		if (tempObj->GetName() == MessageQueue::StringToEnum("background"))
			continue;
		else if (tempObj->GetName() == MessageQueue::StringToEnum("Block"))
		{
			objRect.left = tempObj->GetPosition().x;
			objRect.top = tempObj->GetPosition().y - SIZE_TUNING;
			objRect.right = tempObj->GetPosition().x + BLOCK_X;
			objRect.bottom = tempObj->GetPosition().y + BLOCK_Y - SIZE_TUNING;
		}
		else if (tempObj->GetName() == MessageQueue::StringToEnum("Wall"))
		{
			objRect.left = tempObj->GetPosition().x;
			objRect.top = tempObj->GetPosition().y;
			objRect.right = tempObj->GetPosition().x + BLOCK_X;
			objRect.bottom = tempObj->GetPosition().y + BLOCK_Y;
		}

		//충돌체크 -> 플레이어 색깔체크 -> 플레이어 방향체크 -> 플레이어가 벽에 부딪혔을때 옆으로 비껴나가야할지 체크
		if (characterRect.left < objRect.right && characterRect.right > objRect.left
			&& characterRect.top < objRect.bottom && characterRect.bottom > objRect.top)
		{
			switch (color)
			{
			case CharacterColor::RED:
				//끝에 조금 스치면 빗겨서 앞으로나가게 만드는 구문
				//15는 좌측, 우측에서 15이내로 떨어져있을경우에만 서서히 좌측/우측으로 이동할때 값으로 사용
				switch (dir)
				{
				case Diraction::TOP:
				case Diraction::BOTTOM:
					if (objRect.right > characterRect.left&& objRect.right - characterRect.left <= PERMIT_RANGE)
						redValue.prevPos.x++;
					else if (objRect.left < characterRect.right && characterRect.right - objRect.left <= PERMIT_RANGE)
						redValue.prevPos.x--;
					break;
				case Diraction::LEFT:
				case Diraction::RIGHT:
					if (objRect.bottom > characterRect.top&& objRect.bottom - characterRect.top <= PERMIT_RANGE)
						redValue.prevPos.y++;
					else if (objRect.top < characterRect.bottom && characterRect.bottom - objRect.top <= PERMIT_RANGE)
						redValue.prevPos.y--;
					break;
				}
				pos = redValue.prevPos;
				break;

			case CharacterColor::BLUE:
				switch (dir)
				{
				case Diraction::TOP:
				case Diraction::BOTTOM:
					if (objRect.right > characterRect.left&& objRect.right - characterRect.left <= PERMIT_RANGE)
						blueValue.prevPos.x++;
					else if (objRect.left < characterRect.right && characterRect.right - objRect.left <= PERMIT_RANGE)
						blueValue.prevPos.x--;
					break;
				case Diraction::LEFT:
				case Diraction::RIGHT:
					if (objRect.bottom > characterRect.top&& objRect.bottom - characterRect.top <= PERMIT_RANGE)
						blueValue.prevPos.y++;
					else if (objRect.top < characterRect.bottom && characterRect.bottom - objRect.top <= PERMIT_RANGE)
						blueValue.prevPos.y--;
					break;
				}
				pos = blueValue.prevPos;
				break;
			}
		}
	}
}

void Character::WaterBallonImmovableArea()
{
	RECT characterRect{ pos.x, pos.y, pos.x + BLOCK_X, pos.y + BLOCK_Y };
	RECT objRect{ 0,0,0,0 };

	//물풍선 이동범위 제한
	for (const auto& wbPos : waterBallonPos)
	{
		switch (color)
		{
		case CharacterColor::RED:
			objRect.left = redValue.lastWaterBallonPos.x;
			objRect.top = redValue.lastWaterBallonPos.y - SIZE_TUNING;
			objRect.right = redValue.lastWaterBallonPos.x + BLOCK_X;
			objRect.bottom = redValue.lastWaterBallonPos.y + BLOCK_Y - SIZE_TUNING;
			if (redValue.isRevisit)
			{
				if (!(characterRect.left < objRect.right && characterRect.right > objRect.left
					&& characterRect.top < objRect.bottom && characterRect.bottom > objRect.top))
				{
					redValue.isRevisit = false;
				}
				else
					continue;
			}
			break;
		case CharacterColor::BLUE:
			objRect.left = blueValue.lastWaterBallonPos.x;
			objRect.top = blueValue.lastWaterBallonPos.y - SIZE_TUNING;
			objRect.right = blueValue.lastWaterBallonPos.x + BLOCK_X;
			objRect.bottom = blueValue.lastWaterBallonPos.y + BLOCK_Y - SIZE_TUNING;

			if (blueValue.isRevisit)
			{
				if (!(characterRect.left < objRect.right && characterRect.right > objRect.left
					&& characterRect.top < objRect.bottom && characterRect.bottom > objRect.top))
				{
					blueValue.isRevisit = false;
				}
				else
					continue;
			}
			break;
		}

		objRect.left = wbPos.x;
		objRect.top = wbPos.y - SIZE_TUNING;
		objRect.right = wbPos.x + BLOCK_X;
		objRect.bottom = wbPos.y + BLOCK_Y - SIZE_TUNING;

		//비껴서 앞으로나가기 + 이동제한
		if (characterRect.left < objRect.right && characterRect.right > objRect.left
			&& characterRect.top < objRect.bottom && characterRect.bottom > objRect.top)
		{
			switch (color)
			{
			case CharacterColor::RED:
				switch (dir)
				{
				case Diraction::TOP:
				case Diraction::BOTTOM:
					if (objRect.right > characterRect.left&& objRect.right - characterRect.left <= PERMIT_RANGE)
						redValue.prevPos.x++;
					else if (objRect.left < characterRect.right && characterRect.right - objRect.left <= PERMIT_RANGE)
						redValue.prevPos.x--;
					break;
				case Diraction::LEFT:
				case Diraction::RIGHT:
					if (objRect.bottom > characterRect.top&& objRect.bottom - characterRect.top <= PERMIT_RANGE)
						redValue.prevPos.y++;
					else if (objRect.top < characterRect.bottom && characterRect.bottom - objRect.top <= PERMIT_RANGE)
						redValue.prevPos.y--;
					break;
				}
				pos = redValue.prevPos;
				break;
			case CharacterColor::BLUE:
				switch (dir)
				{
				case Diraction::TOP:
				case Diraction::BOTTOM:
					if (objRect.right > characterRect.left&& objRect.right - characterRect.left <= PERMIT_RANGE)
						blueValue.prevPos.x++;
					else if (objRect.left < characterRect.right && characterRect.right - objRect.left <= PERMIT_RANGE)
						blueValue.prevPos.x--;
					break;
				case Diraction::LEFT:
				case Diraction::RIGHT:
					if (objRect.bottom > characterRect.top&& objRect.bottom - characterRect.top <= PERMIT_RANGE)
						blueValue.prevPos.y++;
					else if (objRect.top < characterRect.bottom && characterRect.bottom - objRect.top <= PERMIT_RANGE)
						blueValue.prevPos.y--;
					break;
				}
				pos = blueValue.prevPos;
				break;
			}
		}
	}
}

void Character::Trapped()
{
	//this->characterStats.speed -= 4;		//물풍선 갖히면 속도감소.. 현재는 키 누를때 실행이라 한번에 여려번입력됨

	switch (color)
	{
	case CharacterColor::RED:
		redValue.time = GetTickCount64();		//갇히는 시작시간
		redValue.state = State::TRAPPED;		//상태바꾸기
		redValue.isAttackPossible = false;		//공격불가능
		break;
	case CharacterColor::BLUE:
		blueValue.time = GetTickCount64();		//갇히는 시작시간
		blueValue.state = State::TRAPPED;		//상태바꾸기
		blueValue.isAttackPossible = false;		//공격불가능
		break;
	}
}