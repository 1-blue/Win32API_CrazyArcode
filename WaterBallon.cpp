#include "WaterBallon.h"

void WaterBallon::SetEffectDir(const int x, const int y, const int dir, int& dirCount)
{
	int xCount = 0;
	int yCount = 0;

	switch (dir)
	{
	case Direction::TOP:
		yCount = -1;
		break;
	case Direction::BOTTOM:
		yCount = 1;
		break;
	case Direction::RIGHT:
		xCount = 1;
		break;
	case Direction::LEFT:
		xCount = -1;
		break;
	}

	for (int n = 1; n <= waterLength; n++)
	{
		//범위 제한
		if (((y + (yCount * n)) < 0) || ((y + (yCount * n)) > 10))
			break;
		else if (((x + (xCount * n)) < 0) || ((x + (xCount * n)) > 14))
			break;

		if (mapData.data[y + (yCount * n)][x + (xCount * n)] != 0)
		{
			hitObjectPos[dirCount].x = x + (xCount * n)
			break;
		}

		dirCount++;
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
	if (isEffect)
	{
		if (CheckmDelay(600, deadlineTick))
			isAlive = false;

		if (!CheckmDelay(50, charAnimationTick))
			return;
		printhNumber++;

		if (printhNumber == hNumber)	//시간지나면,, 현재조건 : 8번반복하면
			printhNumber = 0;
		return;
	}

	if (!CheckmDelay(300, charAnimationTick))
		return;

	printhNumber++;					//시간지나면 모양변경
	if (printhNumber == hNumber)	//시간지나면,, 현재조건 : 8번반복하면
	{
		printhNumber = 0;
		isEffect = true;
		deadlineTick = GetTickCount64();	// 이펙트 시작 타임부터 죽음까지 시간 체크
	}
}

void WaterBallon::Render(HDC hDC, HDC memDc)
{
	SelectObject(memDc, hBitmap);

	if (!isEffect)	//일반 출력
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
		if ((n == printBoomImgCount ) && (printBoomImgPos != 1))
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
			pos.x +(addXPos * n * BLOCK_X), pos.y + (addYPos * n * BLOCK_X),					//출력될 이미지 시작좌표
			imageWidth, imageHeight,		//출력될 이미지크기
			memDc,
			printhNumber * imageWidth, imageHeight * printBoomImgPos,	//이미지에서 출력할 시작위치
			imageWidth, imageHeight,		//이미지에서 출력할 이미지의 크기
			RGB(0, 0, 0));
	}
}

void WaterBallon::GetMapData(const MapData& mapData)
{
	this->mapData = mapData;

	int mapXpos = ((pos.x + 20) / BLOCK_X) - 1;
	int mapYpos = ((pos.y + 2) / BLOCK_Y) - 1;

	SetEffectDir(mapXpos, mapYpos,Direction::TOP, printDirCount.north);
	SetEffectDir(mapXpos, mapYpos, Direction::BOTTOM, printDirCount.south);
	SetEffectDir(mapXpos, mapYpos, Direction::RIGHT, printDirCount.east);
	SetEffectDir(mapXpos, mapYpos, Direction::LEFT, printDirCount.west);
}

const bool WaterBallon::GetIsAlive()
{
	return isAlive;
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
