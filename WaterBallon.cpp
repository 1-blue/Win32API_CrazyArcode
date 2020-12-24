#include "WaterBallon.h"

void WaterBallon::SetExplosiontDir(const int x, const int y, const int dir, int& dirCount)
{
	int xCount = 0;		
	int yCount = 0;		

	//SetEffectDir 코드를 4번실행, 동서남북에 따라 물줄기 길이 체크 관련 변수 세팅
	switch (dir)
	{
	case Direction::TOP:
		yCount = -1;	break;
	case Direction::BOTTOM:
		yCount = 1;		break;
	case Direction::RIGHT:
		xCount = 1;		break;
	case Direction::LEFT:
		xCount = -1;	break;
	}

	for (int n = 1; n <= waterLength; n++)
	{
		//맵밖으로 물줄기 안나가게 맵크기 이상은 실행 안되게 설정
		if (((y + (yCount * n)) < 0) || ((y + (yCount * n)) > 10))
			return;
		else if (((x + (xCount * n)) < 0) || ((x + (xCount * n)) > 14))
			return;

		ObjectData::POSITION pos;
		pos.x = (x + (xCount * n));
		pos.y = (y + (yCount * n));

		switch ((mapData->data[y + (yCount * n)][x + (xCount * n)]))
		{
		case Objects::BLANK:
			++dirCount;		break;
		case Objects::BLOCK:
			hitObjectPos.emplace_back(pos);		return;
		case Objects::WALL:	return;;
		case Objects::WATERBALLON:
			hitWaterBallonstPos.emplace_back(pos);
			++dirCount;
			break;
		}
		//공격범위값저장
		attackArea.pos.x = mapPos.x;
		attackArea.pos.y = mapPos.y;
		switch (dir)
		{
		case Direction::TOP:
			attackArea.t = dirCount;	break;
		case Direction::RIGHT:
			attackArea.r = dirCount;	break;
		case Direction::BOTTOM:
			attackArea.b = dirCount;	break;
		case Direction::LEFT:
			attackArea.l = dirCount;	break;
		}
	}
		
}

WaterBallon::WaterBallon(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap,const int& waterLength)
			: DynamicObject(name, pos, size, hNumber, vNumber, hBitmap)
{
	charAnimationTick = GetTickCount64();	//생성시간기록
	order = pos.y;

	this->waterLength = waterLength;
}

WaterBallon::~WaterBallon()
{

}

void WaterBallon::Input()
{

}

void WaterBallon::Update()
{
	if (WaterBallonState::DIE == state)
		return;
	if (WaterBallonState::EXPLOSION == state)
	{
		if (!CheckmDelay(80, charAnimationTick))
			return;
		printhNumber++;

		if (printhNumber == hNumber)	//시간지나면,, 현재조건 : 8번반복하면
			state = WaterBallonState::DIE;

		return;
	}

	if (!CheckmDelay(300, charAnimationTick))
		return;

	printhNumber++;					//시간지나면 모양변경
	if (printhNumber == hNumber)	//시간지나면,, 현재조건 : 8번반복하면
		SetExplosionState();
}

void WaterBallon::Render(HDC hDC, HDC memDc)
{
	SelectObject(memDc, hBitmap);

	if (WaterBallonState::EXPLOSION != state)	//일반 출력
	{
		TransparentBlt(hDC,
			pos.x, pos.y,					//출력될 이미지 시작좌표
			imageWidth, imageHeight,		//출력될 이미지크기
			memDc,
			printhNumber * imageWidth, 0,	//이미지에서 출력할 시작위치
			imageWidth, imageHeight,		//이미지에서 출력할 이미지의 크기
			RGB(0, 0, 0));
	}
	else
	{
		//4방향 폭발 출력 + 중앙 폭발
		BoomRender(hDC, memDc, printDirCount.north, Direction::TOP);
		BoomRender(hDC, memDc, printDirCount.south, Direction::BOTTOM);
		BoomRender(hDC, memDc, printDirCount.east, Direction::RIGHT);
		BoomRender(hDC, memDc, printDirCount.west,  Direction::LEFT);
		BoomRender(hDC, memDc, 1, Direction::CENTER);
	}
}

void WaterBallon::BoomRender(HDC hDC, HDC memDc, const int printBoomImgCount, const int direction)
{
	int printBoomImgPos = 0;
	int addXPos = 0;	//출력위치 수정 변수, x
	int addYPos = 0;	//출력위치 수정 변수, y

	switch (direction)
	{
	case Direction::TOP:
		printBoomImgPos = 5;	addYPos = -1;	break;
	case Direction::BOTTOM:
		printBoomImgPos = 9;	addYPos = 1;	break;
	case Direction::RIGHT:
		printBoomImgPos = 7;	addXPos = 1;	break;
	case Direction::LEFT:
		printBoomImgPos = 3;	addXPos = -1;	break;
	case Direction::CENTER:
		printBoomImgPos = 1;	break;
	}

	for (int n = 1; n <= printBoomImgCount; n++)
	{
		//폭발 맨끝 처리
		if ((n == waterLength) && (printBoomImgPos != 1))
		{
			TransparentBlt(hDC,
				pos.x + (addXPos * n * BLOCK_X), pos.y + (addYPos * n * BLOCK_X),					//출력될 이미지 시작좌표
				imageWidth, imageHeight,		//출력될 이미지크기
				memDc,
				printhNumber * imageWidth, imageHeight * (printBoomImgPos-1),	//이미지에서 출력할 시작위치
				imageWidth, imageHeight,		//이미지에서 출력할 이미지의 크기
				RGB(0, 0, 0));

			return;
		}

		TransparentBlt(hDC,
			pos.x + (addXPos * n * BLOCK_X), pos.y + (addYPos * n * BLOCK_X),					//출력될 이미지 시작좌표
			imageWidth, imageHeight,		//출력될 이미지크기
			memDc,
			printhNumber * imageWidth, imageHeight * printBoomImgPos,	//이미지에서 출력할 시작위치
			imageWidth, imageHeight,		//이미지에서 출력할 이미지의 크기
			RGB(0, 0, 0));
	}
}

void WaterBallon::GetMapData(MapData* mapData)
{
	this->mapData = mapData;

	mapPos.x = ((pos.x + 20) / BLOCK_X) - 1;
	mapPos.y = ((pos.y + 2) / BLOCK_Y) - 1;

	//물풍선 위치 맵에 반영
	mapData->data[mapPos.y][mapPos.x] = 3;
}

const int WaterBallon::GetState()
{
	return state;
}

void WaterBallon::SetExplosionState()
{
	state = WaterBallonState::EXPLOSION;
	printhNumber = 0;
	mapData->data[mapPos.y][mapPos.x] = 0;	//물풍선 맵에서 제거

	SetExplosiontDir(mapPos.x, mapPos.y, Direction::TOP, printDirCount.north);
	SetExplosiontDir(mapPos.x, mapPos.y, Direction::BOTTOM, printDirCount.south);
	SetExplosiontDir(mapPos.x, mapPos.y, Direction::RIGHT, printDirCount.east);
	SetExplosiontDir(mapPos.x, mapPos.y, Direction::LEFT, printDirCount.west);
}

ObjectData::POSITION WaterBallon::GetMapPos()
{
	return mapPos;
}

vector<ObjectData::POSITION> WaterBallon::GetHitObjectPos()
{
	return hitObjectPos;
}

vector<ObjectData::POSITION> WaterBallon::GetHitWaterBallonsPos()
{
	return hitWaterBallonstPos;
}

void WaterBallon::SetColor(int color)
{
	this->color = color;
}

const int& WaterBallon::GetColor() const
{
	return color;
}

const AttackArea& WaterBallon::GetAttackArea() const
{
	return attackArea;
}

bool WaterBallon::CheckmDelay(const int delayTime, ULONGLONG& tick)
{
	if (GetTickCount64() > tick + delayTime)
	{
		tick = GetTickCount64();
		return true;
	}
	return false;
}