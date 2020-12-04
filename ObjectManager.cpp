#include "ObjectManager.h"
#include "Obj.h"
#include "Character.h"
#include "LobbyUI.h"
#include "StaticObject.h"

SelectData ObjectManager::selectData{ 0, 0, 0 };

ObjectManager::ObjectManager(int *stage)
{
	this->stage = stage;
}

ObjectManager::~ObjectManager()
{
	for (auto objs : LobbyDataVector)
		delete objs;
	LobbyDataVector.clear();

	for (auto objs : inGameSceneDataVector)
		delete objs;
	inGameSceneDataVector.clear();

	for (auto objs : CharacterDataVector)
		delete objs;
	CharacterDataVector.clear();
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

		for (const auto& character : CharacterDataVector)
			character->Input();
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

		for (const auto& character : CharacterDataVector)
			character->Update();
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
		if (LobbyUI::IsStart())	//게임매니저로 옮기자, lobbyUI도 굳이 dynamic object를 상속해서 만들 필요가 없다고 생각함,
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

		for (const auto& character : CharacterDataVector)
			character->Render(memDCBack, memDC);
	}
}

void ObjectManager::LoadLobbyData(const vector<pImageData>& lobbyDataVector)
{
	BITMAP bitMap;

	for (const auto iterator : lobbyDataVector)
	{
		GetObject(iterator->hBitmap, sizeof(BITMAP), &bitMap);

		LobbyDataVector.emplace_back(new LobbyUI(iterator->name,
			{ iterator->x,iterator->y },
			{ bitMap.bmWidth ,bitMap.bmHeight },
			iterator->hNumber, iterator->vNumber,
			iterator->hBitmap));
	}
}

void ObjectManager::LoadInGameImageData(const vector<pImageData>& bitmapVector)
{
	BITMAP bitMap;

	for (const auto iterator : bitmapVector)
	{
		GetObject(iterator->hBitmap, sizeof(BITMAP), &bitMap);
		if (iterator->objType == 0)	//static
			inGameSceneDataVector.emplace_back(new StaticObject(iterator->name, { iterator->x,iterator->y }, { bitMap.bmWidth ,bitMap.bmHeight }, iterator->hBitmap));
		else						//dynamic
			inGameSceneDataVector.emplace_back(new DynamicObject(iterator->name, { iterator->x,iterator->y }, { bitMap.bmWidth ,bitMap.bmHeight },  iterator->hNumber, iterator->vNumber, iterator->hBitmap));
	}
}

void ObjectManager::LoadRedCharacterImageData(pImageData characterImage)
{
	BITMAP bitMap;
	GetObject(characterImage->hBitmap, sizeof(BITMAP), &bitMap);

	CharacterDataVector.emplace_back(new Character(characterImage->name,
		{ characterImage->x,characterImage->y },
		{ bitMap.bmWidth ,bitMap.bmHeight },
		characterImage->hNumber, characterImage->vNumber,
		bitMap.bmWidth / characterImage->vNumber, bitMap.bmHeight / characterImage->hNumber,
		characterImage->hBitmap));
}

void ObjectManager::LoadBlueCharacterImageData(pImageData characterImage)
{
	BITMAP bitMap;
	GetObject(characterImage->hBitmap, sizeof(BITMAP), &bitMap);

	CharacterDataVector.emplace_back( new Character(characterImage->name,
		{ characterImage->x,characterImage->y },
		{ bitMap.bmWidth ,bitMap.bmHeight },
		characterImage->hNumber, characterImage->vNumber,
		bitMap.bmWidth / characterImage->vNumber, bitMap.bmHeight / characterImage->hNumber,
		characterImage->hBitmap));
}