#include "Block.h"

Block::Block()
{
}

Block::Block(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap)
	:StaticObject(name, pos, size, hBitmap)
{
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

void Block::Render(HDC hDC, HDC memDc)
{
}