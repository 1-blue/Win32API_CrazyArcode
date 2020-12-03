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
	vector<pImageData> bitmapVector;	//굳이 사용해야하나

	vector<Obj*> defaultDataVector;	//WaitingUI객체의 포인터를 저장할 벡터 (LOBBY object data)
	vector<Obj*> inGameSceneDataVector;	//INGAME Scene Data

	list<HBITMAP> hbmpList;

	int* stage;
public:
	ObjectManager(int *stage);
	~ObjectManager();
	void Input();
	void Update();
	void Render(HDC hdc, HDC backdc, HDC mdc);

public:
	void LoadDefaultData(const vector<pImageData>& bitmapVector);
	void LoadInGameImageData(const vector<pImageData>& bitmapVector);
	void GetImageDataList(list<HBITMAP>* imageDataList);
};