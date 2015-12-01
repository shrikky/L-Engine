#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>


TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(std::string texturePath){

	auto mapIterator = _textureMap.find(texturePath);

	if (mapIterator == _textureMap.end()){
		// Load the texture
		GLTexture newTexture = ImageLoader::loadPNG(texturePath);
		
		//Insert the pair into the map
		_textureMap.insert(make_pair(texturePath, newTexture));
		std::cout << "Loaded Texture! \n";
		return newTexture;
	}
	else
	{
		return mapIterator->second;
	}
}
