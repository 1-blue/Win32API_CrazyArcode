#include "MessageQueue.h"

list<ClickEvent> MessageQueue::eventQueue{};

void MessageQueue::AddEventQueue(ClickEvent clickEvent)
{
	eventQueue.emplace_back(clickEvent);
}

const list<ClickEvent> MessageQueue::RunEventQueue()
{
	if (eventQueue.size() <= 0)
		return{};

	return eventQueue;
}
