#include "LobbyScene.h"
#include "StaticObject.h"
#include "BtnObj.h"
#include "MessageQueue.h"

void LobbyScene::LoadData(const vector<pImageData>& lobbyData)
{
	BITMAP bitMap;

	for (const auto& lobby : lobbyData)
	{
		GetObject(lobby->hBitmap, sizeof(BITMAP), &bitMap);

		if (lobby->objType == 0)	//static
		{
			lobbyObjectList.emplace_back(new StaticObject(lobby->name,
				{ lobby->x,lobby->y },
				{ bitMap.bmWidth ,bitMap.bmHeight },
				lobby->hBitmap));
		}
		else if (lobby->objType == 1)	//dynamic
		{
			lobbyObjectList.emplace_back(new DynamicObject(lobby->name,
				{ lobby->x,lobby->y },
				{ bitMap.bmWidth ,bitMap.bmHeight },
				lobby->hNumber, lobby->vNumber,
				lobby->hBitmap));
		}	
		else if (lobby->objType == 2)	//btn
		{
			lobbyObjectList.emplace_back(new BtnObj(lobby->name,
				{ lobby->x,lobby->y },
				{ bitMap.bmWidth ,bitMap.bmHeight },
				lobby->hNumber, lobby->vNumber,
				lobby->hBitmap));
		}
	}
}

void LobbyScene::Process(HDC memDCBack, HDC memDC)
{
	for (const auto& lobby : lobbyObjectList)
	{
		lobby->Input();
		lobby->Update();
		lobby->Render(memDCBack, memDC);
	}
	MessageQueue::RunEventQueue(lobbyObjectList);

	if(MessageQueue::selectData.isStart)
		this->SaveSelectData();		//현재 선택한 캐릭터과 맵정보 저장
}

void LobbyScene::SaveSelectData()
{
	selectData = MessageQueue::selectData;
}

const SelectData& LobbyScene::GetSelectData() const
{
	return selectData;
}
