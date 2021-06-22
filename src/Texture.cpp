#include "Texture.h"
#include "ResourceManager.h"

Texture::Texture()
	:mp_ImageManager(nullptr)
{
	Load();
}

Texture::~Texture()
{
}

ofImage * Texture::GetImage(const string & _filename)
{
	return mp_ImageManager->getContents(_filename);
}

bool Texture::Load()
{
	mp_ImageManager = make_unique<ResourceManager<ofImage>>();
	mp_ImageManager->loadContentFromFile("ImageRes.txt");
	return true;
}

//const shared_ptr<ofImage> Texture::GetImage(const string& _filename)
//{
//	shared_ptr<ofImage> image = make_shared<ofImage>(mp_ImageManager->getContents(_filename));
//	return image;
//}
