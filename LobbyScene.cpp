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
			lobbyObjectVector.emplace_back(new StaticObject(lobby->name,
				{ lobby->x,lobby->y },
				{ bitMap.bmWidth ,bitMap.bmHeight },
				lobby->hBitmap));
		}
		else if (lobby->objType == 1)	//dynamic
		{
			lobbyObjectVector.emplace_back(new DynamicObject(lobby->name,
				{ lobby->x,lobby->y },
				{ bitMap.bmWidth ,bitMap.bmHeight },
				lobby->hNumber, lobby->vNumber,
				lobby->hBitmap));
		}	
		else if (lobby->objType == 2)	//btn
		{
			lobbyObjectVector.emplace_back(new BtnObj(lobby->name,
				{ lobby->x,lobby->y },
				{ bitMap.bmWidth ,bitMap.bmHeight },
				lobby->hNumber, lobby->vNumber,
				lobby->hBitmap));
		}
	}
}

void LobbyScene::Process(HDC memDCBack, HDC memDC)
{
	for (const auto& lobby : lobbyObjectVector)
	{
		lobby->Input();
		lobby->Update();
		lobby->Render(memDCBack, memDC);
	}

	EventProcess(MessageQueue::RunEventQueue());

	this->SaveSelectData();		//현재 선택한 캐릭터과 맵정보 저장
}

void LobbyScene::EventProcess(list<ClickEvent> eventList)
{
	if (eventList.size() <= 0)
		return;

	for (auto iter : eventList)
	{
		if (iter.name == "exit")
			exit(0);
		if ((iter.name == "bazziPickImage" || iter.name == "dizniPickImage") && iter.isRight == false)
		{
			int x = 10;
			//redCharacter
			//blueCharacter
		}
		if ((iter.name == "bazziPickImage" || iter.name == "dizniPickImage") && iter.isRight == true)
		{
			//redCharacter
			//blueCharacter
		}

	}
}

void LobbyScene::SaveSelectData()
{

}

const SelectData& LobbyScene::GetSelectData() const
{
	return selectData;
}
