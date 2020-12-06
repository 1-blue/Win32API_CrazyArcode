#include "SceneManager.h"
#include "Obj.h"
#include "Character.h"
#include "StaticObject.h"
#include "InGameScene.h"

#include "LobbyScene2.h"
//gameManager의 imageManager를 scene매니저에서 사용한다 -> 게임 시작 시 데이터 불러올 떄 사용하려고
#include "ImageManager.h"

//추가
#include "Blank.h"
#include "Block.h"
#include "Wall.h"

SceneManager::SceneManager(HWND hWnd)
{
	this->hWnd = hWnd;
	this->hdc = GetDC(hWnd);
	memDC = CreateCompatibleDC(hdc);
	memDCBack = CreateCompatibleDC(hdc);
	lobbyScene = new LobbyScene2();
	inGameScene = new InGameScene();
}

SceneManager::~SceneManager()
{
	DeleteDC(memDC);
	DeleteDC(memDCBack);
	ReleaseDC(hWnd, hdc);

	delete lobbyScene;
	delete inGameScene;




	//이것도 없애야할것들
	for (auto objs : inGameSceneDataVector)
		delete objs;
	inGameSceneDataVector.clear();

	for (auto objs : CharacterDataVector)
		delete objs;
	CharacterDataVector.clear();
}

void SceneManager::Process(const int& stage)
{
	if (stage == GameStage::LOBBY)
	{
		lobbyScene->Process();
	}
	else if (stage == GameStage::INGAME)
	{
		inGameScene->Process();
	}
}

void SceneManager::LoadLobbyImageData()
{
}

//밑에꺼 버려
void SceneManager::Input()
{
	for (auto it = inGameSceneDataVector.begin(); it != inGameSceneDataVector.end(); it++)
		(*it)->Input();

	for (const auto& character : CharacterDataVector)
		character->Input();
}

void SceneManager::Update()
{
	for (auto it = inGameSceneDataVector.begin(); it != inGameSceneDataVector.end(); it++)
		(*it)->Update();

	for (const auto& character : CharacterDataVector)
		character->Update();
}

void SceneManager::Render(HDC hdc, HDC memDCBack, HDC memDC)
{
	for (auto it = inGameSceneDataVector.begin(); it != inGameSceneDataVector.end(); it++)
		(*it)->Render(memDCBack, memDC);

	for (const auto& character : CharacterDataVector)
		character->Render(memDCBack, memDC);
}

void SceneManager::LoadInGameImageData(const vector<pImageData>& bitmapVector)
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

void SceneManager::LoadRedCharacterImageData(pImageData characterImage)
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

void SceneManager::LoadBlueCharacterImageData(pImageData characterImage)
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

//밑에 두개 하나로 합치고 매개변수로 구분해서 사용하도록 만들자
void SceneManager::LoadRedCharacterStatsData(CharacterStatsData characterStats)
{
	dynamic_cast<Character*>(CharacterDataVector[0])->SetStats(characterStats);
}

void SceneManager::LoadBlueCharacterStatsData(CharacterStatsData characterStats)
{
	dynamic_cast<Character*>(CharacterDataVector[1])->SetStats(characterStats);
}

//밑에 것들 inGameScene 안에서 처리하도록 만들자
void SceneManager::LoadStaticObjectData(const MapData& mapData)
{
	//나중에 생성자로 각종 정보들 넘겨주기

	for (int h = 0; h < 13; h++)		//일단 맵세로길이
	{
		for (int w = 0; w < 15; w++)	//맵가로길이
		{
			switch (mapData.data[h][w])
			{
			case Objects::BLANK:
				//공백생성
				mapObjectVector.emplace_back(new Blank());
				break;
			case Objects::BLOCK:
				//블록생성
				mapObjectVector.emplace_back(new Block());
				break;
			case Objects::WALL:
				//벽생성
				mapObjectVector.emplace_back(new Wall());
				break;
			}
		}
	}
	int x = 10;
}
