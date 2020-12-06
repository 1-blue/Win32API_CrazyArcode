#pragma once
#include "DataStruct.h"

class Obj;
class LobbyScene2
{
private:
	int mapNumber{ 0 };	//이걸로 게임 시작 시 게임 맵 데이터 , 그 외 데이터 불러올 떄 쓸거임
	//색, 플레이어 수, 캐릭터 정보 등등 추가하고 싶지만 이 게임에서 필요로 하지 않으니 안쓸거

	vector<Obj*> lobbyObjectVector;	//INGAME Scene Data
public:
	void LoadData();

	void Process();
};