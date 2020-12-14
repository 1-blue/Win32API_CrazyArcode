#pragma once
#include <list>
#include <string>
#include "DataStruct.h"

using namespace std;
class Obj;
class MessageQueue
{
private:
	static queue<ClickEvent> eventQueue;		//이벤트가 쌓이는 리스트

public:
	static void AddEventQueue(const ClickEvent clickEvent);	//이벤트 추가
	static void RunEventQueue(list <Obj*> objList);	//루프 돌면서 이벤트 수행
	static void MessageLoop(const ClickEvent clickEvent, list <Obj*> objList);
};

