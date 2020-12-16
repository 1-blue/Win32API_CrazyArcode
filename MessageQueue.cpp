#include "MessageQueue.h"
#include "DynamicObject.h"

queue<ClickEvent> MessageQueue::eventQueue{};
SelectData MessageQueue::selectData{ 0, 0, 0, false };

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
			{
				dynamic_cast<DynamicObject*>(iterator)->SetImageNumber(0);
				selectData.redCharacterNumber = CharacterSelect::BAZZI;
			}
				
			if (iterator->GetName() == "blueCharacter" && clickEvent.isRight == true)	//우클릭
			{
				dynamic_cast<DynamicObject*>(iterator)->SetImageNumber(0);
				selectData.blueCharacterNumber = CharacterSelect::BAZZI;
			}		
		}
	}
	if ((clickEvent.name == "dizniPickImage"))
	{
		for (auto iterator : objList)
		{
			if (iterator->GetName() == "redCharacter" && clickEvent.isRight == false)	//좌클릭
			{
				dynamic_cast<DynamicObject*>(iterator)->SetImageNumber(1);
				selectData.redCharacterNumber = CharacterSelect::DIZNI;
			}
				
			if (iterator->GetName() == "blueCharacter" && clickEvent.isRight == true)	//우클릭
			{
				dynamic_cast<DynamicObject*>(iterator)->SetImageNumber(1);
				selectData.blueCharacterNumber = CharacterSelect::DIZNI;
			}
		}
	}
	if ((clickEvent.name == "RandomPickImage"))
	{
		for (auto iterator : objList)
		{
			if (iterator->GetName() == "redCharacter" && clickEvent.isRight == false)	//좌클릭
			{
				dynamic_cast<DynamicObject*>(iterator)->SetImageNumber(2);
				//selectData.redcharacterNumber = //랜덤값넣기
			}
				
			if (iterator->GetName() == "blueCharacter" && clickEvent.isRight == true)	//우클릭
			{
				dynamic_cast<DynamicObject*>(iterator)->SetImageNumber(2);
				//selectData.blueCharacterNumber = //랜덤값넣기
			}	
		}
	}
	if ((clickEvent.name == "mapPick"))
	{
		for (auto iterator : objList)
		{
			if (iterator->GetName() == "map" && clickEvent.isRight == false)	//좌클릭
			{
				int tempImageNumber = dynamic_cast<DynamicObject*>(iterator)->GetImageNumber();
				dynamic_cast<DynamicObject*>(iterator)->SetImageNumber((tempImageNumber == 1 ? 0 : 1));
				selectData.mapNumber = (tempImageNumber == 1 ? 0 : 1);
			}	
		}
	}
	if ((clickEvent.name == "start"))
	{
		selectData.isStart = true;
	}
}