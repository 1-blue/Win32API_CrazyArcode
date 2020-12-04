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

	vector<Obj*> LobbyDataVector;		//WaitingUI객체의 포인터를 저장할 벡터 (LOBBY object data)
	vector<Obj*> inGameSceneDataVector;	//INGAME Scene Data
	vector<Obj*> CharacterDataVector;	//CHARACTER Data

	int* stage;
public:
	static SelectData selectData;		//요거에 선택한 캐릭터들, 맵번호 넣었음.. 이걸로 게임시작할때 캐릭터불러오는데 사용하면됨

public:
	ObjectManager(int *stage);
	~ObjectManager();
	void Input();
	void Update();
	void Render(HDC hdc, HDC backdc, HDC mdc);

public:
	void LoadLobbyData(const vector<pImageData>& lobbyDataVector);
	void LoadInGameImageData(const vector<pImageData>& bitmapVector);
	void LoadRedCharacterImageData(pImageData characterImage);
	void LoadBlueCharacterImageData(pImageData characterImage);
};