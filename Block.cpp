#include "Block.h"

Block::Block(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap)
	:StaticObject(name, pos, size, hBitmap)
{
	order = pos.y;

	mapPos.x = ((pos.x + 20) / BLOCK_X) - 1;
	mapPos.y = ((pos.y + 2) / BLOCK_Y) - 1;
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

const ObjectData::POSITION Block::GetMapPos()
{
	return mapPos;
}
