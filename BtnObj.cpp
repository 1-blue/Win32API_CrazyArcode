#include "BtnObj.h"
#include "MessageQueue.h"
#include "SoundManager.h"

extern HWND hWnd;

BtnObj::BtnObj()
{
}
BtnObj::BtnObj(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap)
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

		if (!playingSound)
		{
			SoundManager::GetInstance()->PlayEffectSound(2);
			playingSound = true;
		}
	}
	else //화면 밖으로 나가면 원상복구
	{
		isOverlap = false;
		playingSound = false;
		state = ClickedState::DEFAULT;
	}

	if (!isOverlap)
		return;

	if (GetAsyncKeyState(MK_LBUTTON) & 0x8000)
		state = ClickedState::LMOUSEDOWN;
	else if (GetAsyncKeyState(MK_RBUTTON) & 0x8000)
		state = ClickedState::RMOUSEDOWN;

	if (ClickedState::LMOUSEDOWN == state)
	{
		if (!(GetAsyncKeyState(MK_LBUTTON) & 0x8000))
		{
			MessageQueue::AddEventQueue({ name,false });
			state = ClickedState::DEFAULT;
		}
	}
	else if (ClickedState::RMOUSEDOWN == state)
	{
		if (!(GetAsyncKeyState(MK_RBUTTON) & 0x8000))
		{
			MessageQueue::AddEventQueue({ name,true });
			state = ClickedState::DEFAULT;
		}
	}
}

void BtnObj::Update()
{
	if (!isOverlap)
		imageNumber = 0;
	else
		imageNumber = 1;
}
