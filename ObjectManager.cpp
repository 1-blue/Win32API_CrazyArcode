#include "ObjectManager.h"
#include "Obj.h"
#include "Character.h"
#include "LobbyUI.h"
#include "StaticObject.h"

ObjectManager::ObjectManager(int *stage)
{
	this->stage = stage;
}

ObjectManager::~ObjectManager()
{
	for (auto objs : LobbyDataVector)
		delete objs;
	LobbyDataVector.clear();
}

void ObjectManager::Input()
{
	if (*stage == GameStage::LOBBY)
	{
		for (const auto& lobby : LobbyDataVector)
			lobby->Input();
	}
	else if (*stage == GameStage::INGAME)
	{
		for (auto it = inGameSceneDataVector.begin(); it != inGameSceneDataVector.end(); it++)
			(*it)->Input();
	}
}

void ObjectManager::Update()
{
	if (*stage == GameStage::LOBBY)
	{
		for (const auto& lobby : LobbyDataVector)
			lobby->Update();
	}
	else if (*stage == GameStage::INGAME)
	{
		for (auto it = inGameSceneDataVector.begin(); it != inGameSceneDataVector.end(); it++)
			(*it)->Update();
	}
}

void ObjectManager::Render(HDC hdc, HDC memDCBack, HDC memDC)
{
	if (*stage == GameStage::LOBBY)
	{
		for (const auto& lobby : LobbyDataVector)
			lobby->Render(memDCBack, memDC);

		//여기넣을건 아닌것같긴한데 일단넣음
		//시작버튼누르면 시작
		if (LobbyUI::IsStart())
		{
			*stage = GameStage::INGAME;
			selectData.redCharacterNumber = LobbyUI::redImageNumber;
			selectData.blueCharacterNumber = LobbyUI::blueImageNumber;
			selectData.mapNumber = LobbyUI::mapImageNumber;
		}

	}
	else if (*stage == GameStage::INGAME)
	{
		for (auto it = inGameSceneDataVector.begin(); it != inGameSceneDataVector.end(); it++)
			(*it)->Render(memDCBack, memDC);
	}
}

void ObjectManager::LoadLobbyData(const vector<pImageData2>& lobbyDataVector)
{
	BITMAP bitMap;

	for (const auto iterator : lobbyDataVector)
	{
		GetObject(iterator->hBitmap, sizeof(BITMAP), &bitMap);

		LobbyDataVector.emplace_back(new LobbyUI(iterator->name,
			{ iterator->x,iterator->y },
			{ bitMap.bmWidth ,bitMap.bmHeight },
			iterator->hNumber, iterator->vNumber,
			bitMap.bmWidth / iterator->vNumber, bitMap.bmHeight / iterator->hNumber,
			iterator->hBitmap));
	}
}

void ObjectManager::LoadInGameImageData(const vector<pImageData>& bitmapVector)
{
	BITMAP bitMap;

	for (const auto iterator : bitmapVector)
	{
		GetObject(iterator->hBitmap, sizeof(BITMAP), &bitMap);
		if (iterator->objType == 0)
			inGameSceneDataVector.emplace_back(new StaticObject(iterator->name, { iterator->x,iterator->y }, { bitMap.bmWidth ,bitMap.bmHeight }, iterator->hBitmap));
		//else 
		//	inGameSceneDataVector.emplace_back(new DynamicObject(iterator->name, { iterator->x,iterator->y }, { bitMap.bmWidth ,bitMap.bmHeight }, iterator->kinds, iterator->number, iterator->interval, iterator->hBitmap));
	}
}

void ObjectManager::GetImageDataList(list<HBITMAP>* imageDataList)
{
	hbmpList = *imageDataList;
}
