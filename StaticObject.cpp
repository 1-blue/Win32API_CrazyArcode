#include "StaticObject.h"

extern HWND hWnd;
int StaticObject::redImageNumber = 0;
int StaticObject::blueImageNumber = 0;
int StaticObject::mapImageNumber = 0;

StaticObject::StaticObject()
{
}

StaticObject::StaticObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int kinds, int number, int interval, HBITMAP hBitmap) : Obj(name, pos, size, kinds, number, interval, hBitmap)
{
}

StaticObject::~StaticObject()
{
	Obj::~Obj();
}

void StaticObject::Input()
{
	if (imageNumber <= 1)	//이미지수가 2개이상일때 (이미지 변화할 애들만 변화시키위해)
		return;

	GetCursorPos(&cursorPos);			//모니터에서 마우스위치값받아옴
	ScreenToClient(hWnd, &cursorPos);	//현재 윈도우창에서 마우스위치값으로 변환

	//커서가 이미지위로올라오면 이미지변화.. 여기도 원래는 switch~case사용해서 구별해야함
	if ((cursorPos.x >= pos.x && cursorPos.x <= pos.x + size.width)
		&& (cursorPos.y >= pos.y && cursorPos.y <= pos.y + size.height / imageNumber))
	{
		printImageNumber = 1;

		//버튼클릭하면
		if ((GetAsyncKeyState(MK_LBUTTON)))
		{
			if ("bazziPickImage" == name)
				redImageNumber = 0;
			if ("dizniPickImage" == name)
				redImageNumber = 1;
			if ("RandomPickImage" == name)
				redImageNumber = 2;
			if ("mapPick" == name)
				++mapImageNumber > 1 ? mapImageNumber = 0 : 0;

			if ("start" == name)
			{
				//redImageNumber, blueImageNumber, mapImageNumber값들을 게임시작시 데이터로 사용
			}
		}
		if ((GetAsyncKeyState(MK_RBUTTON)))
		{
			if ("bazziPickImage" == name)
				blueImageNumber = 0;
			if ("dizniPickImage" == name)
				blueImageNumber = 1;
			if ("RandomPickImage" == name)
				blueImageNumber = 2;
		}
	}
	else
	{
		printImageNumber = 0;
	}
}

void StaticObject::Render(HDC hDC, HDC memDc)
{
	SelectObject(memDc, hBitmap);

	if ("redCharacter" == name)
		printImageNumber = redImageNumber;
	if ("blueCharacter" == name)
		printImageNumber = blueImageNumber;
	if ("map" == name)
		printImageNumber = mapImageNumber;

	//이미지를 자를방향을 구분해서 출력
	switch (kinds)
	{
	case ObjectData::HORIZONTAL:
		TransparentBlt(hDC,
			pos.x, pos.y,									//출력될 이미지 시작좌표
			size.width / imageNumber, size.height,			//출력될 이미지크기
			memDc,
			size.width / imageNumber * printImageNumber, 0,	//이미지에서 출력할 시작위치
			size.width / imageNumber, size.height,			//이미지에서 출력할 이미지의 크기
			RGB(255, 0, 255));
		break;

	case ObjectData::VERTICAL:
		TransparentBlt(hDC,
			pos.x, pos.y,										//출력될 이미지 시작좌표
			size.width, size.height / imageNumber,				//출력될 이미지크기
			memDc,
			0, size.height / imageNumber * printImageNumber,	//이미지에서 출력할 시작위치
			size.width, size.height / imageNumber,				//이미지에서 출력할 이미지의 크기
			RGB(255, 0, 255));
		break;

	default:
		TransparentBlt(hDC,
			pos.x, pos.y,				//출력될 이미지 시작좌표
			size.width, size.height,	//출력될 이미지크기
			memDc,
			0, 0,						//이미지에서 출력할 시작위치
			size.width, size.height,	//이미지에서 출력할 이미지의 크기
			RGB(255, 0, 255));
		break;
	}
}
