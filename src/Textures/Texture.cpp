#include "Texture.h"

void Texture::Bind(int id){
	glBindTexture(type,id);
}

void Texture::setParam(int key,int val){
	glTextureParameteri(id,key,val);
}
