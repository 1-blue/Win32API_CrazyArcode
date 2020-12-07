#include "WaterBallon.h"

WaterBallon::WaterBallon(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap)
			: DynamicObject(name, pos, size, hNumber, vNumber, hBitmap)
{
	//�����ýð����
}

WaterBallon::~WaterBallon()
{

}

void WaterBallon::Input()
{
	//�ð�üũ
}

void WaterBallon::Update()
{
	//�ð������� ����
	//�ð������� ��纯��
}

void WaterBallon::Render(HDC hDC, HDC memDc)
{
	SelectObject(memDc, hBitmap);

	TransparentBlt(hDC,
		pos.x, pos.y,					//��µ� �̹��� ������ǥ
		imageWidth, imageHeight,		//��µ� �̹���ũ��
		memDc,
		0, 0,							//�̹������� ����� ������ġ
		imageWidth, imageHeight,		//�̹������� ����� �̹����� ũ��
		RGB(0, 0, 0));
}
