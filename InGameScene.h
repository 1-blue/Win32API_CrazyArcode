#pragma once
#include "DataStruct.h"

class Obj;
class InGameScene
{
private:
	vector<Obj*> inGameObjectVector;	//INGAME Scene Data
public:

	void LoadData();

	void Process();
};

