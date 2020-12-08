#pragma once
#include "Obj.h"

class StaticObject : public Obj
{

public:
	StaticObject();		//이거 나중에 삭제 지금은 block같은거 때문에 남겨놓음
	StaticObject(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap);
	~StaticObject();
	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);

};

