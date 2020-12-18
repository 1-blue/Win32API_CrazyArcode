#include "Block.h"

Block::Block(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap)
	:StaticObject(name, pos, size, hBitmap)
{
	order = pos.y;
}

Block::~Block()
{
}

void Block::Input()
{
}

void Block::Update()
{
}