#pragma once
#include "DataStruct.h"

class Obj;
class Character;
class WaterBallon;
class InGameScene
{
private:
	list <Obj*> inGameObjectVector;	//INGAME Scene Data
	list <Character*> characterList;	//캐릭터들저장	//obj를 바꾸기
	list <WaterBallon*> waterBallon;	//물풍선들저장

	//물풍선관련
	pImageData waterBallonData;
	BITMAP waterBallonBitmap;

public:
	void Process(HDC memDCBack, HDC memDC);
	void LoadData(const vector<pImageData>&);

	void LoadBackGroundImage(const vector<pImageData>& inGameData);
	void LoadCharacterData(const pImageData characterImage, CharacterStatsData characterStats);
	void LoadStaticObjectData(const MapData& mapData);
	void LoadWaterBallon(const pImageData waterBallon);
};

