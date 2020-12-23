#include "MessageQueue.h"
#include "DynamicObject.h"

queue<ClickEvent> MessageQueue::eventQueue{};
SelectData MessageQueue::selectData{ 0, 0, 0};

map<string, int> MessageQueue::sToEnumMap{ {"background", EnumObj::background },{"redCharacter", EnumObj::redCharacter },
{"blueCharacter", EnumObj::blueCharacter } ,{"bazziPickImage", EnumObj::bazziPickImage } ,{"dizniPickImage", EnumObj::dizniPickImage } ,
{"RandomPickImage", EnumObj::RandomPickImage } ,{"exit", EnumObj::exit } ,{"map", EnumObj::map } ,
{"mapPick", EnumObj::mapPick } ,{"start", EnumObj::start } ,{"Block", EnumObj::Block } ,
{"Wall", EnumObj::Wall } ,{"WaterBallon", EnumObj::WaterBallon },
{"RedBazzi", EnumObj::RedBazzi } ,{"RedDizni", EnumObj::RedDizni },
{"BlueBazzi", EnumObj::BlueBazzi } ,{"BlueDizni", EnumObj::BlueDizni } ,
{"Trapped", EnumObj::Trapped } ,{"Die", EnumObj::Die },
{"drawUI",EnumObj::drawUI},{"loseUI",EnumObj::loseUI},{"winUI",EnumObj::winUI} };

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
		if (iterator->GetName() == EnumObj::redCharacter && isRight == false)	//좌클릭
		{
			dynamic_cast<DynamicObject*>(iterator)->SetImageNumber(setImageNumber);
			selectData.redCharacterNumber = setImageNumber;
		}

		if (iterator->GetName() == EnumObj::blueCharacter && isRight == true)	//우클릭
		{
			dynamic_cast<DynamicObject*>(iterator)->SetImageNumber(setImageNumber);
			selectData.blueCharacterNumber = setImageNumber;
		}
	}
}

const int MessageQueue::StringToEnum(string str)
{
	return sToEnumMap[str];
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
		switch (clickEvent.name)
		{
		case EnumObj::exit:
			sceneState = GameStage::INGAME_EXITING;	break;
		}
		return;
	}

	//로비의 버튼기능
	switch (clickEvent.name)
	{
	case EnumObj::exit:
		exit(0);	break;
	case EnumObj::bazziPickImage:
		CharPickEvent(objList, clickEvent.isRight, CharacterSelect::BAZZI);
		break;
	case EnumObj::dizniPickImage:
		CharPickEvent(objList, clickEvent.isRight, CharacterSelect::DIZNI);
		break;
	case EnumObj::RandomPickImage:
		CharPickEvent(objList, clickEvent.isRight, CharacterSelect::RANDOM);
		break;
	case EnumObj::mapPick:
		if (clickEvent.isRight)
			break;

		for (auto iterator : objList)
		{
			if (iterator->GetName() == EnumObj::map)
			{
				int tempImageNumber = dynamic_cast<DynamicObject*>(iterator)->GetImageNumber();
				dynamic_cast<DynamicObject*>(iterator)->SetImageNumber((tempImageNumber == 1 ? 0 : 1));
				selectData.mapNumber = (tempImageNumber == 1 ? 0 : 1);
			}
		}
		break;
	case EnumObj::start:
		sceneState = GameStage::INGAME_LOADING;
		break;
	}
}