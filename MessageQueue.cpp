#include "MessageQueue.h"
#include "DynamicObject.h"

queue<ClickEvent> MessageQueue::eventQueue{};

void MessageQueue::AddEventQueue(ClickEvent clickEvent)
{
	eventQueue.push(clickEvent);
}

void MessageQueue::RunEventQueue(list<Obj*> objList)
{
	if (eventQueue.size() <= 0)
		return;

	while (eventQueue.size() != 0)
	{
		MessageLoop(eventQueue.front(), objList);

		eventQueue.pop();
	}
}

void MessageQueue::MessageLoop(const ClickEvent clickEvent, list<Obj*> objList)
{
	if (clickEvent.name == "exit")
		exit(0);
	if (clickEvent.name == "bazziPickImage")
	{
		for (auto iterator : objList)
		{
			if (iterator->GetName() == "redCharacter" && clickEvent.isRight == false)	//좌클릭
				dynamic_cast<DynamicObject*>(iterator)->SetImageNumber(0);
			if (iterator->GetName() == "blueCharacter" && clickEvent.isRight == true)	//우클릭
				dynamic_cast<DynamicObject*>(iterator)->SetImageNumber(0);
		}
	}
	if ((clickEvent.name == "dizniPickImage"))
	{
		for (auto iterator : objList)
		{
			if (iterator->GetName() == "redCharacter" && clickEvent.isRight == false)	//좌클릭
				dynamic_cast<DynamicObject*>(iterator)->SetImageNumber(1);
			if (iterator->GetName() == "blueCharacter" && clickEvent.isRight == true)	//우클릭
				dynamic_cast<DynamicObject*>(iterator)->SetImageNumber(1);
		}
	}
	if ((clickEvent.name == "RandomPickImage"))
	{
		for (auto iterator : objList)
		{
			if (iterator->GetName() == "redCharacter" && clickEvent.isRight == false)	//좌클릭
				dynamic_cast<DynamicObject*>(iterator)->SetImageNumber(2);
			if (iterator->GetName() == "blueCharacter" && clickEvent.isRight == true)	//우클릭
				dynamic_cast<DynamicObject*>(iterator)->SetImageNumber(2);
		}
	}
}






//const list<ClickEvent> MessageQueue::RunEventQueue()
//{
//	
//		return{};
//
//	return eventQueue;
//}
