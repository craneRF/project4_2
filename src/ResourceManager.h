#pragma once
#include "ofMain.h"

template<typename T>
class ResourceManager
{
private:
	unordered_map<string, T> mp_contents;

public:
	ResourceManager();
	virtual ~ResourceManager();

	void loadContentFromFile(string _filename);
	T* getContents(string _key);
	void clearContents();
	void unloadContentFromFile(string _filename);
	void loadCropImageFromFile(string _fileName, int _width, int _height);
	const unordered_map<string, T> getMap();
};

template<typename T>
inline ResourceManager<T>::ResourceManager()
{
}

template<typename T>
inline ResourceManager<T>::~ResourceManager()
{
	mp_contents.clear();
}

template<typename T>
inline void ResourceManager<T>::loadContentFromFile(string _filename)
{
	ofBuffer resfile = ofBufferFromFile(_filename);
	auto lines = resfile.getLines();
	for (auto l : lines)
	{
		mp_contents.insert(make_pair(l, T(l)));
	}
}

template<typename T>
inline T* ResourceManager<T>::getContents(string _key)
{
	return &mp_contents[_key];
}

template<typename T>
inline void ResourceManager<T>::clearContents()
{
	mp_contents.clear();
}

template<typename T>
inline void ResourceManager<T>::unloadContentFromFile(string _filename)
{
	ofBuffer resfile = ofBufferFromFile(_filename);
	auto lines = resfile.getLines();
	for (auto l : lines) {
		mp_contents.erase(l);
	}
}


template<>
inline void ResourceManager<ofImage>::loadCropImageFromFile(string _fileName, int _width, int _height)
{
	//ofBuffer resfile = ofBufferFromFile(_fileName);
	//auto lines = resfile.getLines();
	//for (auto l : lines) {
	//	// contents_[l] = T(l);
	//	contents_.insert(make_pair(l, T(l)));
	//}
	//if (T != ofImage){
	//	OutputDebugString("not ofImage\n");
	//	return;
	//}
	ofImage res;
	res.loadImage(_fileName);
	int w = res.getWidth() / _width;
	int h = res.getHeight() / _height;

	for (int i = 0; i < 2; i++)
	{
		int a = _fileName.find("/") + 1;
		_fileName.erase(0, a);
	}
	ofImage cropedRes;
	for (auto i = 0; i < h; i++)
	{
		for (auto j = 0; j < w; j++)
		{
			cropedRes.cropFrom(res, j * _width, i * _height, _width, _height);
			mp_contents.insert(make_pair(_fileName + std::to_string(i * w + j), cropedRes));
		}
	}
}

template<typename T>
const inline unordered_map<string, T> ResourceManager<T>::getMap()
{
	return mp_contents;
}