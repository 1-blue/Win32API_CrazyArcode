#pragma once
#pragma comment(lib, "Msimg32.lib")
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#include "DataStruct.h"

using namespace std;

class ImageManager
{
private:
	ifstream fin;
	vector<pDefaultData> defaultBitmap;

public:
	ImageManager();
	~ImageManager();
	void LoadDafaultData();
	const vector<pDefaultData>& GetBitmap() const;

};

