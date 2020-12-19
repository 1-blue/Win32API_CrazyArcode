#pragma once
#include "StaticObject.h"
#include "DataStruct.h"

class Wall : public StaticObject
{
private:


public:
	Wall(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap);
	~Wall();

	virtual void Input();
	virtual void Update();
};