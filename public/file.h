#ifndef _FILE_H_
#define _FILE_H_

//读取文件函数 
FILE *file_open(const char *filename);

//获取文件大小函数 
int file_getsize(const char *filename); 


//文件数据添加
void file_add(FILE *,int,void *);



 
//初始化用户数据到硬盘文件中
//Lnode *user_data_init(FILE *user_fp);	//在硬盘中初始化用户数据 
#endif 
