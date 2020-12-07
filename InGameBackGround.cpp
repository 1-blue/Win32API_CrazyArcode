#include "InGameBackGround.h"

InGameBackGround::InGameBackGround(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, HBITMAP hBitmap)
								: StaticObject(name, pos, size, hBitmap)
{

}

InGameBackGround::~InGameBackGround()
{

}

void InGameBackGround::Input()
{

}

void InGameBackGround::Update()
{

}

void InGameBackGround::Render(HDC hDC, HDC memDc)
{
	SelectObject(memDc, hBitmap);

	TransparentBlt(hDC,
		pos.x, pos.y,					//��µ� �̹��� ������ǥ
		size.width, size.height,		//��µ� �̹���ũ��
		memDc,
		0, 0,							//�̹������� ����� ������ġ
		size.width, size.height,		//�̹������� ����� �̹����� ũ��
		RGB(255, 0, 255));
}