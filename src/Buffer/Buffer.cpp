#include "Buffer.h"
#include <utility>

void Buffer::Data(void* data,int size){
	this->data=data;
	this->size=size;
	glBufferData(type,size,data, usage);
}
void Buffer::Bind(){
	glBindBuffer(type,this->id);
	Data(this->data,this->size);
}
void VertexArray::Bind(){
	glBindVertexArray(this->id);
}

void VertexLayout::AddEntry(int type,int stride,int n){
	this->vec.push_back(VertexLayoutEntry(type,stride,n));
}
void VertexLayout::Bind(){
	int sum=0;
	for(auto x:this->vec){
		int width=x.stride*x.n;
		glVertexAttribPointer(sum,x.n,x.type,normalized,width,NULL);
		sum+=width;
	}
	glEnableVertexAttribArray(0);
}
