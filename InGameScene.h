#pragma once
#include "DataStruct.h"
#include "BtnObj.h"
#include "MessageQueue.h"

class Obj;
class Character;
class WaterBallon;
class InGameScene
{
private:
	list <Obj*> allInGameScene;			//모든 INGAME Scene이 들어갈 리스트
	list <Obj*> inGameObjectList;		//INGAME Scene Data
	list <Character*> characterList;	//캐릭터들저장	//obj를 바꾸기
	list <WaterBallon*> waterBallon;	//물풍선들저장
	bool isDeleteWaterBallon{ false };

	vector<pImageData> objectsData;		//블럭, 벽, 물풍선 데이터 저장
	vector<BITMAP> objectsBitmap;		//블럭, 벽, 물풍선 비트맵 저장

	list<ObjectData::Position> waterBallonPos;			//물풍선 포지션.. 캐릭터한테 전달함
	static ObjectData::POSITION removeWaterBallonPos;	//삭제한물풍선좌표 전체 업데이트해주는데 사용

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
	static bool SortObject(Obj* obj1, Obj* obj2);	//출력순서정렬을 위한
	static bool RemoveWaterBallonData(Obj* tempWaterBallon);					//모든 물풍선사용하는 자료구조들 초기화해주기위해 사용
	static bool RemoveWaterBallonData1(ObjectData::POSITION tempWaterBallon);	//함수 오버로딩이 안되가지고 두개만듦
};

