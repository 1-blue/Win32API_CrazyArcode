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
		DeleteObject(oldHBitMap);

	oldHBitMap = (HBITMAP)SelectObject(memDCBack, CreateCompatibleBitmap(hdc, WND_WIDTH, WND_HEIGHT));

	DeleteObject(oldHBitMap);

	if (stage == GameStage::LOBBY)
		lobbyScene->Process(memDCBack, memDC);
	else if (stage == GameStage::INGAME)
		inGameScene->Process(memDCBack, memDC);

	BitBlt(hdc, 0, 0, WND_WIDTH, WND_HEIGHT, memDCBack, 0, 0, SRCCOPY);

	//임시추가
	if (stage == GameStage::INGAME && isFirst)
	{
		selectData = lobbyScene->GetSelectData();
		isFirst = false;
	}
}

void SceneManager::LoadLobbyData(const vector<pImageData>& lobbyData)
{
	lobbyScene->LoadData(lobbyData);
}

const SelectData& SceneManager::GetSelectData()
{
	return selectData;
}

void SceneManager::LoadInGameBackGroundImage(const vector<pImageData>& inGameData)
{
	inGameScene->LoadBackGroundImage(inGameData);
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
