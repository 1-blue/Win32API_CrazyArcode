#pragma once
#include "DataStruct.h"

class Obj;
class InGameScene
{
private:
	vector<Obj*> inGameObjectVector;	//INGAME Scene Data

public:
	void Process(HDC memDCBack, HDC memDC);
	void LoadData(const vector<pImageData>&);

	void LoadBackGroundImage(const vector<pImageData>& inGameData);
	void LoadBackCharacterData(const pImageData characterImage, CharacterStatsData characterStats);
	void LoadStaticObjectData(const MapData& mapData);
};

