#include "GameMananger.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "MapManager.h"
#include "MessageQueue.h"
#include "SoundManager.h"

GameMananger::GameMananger(HWND hWnd)
{
	sceneManager = new SceneManager(hWnd);
	imageManager = new ImageManager();
	mapManager = new MapManager();
	soundManager = SoundManager::GetInstance();

	//soundManager->PlaySoundTrack(BGM::ROOM);
}

GameMananger::~GameMananger()
{
	delete sceneManager;
	delete imageManager;
	delete mapManager;
	SoundManager::ReleaseInstance();
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
		//soundManager->PlaySoundTrack(BGM::PATRIT);
		break;
	case GameStage::INGAME_EXITING: 
		sceneManager->InitInGameData();
		sceneManager->SetSceneState(GameStage::LOBBY);
		//soundManager->PlaySoundTrack(BGM::ROOM);
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
