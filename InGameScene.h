﻿#pragma once
#include "DataStruct.h"
#include "BtnObj.h"
#include "MessageQueue.h"

class Obj;
class Character;
class WaterBallon;
class InGameScene
{
private:
	list <Obj*> inGameObjectList;		//INGAME Scene Data
	list <Character*> characterList;	//캐릭터들저장	//obj를 바꾸기
	list <WaterBallon*> waterBallon;	//물풍선들저장
	bool isDeleteWaterBallon{ false };

	vector<pImageData> objectsData;		//블럭, 벽, 물풍선 데이터 저장
	vector<BITMAP> objectsBitmap;		//블럭, 벽, 물풍선 비트맵 저장

	vector<ObjectData::Position> waterBallonPos;

public:
	void Init();
	~InGameScene();
	void Process(HDC memDCBack, HDC memDC);
	void LoadData(const vector<pImageData>&);

	list <Obj*>& GetInGameObjList();

	void LoadInGameImage(const vector<pImageData>& inGameBackGround);
	void LoadCharacterData(const pImageData characterImage, CharacterStatsData characterStats);
	void LoadStaticObjectData(const MapData& mapData);

private:
	void CreateWaterBallon(Character* character);
	void DeleteWaterBallons();
};

