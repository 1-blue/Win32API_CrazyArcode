#include "LobbyScene.h"

extern HWND hWnd;		//이거 마우스위치알아낼때 필요해서 임시로사용
int LobbyScene::redImageNumber = 0;
int LobbyScene::blueImageNumber = 0;
int LobbyScene::mapImageNumber = 0;
bool LobbyScene::isStart = false;

LobbyScene::LobbyScene(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap)
{
	this->name = name;
	this->pos = pos;
	this->size = size;
	this->hNumber = hNumber;
	this->vNumber = vNumber;
	this->hBitmap = hBitmap;
	this->imageWidth = size.width / hNumber;
	this->imageHeight = size.height / vNumber;
}

LobbyScene::~LobbyScene()
{

}

void LobbyScene::Input()
{
	if ((hNumber * vNumber) <= 1)	//이미지수가 2개이상일때 (이미지 변화할 애들만 변화시키위해)
		return;

	GET_CURSOR_POSITION(cursorPos);

	//커서가 이미지위로올라오면 이미지변화
	if ((cursorPos.x >= pos.x && cursorPos.x <= pos.x + size.width)
		&& (cursorPos.y >= pos.y && cursorPos.y <= pos.y + size.height / vNumber))
	{
		imageNumber = 1;

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
		imageNumber = 0;
	}
}

void LobbyScene::Update()
{
	if ("redCharacter" == name)
		imageNumber = redImageNumber;
	if ("blueCharacter" == name)
		imageNumber = blueImageNumber;
	if ("map" == name)
		imageNumber = mapImageNumber;
}

void LobbyScene::Render(HDC hDC, HDC memDc)
{
	SelectObject(memDc, hBitmap);

	if (hNumber >= 2)
	{
		TransparentBlt(hDC,
			pos.x, pos.y,						//출력될 이미지 시작좌표
			imageWidth, imageHeight,			//출력될 이미지크기
			memDc,
			imageNumber * imageWidth, 0,	//이미지에서 출력할 시작위치
			imageWidth, imageHeight,			//이미지에서 출력할 이미지의 크기
			RGB(255, 0, 255));
	}
	else if (vNumber >= 2)
	{
		TransparentBlt(hDC,
			pos.x, pos.y,							//출력될 이미지 시작좌표
			imageWidth, imageHeight,				//출력될 이미지크기
			memDc,
			0, imageNumber * imageHeight,		//이미지에서 출력할 시작위치
			imageWidth, imageHeight,				//이미지에서 출력할 이미지의 크기
			RGB(255, 0, 255));
	}
	else
	{
		TransparentBlt(hDC,
			pos.x, pos.y,					//출력될 이미지 시작좌표
			imageWidth, imageHeight,		//출력될 이미지크기
			memDc,
			0, 0,							//이미지에서 출력할 시작위치
			imageWidth, imageHeight,		//이미지에서 출력할 이미지의 크기
			RGB(255, 0, 255));
	}
}

bool LobbyScene::IsStart()
{
	return isStart;
}
