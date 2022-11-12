#pragma once
#include "StaticObject.h"
#include "DataStruct.h"

class Block : public StaticObject
{
private:

public:
	Block(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap);
	~Block();

	virtual void Input();
	virtual void Update();
};