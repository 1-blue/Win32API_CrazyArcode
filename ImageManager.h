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
	vector<pDefaultBitmap> defaultBitmap;

public:
	ImageManager();
	~ImageManager();
	void LoadData();
	const vector<pDefaultBitmap>& GetBitmap() const;

};

