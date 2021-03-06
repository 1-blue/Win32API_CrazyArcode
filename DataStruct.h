﻿#pragma once
#include <Windows.h>
#include <string>
#include <list>
#include <vector>
#include <queue>

using namespace std;

constexpr auto WND_WIDTH = 800;
constexpr auto WND_HEIGHT = 600;
constexpr auto IMAGE_DATA_LENGTH = 7;
constexpr auto STATS_DATA_LENGTH = 7;
constexpr auto CURSOR_WIDTH = 33;
constexpr auto CURSOR_HEIGHT = 36;
constexpr auto PLAYER_NUMBER = 2;

//맵의 블록수
constexpr auto MAP_WIDTH_SIZE = 15;
constexpr auto MAP_HEIGHT_SIZE = 11;

//최대최소이동가능포지션
constexpr auto MOVE_MIN_X = 20;
constexpr auto MOVE_MAX_X = 580;
constexpr auto MOVE_MIN_Y = 25;
constexpr auto MOVE_MAX_Y = 495;

//한블럭크기
constexpr auto BLOCK_X = 40;
constexpr auto BLOCK_Y = 47;
constexpr auto SIZE_TUNING = 20;	//이거는 블록위치에 덮어서 출력되야할 사이즈조정을 위한거.. 설명하기 애매해서 보면알수있음

//오차범위 (비껴서 앞으로 갈때)
constexpr auto PERMIT_RANGE = 15;

#define GET_CURSOR_POSITION(point) \
GetCursorPos(&point);\
ScreenToClient(hWnd, &point);
//point.y -= CURSOR_HEIGHT;

typedef struct
{
	int name;			//이미지명
	HBITMAP hBitmap;	//출력할 비트맵
	int objType;		//오브젝트타입
	int x;				//임시 출력 x포지션
	int y;				//임시 출력 y포지션
	int hNumber;		//가로이미지수
	int vNumber;		//세로이미지수
}ImageData, *pImageData;

//캐릭터데이터
typedef struct
{
	int bNum;
	int bLength;
	int speed;
	int bNumMax;
	int bLengthMax;
	int speedMax;
}CharacterStatsData, * pCharacterStatsData;

namespace ObjectData
{
	typedef struct Position
	{
		int x;
		int y;

		bool operator==(const Position& pos)
		{
			if (this->x == pos.x && this->y == pos.y)
				return true;
			return false;
		}

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

namespace WaterBallonState
{
	enum
	{
		DEFAULT,
		EXPLOSION,
		DIE
	};
}

namespace GameStage
{
	enum
	{
		LOBBY,
		INGAME_LOADING,
		INGAME,
		INGAME_EXITING
	};
}

namespace CharacterSelect
{
	enum CharacterSelect
	{
		BAZZI,
		DIZNI,
		RANDOM
	};
}

enum class CharacterColor
{
	NONE,
	RED,
	BLUE
};

enum class CharacterName
{
	BAZZI,
	DIZNI
};

namespace Direction
{
	enum
	{
		TOP,
		LEFT,
		RIGHT,
		BOTTOM,
		CENTER
	};

	typedef struct Dir
	{
		int north{ 0 };	//북
		int west{ 0 };	//서
		int east{ 0 };	//동
		int south{ 0 };	//남

	} DirectionVar;
}

typedef struct
{
	int redCharacterNumber;
	int blueCharacterNumber;
	int mapNumber;
}SelectData, * pSelectData;

typedef struct
{
	string name;
	string path;
	int data[MAP_HEIGHT_SIZE][MAP_WIDTH_SIZE];
}MapData, * pMapData;

namespace Objects
{
	enum
	{
		BLANK,
		BLOCK,
		WALL,
		WATERBALLON,
		ITEM
	};
	enum
	{
		STATIC,
		DYNAMIC,
		BUTTON,
	};
}

namespace WaterBallonKinds
{
	enum
	{
		BALLON,
		CENTER,
		LEFT_END,
		LEFT_MID,
		TOP_END,
		TOP_MID,
		RIGHT_END,
		RIGHT_MID,
		BOTTOM_END,
		BOTTOM_MID
	};
}


	enum class BGM
	{
		ROOM,
		PATRIT,
	};

	enum class EFFECTSOUND
	{
		INSTALL,
		EXPLOSION,
		OVERLAP_BUTTON,
		PICKUP_ITEM,
		EXPLODECHARACTER
	};


typedef struct
{
	bool isAttack;
	CharacterColor color;
	ObjectData::Position pos;

}AttackValue, *pAttackValue;

typedef struct ClickEventStruct
{
	int name;
	bool isRight;

}ClickEvent, * pClickEvent;

typedef struct
{
	string name;		//이미지명
	HBITMAP hBitmap;	//출력할 비트맵
	int hNumber;		//가로이미지수
	int vNumber;		//세로이미지수
	int imageWidth;		//이미지 하나의 가로 길이
	int imageHeight;	//이미지 하나의 세로 길이
	int printVerticalNumber;	//출력할 가로이미지번호
	int printHorizontalNumber;	//출력할 세로이미지번호

}Img, * pImg;

//물풍선 공격범위.. 물풍선에서 캐릭터에게 넘겨줄값
typedef struct
{
	POINT pos;	//물풍선좌표
	int t;		//공격범위
	int r;
	int b;
	int l;
}AttackArea, *pAttackArea;

typedef struct
{
	int name;
	ObjectData::Position pos;	//아이템포지션

}ItemValue, * pItemValue;


enum class CharacterState
{
	NORMAL,
	TRAPPED,
	DIE,
	DEAD
};

//잠깐추가
//trapped상태 모션
enum TrappedMotion
{
	BAZZI_TRAPPED,
	DIZNI_TRAPPED
};

//death상태 모션
enum DeathMotion
{
	RED_BAZZI_DEATH,
	BLUE_BAZZI_DEATH,
	RED_DIZNI_DEATH,
	BLUE_DIZNI_DEATH
};