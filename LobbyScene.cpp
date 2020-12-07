#include "LobbyScene.h"
#include "Lobby.h"

void LobbyScene::LoadData(const vector<pImageData>& lobbyData)
{
	BITMAP bitMap;

	for (const auto& lobby : lobbyData)
	{
		GetObject(lobby->hBitmap, sizeof(BITMAP), &bitMap);

		lobbyObjectVector.emplace_back(new Lobby(lobby->name,
			{ lobby->x,lobby->y },
			{ bitMap.bmWidth ,bitMap.bmHeight },
			lobby->hNumber, lobby->vNumber,
			lobby->hBitmap));
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

	this->SaveSelectData();		//현재 선택한 캐릭터과 맵정보 저장
}

void LobbyScene::SaveSelectData()
{
	selectData.redCharacterNumber = Lobby::redImageNumber;
	selectData.blueCharacterNumber = Lobby::blueImageNumber;
	selectData.mapNumber = Lobby::mapImageNumber;
}

const SelectData& LobbyScene::GetSelectData() const
{
	return selectData;
}
