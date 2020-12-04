#pragma once
#include "DynamicObject.h"

//캐릭터데이터
typedef struct
{
	string name;
	int bNum;
	int bLength;
	int speed;
	int bNumMax;
	int bLengthMax;
	int speedMax;
	int image_char;
}CHARTERDATA, * pCHARACTERDATA;

class Character : public DynamicObject
{
private:
	CHARTERDATA data;

	int x{ 0 };
	int y{ 0 };

public:
	Character(CHARTERDATA data);
	Character(ImageData2 test);
	~Character();

	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);
};

