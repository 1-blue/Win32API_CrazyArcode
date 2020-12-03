#pragma once
#include <fstream>
#include <list>
#include <vector>
#include "DataStruct.h"

using namespace std;

class Obj;
class StaticObject;
class ObjectManager
{
private:
	ifstream fin;
	vector<pDefaultData> bitmapVector;

	vector<Obj*> objectVector;		//모든 비트맵 저장
	vector<Obj*> defaultDataVector;	//WaitingUI객체의 포인터를 저장할 벡터

	//vector<Obj*> characterDataVector;	//캐릭터들 저장
	//vector<Obj*> monsterDataVector;	//몬스터들 저장
	//vector<Obj*> blockDataVector;		//블럭들 저장
	//vector<Obj*> itemDataVector;		//아이템들 저장
	//list<Obj*> blockObjectList;		//블록
	//list<Obj*> playerObjectList;		//플레이어

	list<HBITMAP> hbmpList;

public:
	ObjectManager();
	~ObjectManager();
	void Input();
	void Update();
	void Render(HDC hdc, HDC backdc, HDC mdc);

public:
	void LoadDefaultData(const vector<pDefaultData>& bitmapVector);
	void GetImageDataList(list<HBITMAP>* imageDataList);
	void LoadCharacterData();
	void LoadMonsterData();
	void LoadBlockData();
	void LoadItemData();

};