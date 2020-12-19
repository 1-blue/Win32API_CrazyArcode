#include "WaterBallon.h"

void WaterBallon::SetEffect4Dir()
{
	//설치 시 플레이어 물줄기, 주변 오브젝트 이용해서 맥스카운트 설정
	//생성자에서 물줄기 크기 받는거 추가 해야 함
}

WaterBallon::WaterBallon(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap)
			: DynamicObject(name, pos, size, hNumber, vNumber, hBitmap)
{
	charAnimationTick = GetTickCount64();	//생성시간기록
	order = pos.y;

	//출력 테스트용
	printDirCount.north = 4;
	printDirCount.south = 4;
	printDirCount.east = 4;
	printDirCount.west = 4;
	//출력 테스트용
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
		BoomRender(hDC, memDc, printDirCount.north, Diraction::TOP);
		BoomRender(hDC, memDc, printDirCount.south, Diraction::BOTTOM);
		BoomRender(hDC, memDc, printDirCount.east, Diraction::RIGHT);
		BoomRender(hDC, memDc, printDirCount.west,  Diraction::LEFT);
		BoomRender(hDC, memDc, 1, Diraction::CENTER);
	}

}

void WaterBallon::BoomRender(HDC hDC, HDC memDc, const int printBoomImgCount, const int direction)
{
	int printBoomImgPos = 0;
	int addXPos = 0;	//출력위치 수정 변수, x
	int addYPos = 0;	//출력위치 수정 변수, y

	switch (direction)
	{
	case Diraction::TOP:
		printBoomImgPos = 5;	addYPos = -1;	break;
	case Diraction::BOTTOM:
		printBoomImgPos = 9;	addYPos = 1;	break;
	case Diraction::RIGHT:
		printBoomImgPos = 7;	addXPos = 1;	break;
	case Diraction::LEFT:
		printBoomImgPos = 3;	addXPos = -1;	break;
	case Diraction::CENTER:
		printBoomImgPos = 1;	break;
	}

	for (int n = 0; n < printBoomImgCount; n++)
	{
		//폭발 맨끝 처리
		if ((n == (printBoomImgCount - 1)) && (printBoomImgPos != 1))
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
	SetEffect4Dir();
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
