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

template<typename T>
const inline unordered_map<string, T> ResourceManager<T>::getMap()
{
	return mp_contents;
}