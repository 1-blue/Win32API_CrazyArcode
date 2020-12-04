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
	vector<Obj*> inGameSceneDataVector;	//INGAME Scene Data
	vector<Obj*> CharacterDataVector;	//CHARACTER Data
	int* stage;

public:

public:
	ObjectManager(int *stage);
	~ObjectManager();
	void Input();
	void Update();
	void Render(HDC hdc, HDC backdc, HDC mdc);

public:
	void LoadInGameImageData(const vector<pImageData>& bitmapVector);
	void LoadRedCharacterImageData(pImageData characterImage);
	void LoadBlueCharacterImageData(pImageData characterImage);
	void LoadRedCharacterStatsData(CharacterStatsData characterStats);
	void LoadBlueCharacterStatsData(CharacterStatsData characterStats);

};