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
	long sum=0;
	int width=0;
	for(auto x:this->vec){
		width+=x.stride*x.n;
	}
	int i=0;
	for(auto x:this->vec){
		glVertexAttribPointer(i,x.n,x.type,normalized,width,(void*)sum);
		sum=sum+x.stride*x.n;
		glEnableVertexAttribArray(i);
		i++;
	}
}
