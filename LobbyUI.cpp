#include "LobbyUI.h"

extern HWND hWnd;		//이거 마우스위치알아낼때 필요해서 임시로사용
int LobbyUI::redImageNumber = 0;
int LobbyUI::blueImageNumber = 0;
int LobbyUI::mapImageNumber = 0;
bool LobbyUI::isStart = false;

LobbyUI::LobbyUI(ImageData2 test) : DynamicObject(test)
{

}

LobbyUI::~LobbyUI()
{
	DynamicObject::~DynamicObject();
}

void LobbyUI::Input()
{
	if (imageNumber <= 1)	//이미지수가 2개이상일때 (이미지 변화할 애들만 변화시키위해)
		return;

	GET_CURSOR_POSITION(cursorPos);

	//커서가 이미지위로올라오면 이미지변화.. 여기도 원래는 switch~case사용해서 구별해야함
	if ((cursorPos.x >= pos.x && cursorPos.x <= pos.x + size.width)
		&& (cursorPos.y >= pos.y && cursorPos.y <= pos.y + size.height / imageNumber))
	{
		printImageNumber = 1;

		//버튼클릭하면
		if (GetAsyncKeyState(MK_LBUTTON) & 0x8000)	//0x8000없으면 클릭하고 마우스올려도 이미지 변화됨
		{
			if ("bazziPickImage" == name)
				redImageNumber = CharacterSelect::BAZZI;
			if ("dizniPickImage" == name)
				redImageNumber = CharacterSelect::DIZNI;
			if ("RandomPickImage" == name)
				redImageNumber = CharacterSelect::RANDOM;
			if ("mapPick" == name)
				++mapImageNumber > 1 ? mapImageNumber = 0 : 0;

			if ("start" == name)
			{
				isStart = true;
			}
		}
		if (GetAsyncKeyState(MK_RBUTTON) & 0x8000)
		{
			if ("bazziPickImage" == name)
				blueImageNumber = CharacterSelect::BAZZI;
			if ("dizniPickImage" == name)
				blueImageNumber = CharacterSelect::DIZNI;
			if ("RandomPickImage" == name)
				blueImageNumber = CharacterSelect::RANDOM;
		}
	}
	else
	{
		printImageNumber = 0;
	}
}

void LobbyUI::Update()
{
	if ("redCharacter" == name)
		printImageNumber = redImageNumber;
	if ("blueCharacter" == name)
		printImageNumber = blueImageNumber;
	if ("map" == name)
		printImageNumber = mapImageNumber;
}

void LobbyUI::Render(HDC hDC, HDC memDc)
{
	SelectObject(memDc, hBitmap);

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

bool LobbyUI::IsStart()
{
	return isStart;
}
