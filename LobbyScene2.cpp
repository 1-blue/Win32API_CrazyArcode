#include "LobbyScene2.h"
#include "Obj.h"

void LobbyScene2::LoadData()
{

}

void LobbyScene2::Process()
{
	for (auto iter : lobbyObjectVector)
	{
		iter->Input();
		iter->Update();
		//iter->Render();
	}
}
