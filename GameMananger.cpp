#include "GameMananger.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "MapManager.h"
#include "MessageQueue.h"

GameMananger::GameMananger(HWND hWnd)
{
	sceneManager = new SceneManager(hWnd);
	imageManager = new ImageManager();
	mapManager = new MapManager();
}

GameMananger::~GameMananger()
{
	delete sceneManager;
	delete imageManager;
	delete mapManager;
}

void GameMananger::Run()
{
	sceneManager->Process();

	switch (sceneManager->GetSceneState())
	{
	case GameStage::INGAME_LOADING:
		LoadInGameData();
		sceneManager->SetSceneState(GameStage::INGAME);
		sceneManager->InitInGamePlayTime();
		break;
	case GameStage::INGAME_EXITING: 
		sceneManager->InitInGameData();
		sceneManager->SetSceneState(GameStage::LOBBY);
		break;	
	}
}

void GameMananger::LoadLobbyData()
{
	imageManager->LoadImageData();
	sceneManager->LoadLobbyData(imageManager->GetLobbyImageData());
}

void GameMananger::LoadInGameData()
{
	sceneManager->LoadInGameImage(imageManager->GetInGameImage());
	sceneManager->LoadCharacterData(imageManager->GetCharacterImageData(sceneManager->GetSelectData()), imageManager->GetCharacterStatsData(sceneManager->GetSelectData()));
	sceneManager->LoadItemImageData(imageManager->GetItemImageData());
	sceneManager->LoadMapData(mapManager->LoadMap(sceneManager->GetSelectData()));
}

void GameMananger::LoadMapData()
{
	mapManager->LoadTextMapData();
}
