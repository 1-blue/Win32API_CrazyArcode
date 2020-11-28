#pragma once
#include <Windows.h>
#include <list>

using namespace std;

class ImageManager
{
private:
	list<HBITMAP> hbmpList;

public:
	void LoadData();
	list<HBITMAP>* GetData();


};

