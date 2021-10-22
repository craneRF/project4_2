#pragma once
#include "ofMain.h"

template<typename T> class ResourceManager;  //template�t���N���X�̑O���錾

class Texture
{
public:
	Texture();
	~Texture();

	//const shared_ptr<ofImage> GetImage(const string& _filename);
	ofImage* GetImage(const string& _filename);

private:
	bool Load();

	unique_ptr<ResourceManager<ofImage>> mp_ImageManager;
};

