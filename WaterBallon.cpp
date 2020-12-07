#include "WaterBallon.h"

WaterBallon::WaterBallon(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap)
			: DynamicObject(name, pos, size, hNumber, vNumber, hBitmap)
{
	//생성시시간기록
}

WaterBallon::~WaterBallon()
{

}

void WaterBallon::Input()
{
	//시간체크
}

void WaterBallon::Update()
{
	//시간지나면 삭제
	//시간지나면 모양변경
}

void WaterBallon::Render(HDC hDC, HDC memDc)
{
	SelectObject(memDc, hBitmap);

	TransparentBlt(hDC,
		pos.x, pos.y,					//출력될 이미지 시작좌표
		imageWidth, imageHeight,		//출력될 이미지크기
		memDc,
		0, 0,							//이미지에서 출력할 시작위치
		imageWidth, imageHeight,		//이미지에서 출력할 이미지의 크기
		RGB(0, 0, 0));
}
