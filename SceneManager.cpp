#include "SceneManager.h"
#include "Character.h"
#include "InGameScene.h"
#include "LobbyScene.h"
#include "ImageManager.h"

SceneManager::SceneManager(HWND hWnd)
{
	this->hWnd = hWnd;
	this->hdc = GetDC(hWnd);
	memDC = CreateCompatibleDC(hdc);
	memDCBack = CreateCompatibleDC(hdc);
	lobbyScene = new LobbyScene();
	inGameScene = new InGameScene();
}

SceneManager::~SceneManager()
{
	DeleteDC(memDC);
	DeleteDC(memDCBack);
	ReleaseDC(hWnd, hdc);

	delete lobbyScene;
	delete inGameScene;
}

void SceneManager::Process(const int& stage)
{
	if (oldHBitMap != NULL)
	{
		DeleteObject(oldHBitMap);
		oldHBitMap = NULL;
	}

	oldHBitMap = (HBITMAP)SelectObject(memDCBack, CreateCompatibleBitmap(hdc, WND_WIDTH, WND_HEIGHT));

	if (stage == GameStage::LOBBY)
	{
		lobbyScene->Process(memDCBack, memDC);
		selectData = lobbyScene->GetSelectData();
	}
	else if (stage == GameStage::INGAME_LOADING)
	{
		//캐릭터생성, 맵생성, 물풍선, 아이템, 등등생성하고 stage값 변경
		//이거를 SceneManager함수를 통해서 GameManager에서 하고있음
	}
	else if (stage == GameStage::INGAME)
		inGameScene->Process(memDCBack, memDC);

	BitBlt(hdc, 0, 0, WND_WIDTH, WND_HEIGHT, memDCBack, 0, 0, SRCCOPY);		
}

void SceneManager::LoadLobbyData(const vector<pImageData>& lobbyData)
{
	lobbyScene->LoadData(lobbyData);
}

const SelectData& SceneManager::GetSelectData()
{
	return selectData;
}

void SceneManager::LoadInGameBackGroundImage(const vector<pImageData>& inGameBackGround)
{
	inGameScene->LoadBackGroundImage(inGameBackGround);
}

void SceneManager::LoadCharacterData(const pImageData* characterImage, const CharacterStatsData* characterStats)
{
	for (int i = 0; i < 2; i++)
		inGameScene->LoadCharacterData(characterImage[i], characterStats[i]);
}

void SceneManager::LoadMapData(const MapData& mapData)
{
	inGameScene->LoadStaticObjectData(mapData);
}

void SceneManager::LoadWaterBallonData(const pImageData waterBallon)
{
	inGameScene->LoadWaterBallon(waterBallon);
}
