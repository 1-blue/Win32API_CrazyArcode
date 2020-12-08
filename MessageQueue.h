#pragma once
#include <list>
#include <string>
#include "DataStruct.h"

using namespace std;

class MessageQueue
{
private:
	static list<ClickEvent> eventQueue;		//이벤트가 쌓이는 리스트

public:
	static void AddEventQueue(const ClickEvent clickEvent);	//이벤트 추가
	static const list<ClickEvent> RunEventQueue();					//루트 돌면서 이벤트 수행
};

