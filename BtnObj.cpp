#include "BtnObj.h"
#include "MessageQueue.h"

extern HWND hWnd;

BtnObj::BtnObj()
{
}
BtnObj::BtnObj(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap)
	:DynamicObject(name,pos,size,hNumber,vNumber,hBitmap)
{
}
BtnObj::~BtnObj()
{
}
void BtnObj::Input()
{
	if ((hNumber * vNumber) <= 1)	//이미지수가 2개이상일때 (이미지 변화할 애들만 변화시키위해)
		return;

	GET_CURSOR_POSITION(cursorPos);

	//커서가 이미지위로올라오면 이미지변화
	if ((cursorPos.x >= pos.x && cursorPos.x <= pos.x + size.width / hNumber)
		&& (cursorPos.y >= pos.y && cursorPos.y <= pos.y + size.height / vNumber))
	{
		isOverlap = true;
		//버튼클릭하면
		if ((GetAsyncKeyState(MK_LBUTTON)) & (0x8000) && (isClicked == false))	//0x8000없으면 클릭하고 마우스올려도 이미지 변화됨
		{
			MessageQueue::AddEventQueue({name,false});
		}
		else if ((GetAsyncKeyState(MK_RBUTTON)) & (0x8000) && (isClicked == false))	//mouseUp
		{
			MessageQueue::AddEventQueue({name,true});
		}
		
	}
	else //화면 밖으로 나가면 원상복구
	{
		isOverlap = false;
		isClicked = false;
	}
}

void BtnObj::Update()
{
	if (isOverlap == false)
	{
		imageNumber = 0;
	}
	else if (isOverlap == true)
	{
		imageNumber = 1;
	}
	else if (isClicked == true)
	{
		//클릭 이미지 바꾸기
	}
}

