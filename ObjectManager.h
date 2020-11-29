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

public:
	void Render(HDC hdc, HDC backdc, HDC mdc);
	
public:
	ObjectManager();
	~ObjectManager();

private:

	//vector<Obj*> characterDataVector;	//캐릭터들 저장
	//vector<Obj*> monsterDataVector;		//몬스터들 저장
	//vector<Obj*> blockDataVector;		//블럭들 저장
	//vector<Obj*> itemDataVector;		//아이템들 저장
	vector<Obj*> objectVector;	//모든 비트맵 저장

	list<Obj*> blockObjectList;		//블록
	list<Obj*> playerObjectList;	//플레이어
private:
	list<HBITMAP> hbmpList;

public:
	ifstream fin;
	vector<string> imagePathVector;
	vector<pDefaultBitmap> bitmapVector;

public:
	void GetImageDataList(list<HBITMAP>* imageDataList);
	void LoadCharacterData();
	void LoadMonsterData();
	void LoadBlockData();
	void LoadItemData();

	void LoadDefaultData(const vector<pDefaultBitmap>& bitmapVector);
};