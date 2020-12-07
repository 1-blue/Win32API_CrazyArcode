#pragma once
#include "StaticObject.h"
#include "DataStruct.h"

class Blank : public StaticObject
{
private:


public:
	Blank();
	~Blank();

	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);
};