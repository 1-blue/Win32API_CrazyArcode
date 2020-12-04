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

	//임시추가
	int dir{ Diraction::TOP };
	POINT printPos{ 0, 0 };

public:
	Character(CHARTERDATA data);	//잠깐보류하고 이미지부터받아봄
	Character(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, int hInterval, int vInterval, HBITMAP hBitmap);
	~Character();

	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);
};

