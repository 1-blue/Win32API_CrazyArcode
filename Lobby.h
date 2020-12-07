#pragma once
#include "DataStruct.h"
#include "DynamicObject.h"

class Lobby : public DynamicObject
{
public:
	static int redImageNumber;
	static int blueImageNumber;
	static int mapImageNumber;

public:
	Lobby(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap);
	~Lobby();
	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);
};

