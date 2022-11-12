#pragma once
#include <fstream>
#include "DataStruct.h"

class MapManager
{
private:
	ifstream fin;
	vector<MapData> mapData;

public:
	void LoadTextMapData();	//텍스트파일에서 맵path읽고 mapData에 저장
	const MapData& LoadMap(SelectData selectData);

};

