#include "MessageQueue.h"

void MessageQueue::AddEventQueue(const string name)
{
	eventQueue.emplace_back(name);
}

void MessageQueue::RunEventQueue()
{
	if (eventQueue.size() <= 0)
		return;

	while (eventQueue.size()>=1)
	{
		ProcesssEvent(eventQueue.front());
		eventQueue.pop_front();
	}
}

void MessageQueue::ProcesssEvent(const string str)
{

}
