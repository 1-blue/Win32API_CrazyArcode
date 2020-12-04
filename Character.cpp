#include "Character.h"


Character::Character(CHARTERDATA data)
{
	this->data = data;
}

Character::Character(ImageData2 test) : DynamicObject(test)
{

}

Character::~Character()
{

}

void Character::Input()
{
	if (GetAsyncKeyState(VK_UP))
		test->y -= 1;
	if (GetAsyncKeyState(VK_DOWN))
		test->y += 1;
	if (GetAsyncKeyState(VK_RIGHT))
		test->x += 1;
	if (GetAsyncKeyState(VK_LEFT))
		test->x -= 1;


}

void Character::Update()
{



}

void Character::Render(HDC hDC, HDC memDc)
{
	SelectObject(memDc, test->hBitmap);

	TransparentBlt(hDC,
		test->x, test->y,							//출력될 이미지 시작좌표
		test->vInterval, test->vInterval,			//출력될 이미지크기
		memDc,
		0, 0,	//이미지에서 출력할 시작위치
		test->vInterval, test->vInterval,			//이미지에서 출력할 이미지의 크기
		RGB(255, 0, 255));
}
