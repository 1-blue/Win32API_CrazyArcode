#pragma once
#include "StaticObject.h"
#include "DataStruct.h"

class Wall : public StaticObject
{
private:


public:
	Wall();
	~Wall();

	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);
};