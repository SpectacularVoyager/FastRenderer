#include "Texture.h"

void Texture::Bind(int id){
	glActiveTexture(GL_TEXTURE0+id);
	glBindTexture(type,this->id);
}

void Texture::setParam(int key,int val){
	glTextureParameteri(id,key,val);
}
