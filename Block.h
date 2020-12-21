#pragma once
#include "StaticObject.h"
#include "DataStruct.h"

class Block : public StaticObject
{
private:
	//맵의 y, x 값 저장
	ObjectData::POSITION mapPos;

public:
	Block(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap);
	~Block();

	virtual void Input();
	virtual void Update();

	const ObjectData::POSITION GetMapPos();
};