#include "Wall.h"

Wall::Wall(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap)
	:StaticObject(name, pos, size, hBitmap)
{
	order = pos.y;
}

Wall::~Wall()
{
}

void Wall::Input()
{
}

void Wall::Update()
{
}