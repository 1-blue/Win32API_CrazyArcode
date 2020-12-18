#include "WaterBallon.h"

WaterBallon::WaterBallon(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap)
			: DynamicObject(name, pos, size, hNumber, vNumber, hBitmap)
{
	charAnimationTick = GetTickCount64();	//�����ð����
	order = pos.y;
}

WaterBallon::~WaterBallon()
{

}

void WaterBallon::Input()
{

}

void WaterBallon::Update()
{
	if (!CheckmDelay(300))
		return;

	printhNumber++;					//�ð������� ��纯��
	if (printhNumber == hNumber)	//�ð�������,, �������� : 8���ݺ��ϸ�
	{
		printhNumber = 0;
		isAlive = false;
	}
}

void WaterBallon::Render(HDC hDC, HDC memDc)
{
	SelectObject(memDc, hBitmap);

	TransparentBlt(hDC,
		pos.x, pos.y,					//��µ� �̹��� ������ǥ
		imageWidth, imageHeight,		//��µ� �̹���ũ��
		memDc,
		printhNumber * imageWidth, 0,	//�̹������� ����� ������ġ
		imageWidth, imageHeight,		//�̹������� ����� �̹����� ũ��
		RGB(0, 0, 0));
}

const bool WaterBallon::GetIsAlive()
{
	return isAlive;
}

bool WaterBallon::CheckmDelay(const int delayTime)
{
	if (GetTickCount64() > charAnimationTick + delayTime)
	{
		charAnimationTick = GetTickCount64();
		return true;
	}
	return false;
}
