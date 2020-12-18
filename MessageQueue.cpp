#include "MessageQueue.h"
#include "DynamicObject.h"

queue<ClickEvent> MessageQueue::eventQueue{};
SelectData MessageQueue::selectData{ 0, 0, 0};

constexpr unsigned int HashCode(const char* str)
{
	return str[0] ? static_cast<unsigned int>(str[0]) + 0xEDB8832Full * HashCode(str + 1) : 8603;
}

void MessageQueue::CharPickEvent(list<Obj*>& objList, bool isRight, int pickEvent)
{
	int setImageNumber;

	switch (pickEvent)
	{
	case CharacterSelect::BAZZI:
		setImageNumber = CharacterSelect::BAZZI;
		break;
	case CharacterSelect::DIZNI:
		setImageNumber = CharacterSelect::DIZNI;
		break;
	case CharacterSelect::RANDOM:
		setImageNumber = CharacterSelect::RANDOM;
		break;
	}


	for (auto iterator : objList)
	{
		if (HashCode(iterator->GetName().c_str()) == HashCode("redCharacter") && isRight == false)	//좌클릭
		{
			dynamic_cast<DynamicObject*>(iterator)->SetImageNumber(setImageNumber);
			selectData.redCharacterNumber = setImageNumber;
		}

		if (HashCode(iterator->GetName().c_str()) == HashCode("blueCharacter") && isRight == true)	//우클릭
		{
			dynamic_cast<DynamicObject*>(iterator)->SetImageNumber(setImageNumber);
			selectData.blueCharacterNumber = setImageNumber;
		}
	}
}

void MessageQueue::AddEventQueue(ClickEvent clickEvent)
{
	eventQueue.push(clickEvent);
}

void MessageQueue::RunEventQueue(list<Obj*>& objList, int& sceneState)
{
	if (eventQueue.size() <= 0)
		return;

	while (eventQueue.size() != 0)
	{
		MessageLoop(eventQueue.front(), objList, sceneState);

		eventQueue.pop();
	}
}

void MessageQueue::MessageLoop(const ClickEvent clickEvent, list<Obj*>& objList, int& sceneState)
{
	if (sceneState == GameStage::INGAME)	//인게임
	{
		switch (HashCode(clickEvent.name.c_str()))
		{
		case HashCode("exit"):
			sceneState = GameStage::INGAME_EXITING;	break;
		}
		return;
	}

	//로비의 버튼기능
	switch (HashCode(clickEvent.name.c_str()))
	{
	case HashCode("exit"):
		exit(0);	break;
	case HashCode("bazziPickImage"):
		CharPickEvent(objList, clickEvent.isRight, CharacterSelect::BAZZI);
		break;
	case HashCode("dizniPickImage"):
		CharPickEvent(objList, clickEvent.isRight, CharacterSelect::DIZNI);
		break;
	case HashCode("RandomPickImage"):
		CharPickEvent(objList, clickEvent.isRight, CharacterSelect::RANDOM);
		break;
	case HashCode("mapPick"):
		if (clickEvent.isRight)
			break;

		for (auto iterator : objList)
		{
			if (iterator->GetName() == "map")
			{
				int tempImageNumber = dynamic_cast<DynamicObject*>(iterator)->GetImageNumber();
				dynamic_cast<DynamicObject*>(iterator)->SetImageNumber((tempImageNumber == 1 ? 0 : 1));
				selectData.mapNumber = (tempImageNumber == 1 ? 0 : 1);
			}
		}
		break;
	case HashCode("start"):
		sceneState = GameStage::INGAME_LOADING;
		break;
	}
}