#pragma once
#include <list>
#include <string>
#include <map>
#include "DataStruct.h"

using namespace std;
class Obj;

class MessageQueue
{
private:
	static queue<ClickEvent> eventQueue;		//이벤트가 쌓이는 리스트
	static map<string, int> sToEnumMap;

	static void CharPickEvent(list<Obj*>& objList, bool isRight, int pickEvent);
public:
	static SelectData selectData;
	
public:
	static const int StringToEnum(string str);

	static void AddEventQueue(const ClickEvent clickEvent);	//이벤트 추가
	static void RunEventQueue(list <Obj*>& objList, int& sceneState);	//루프 돌면서 이벤트 수행
	static void MessageLoop(const ClickEvent clickEvent, list <Obj*>& objList, int& sceneState);
};

namespace EnumObj
{
	enum AllObject
	{
		background,
		redCharacter,
		blueCharacter,
		bazziPickImage,
		dizniPickImage,
		RandomPickImage,
		exit,
		map,
		mapPick,
		start,
		Block,
		Wall,
		WaterBallon,
		RedBazzi,
		RedDizni,
		BlueBazzi,
		BlueDizni,
		Trapped,
		Die
	};
}