#ifndef _MYTIME_H_
#define _MYTIME_H_


#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h> 
#include<tchar.h>
#include<time.h>

typedef enum{
	TIME_FORMAT_SIMPLE,		//HH:MM:SS
	TIME_FORMAT_FULL,			//YYYY--MMMM--DDDD HH:MM:SS
	TIME_FORMAT_DATE,			//YYYY--MMMM--DDDD
	TIME_FORMAT_TIME,			//HH:MM:SS
}TIME_FORMAT_E;

typedef struct{
	int x;		//起始x坐标 
	int y;		//起始y坐标 
	int width;		//宽度 
	int height;		//高度 
	char text[100];		//文本内容  
	int updatenum;			//时间更新间隔 
	TIME_FORMAT_E format;		//时间输出格式 	
}TIME_T;

//初始化时间结构体
TIME_T time_control_init(int,int,int,int,int,TIME_FORMAT_E); 

//获取时间 
void get_time_by_format(char *,TIME_FORMAT_E);

//显示时间 
void time_show(TIME_T);

//动态更新时间
int time_update(TIME_T *); 

//显示角色身份及账户名
void role_show();   


#endif
