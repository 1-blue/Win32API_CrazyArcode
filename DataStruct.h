#pragma once
#include <string>
#include <Windows.h>

using namespace std;

typedef struct
{
	string name;		//이미지명
	HBITMAP hBitmap;	//출력할 비트맵
	int objType;		//오브젝트타입
	int x;				//임시 출력 x포지션
	int y;				//임시 출력 y포지션
	int kinds;			//단일, 가로. 세로 구분
	int number;			//이미지수
	int interval;		//간격

}DefaultBitmap, * pDefaultBitmap;

#define SSSS 8

namespace ObjectData
{
	typedef struct Position
	{
		int x;
		int y;

	}POSITION, * pPOSITION;

	typedef struct Size
	{
		int width;
		int height;

	}SIZE, * pSIZE;

	enum
	{
		NONE,
		HORIZONTAL,
		VERTICAL
	};
}