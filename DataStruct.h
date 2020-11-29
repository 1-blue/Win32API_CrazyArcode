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
}DefaultBitmap, * pDefaultBitmap;

#define SSSS 5