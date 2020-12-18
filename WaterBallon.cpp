#include "WaterBallon.h"

WaterBallon::WaterBallon(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap)
			: DynamicObject(name, pos, size, hNumber, vNumber, hBitmap)
{
	charAnimationTick = GetTickCount64();	//생성시간기록
	order = pos.y;
}

WaterBallon::~WaterBallon()
{

}

void WaterBallon::Input()
{

}

void WaterBallon::Update()
{
	if (!CheckmDelay(300))
		return;

	printhNumber++;					//시간지나면 모양변경
	if (printhNumber == hNumber)	//시간지나면,, 현재조건 : 8번반복하면
	{
		printhNumber = 0;
		isAlive = false;
	}
}

void WaterBallon::Render(HDC hDC, HDC memDc)
{
	SelectObject(memDc, hBitmap);

	TransparentBlt(hDC,
		pos.x, pos.y,					//출력될 이미지 시작좌표
		imageWidth, imageHeight,		//출력될 이미지크기
		memDc,
		printhNumber * imageWidth, 0,	//이미지에서 출력할 시작위치
		imageWidth, imageHeight,		//이미지에서 출력할 이미지의 크기
		RGB(0, 0, 0));
}

const bool WaterBallon::GetIsAlive()
{
	return isAlive;
}

bool WaterBallon::CheckmDelay(const int delayTime)
{
	if (GetTickCount64() > charAnimationTick + delayTime)
	{
		charAnimationTick = GetTickCount64();
		return true;
	}
	return false;
}
