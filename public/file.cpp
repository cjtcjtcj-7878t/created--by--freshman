#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"file.h"

/*
函数名：file_open
函数功能：打开文件，若文件不存在则新建文件，文件存在则正常打开 
参数：文件名 
返回值： 文件指针 
*/

FILE *file_open(const char *filename){
	FILE *fp=NULL;
	
	fp=fopen(filename,"r+");
	if(fp==NULL){
		perror("文件打开失败!");
		fp=fopen(filename,"w+");
	}
	return fp;
}     


/*
函数名：file_getsize
函数功能：获取文件大小 
函数参数：文件名 
函数返回值： 文件大小，若文件打开失败返回-1， 
*/

int file_getsize(const char *filename){
	FILE *fp;
	fp=fopen(filename,"rb+");
	if(fp==NULL){
		perror("打开文件失败!");
		return -1;
	}
	fseek(fp,0,SEEK_END);
	return ftell(fp);
}



/*
函数名:file_add
函数功能:在文件末尾追加数据 
函数参数:FILE *:文件指针，指要添加的文件 
		 int:数据大小
		 void *:数据类型 
函数返回值: 无 
*/

void file_add(FILE *fp,int size,void *data){
	
	fseek(fp,0,SEEK_END);
	fwrite(data,size,1,fp);
	fflush(fp);
}
