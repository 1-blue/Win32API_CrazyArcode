#pragma once
#include <fstream>
#include "DataStruct.h"

class Obj;
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

private:
	vector<Obj*> characterDataVector;
	vector<Obj*> monsterDataVector;
	vector<Obj*> blockDataVector;	//아이템, 불러올떄, 기본세팅정보들,?? 저장할거
	vector<Obj*> itemDataVector;	
	list<Obj*> objectList;	//실제 게임 플레이 중 생성될 오브젝트 (플레이어, 몬스터, 블록)

private:
	list<HBITMAP> hbmpList;

public:
	ifstream fin;
	vector<string> imageVector;

public:
	void GetImageDataList(list<HBITMAP>* imageDataList);
	void LoadCharacterData();
	void LoadMonsterData();
	void LoadBlockData();
	void LoadItemData();

	Obj* Test();
};