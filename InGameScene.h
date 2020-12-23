#pragma once
#include "DataStruct.h"
#include "BtnObj.h"
#include "MessageQueue.h"
#include <ctime>

class Obj;
class Character;
class WaterBallon;
class Block;
class Item;		//이거체크하고 삭제
class InGameScene
{
private:
	list <Obj*> allInGameScene;			//모든 INGAME Scene이 들어갈 리스트	<- allInGameObject로 이름바꾸기
	list <Obj*> inGameObjectList;		//INGAME Scene Data
	list <Character*> characterList;	//캐릭터들저장	//obj를 바꾸기
	list <WaterBallon*> waterBallon;	//물풍선들저장

	MapData mapData;	//맵정보
	ULONGLONG inGamePlayTime;	//게임 시작 시간
	ULONGLONG endGameTime;	//게임 종료 시간

	vector<pImageData> objectsData;		//블럭, 벽, 물풍선 데이터 저장
	vector<BITMAP> objectsBitmap;		//블럭, 벽, 물풍선 비트맵 저장
	pImageData itemData;				//아이템 데이터 저장
	BITMAP itemBitmap;					//아이템 비트맵 저장

	list<ObjectData::Position> waterBallonPos;			//물풍선 포지션.. 캐릭터한테 전달함
	static ObjectData::POSITION removeWaterBallonPos;	//삭제한물풍선좌표 전체 업데이트해주는데 사용
	list<ItemData> itemPos;								//아이템 포지션.. 캐릭터한테 전달함
	static ObjectData::POSITION removeItemPos;			//삭제한아이템좌표 전체 업데이트해주는데 사용

	bool isEndGame{ false };

public:
	void Init();
	~InGameScene();
	void Process(HDC memDCBack, HDC memDC);
	void LoadData(const vector<pImageData>&);

	void InitInGamePlayTime();

	list <Obj*>& GetInGameObjList();

	void GetMapData(MapData mapData);
	void LoadInGameImage(const vector<pImageData>& inGameImage);
	void LoadCharacterData(const pImageData characterImage, const pImageData trappedImage, const pImageData dieImage, CharacterStatsData characterStats);
	void LoadItemImage(const pImageData itemImage);
	void LoadStaticObjectData();

private:
	void DeleteHitObject(vector<ObjectData::POSITION> hitObjectPos);

	void CreateWaterBallon(Character* character);
	void DeleteWaterBallons();
	void CheckCharacterItem();
	void CheckWaterBallonItem(const AttackArea& attackArea);

	static bool SortObject(Obj* obj1, Obj* obj2);			//출력순서정렬을 위한 정렬함수
	static bool RemoveWaterBallonData(Obj* tempWaterBallon);					//모든 물풍선사용하는 자료구조들 초기화해주기위해 사용
	static bool RemoveWaterBallonData1(ObjectData::POSITION tempWaterBallon);	//함수 오버로딩이 안되가지고 두개만듦
	void GameOver(const int playerColor);
	static bool RemoveItemData(Obj* itemPosition);
	static bool RemoveItemData1(ItemData itemPosition);
};

