#ifndef _CONTROL_H_
#define _CONTROL_H_
#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<tchar.h>
#include"../View/myTiMe.h"
//宏定义控件类型 
#define BUTTON 1	//按钮 
#define EDIT 2		//明文输入 
#define EDIT_PWD 3	//密码输入 
#define LABEL 4		//标签 
#define SELECT 5
#define SELECTED 6
#define TIME 7		//时间控件 
//宏定义键盘操作 
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77 


//定义控件结构体
typedef struct{
	int x;	//控件起始x坐标 
	int y;	//控件起始Y坐标 
	int width;		//控件宽度 
	int height;		//控件高度 
	char text[100];		//控件显示的文字(可有可无) 
	COLORREF bgcolor1;	//控件聚焦时呈现的颜色 
	COLORREF bgcolor2;	//控件未聚焦时呈现的颜色 
	COLORREF textcolor;		//控件有文字时，文字呈现的颜色 
	int style;		//控件类型(BUTTON,EDIT,EDIT_PWD,BUTTON) 
	int state;		//控件状态(1-聚焦与非0-聚焦) 
	int chineseEdit;		//控件是否需要输入中文,1-需要,0-不需要
	int pwd_show;			//密码明文密文显示,1-明文，0-密文 
}CONTROL_T; 


//定义窗口结构体(一个窗口包含多个控件)
typedef struct{
	int x;		//窗口起始x坐标 
	int y;		//窗口起始y坐标 
	int width;		//窗口宽度 
	int height;		//窗口高度 
	int count;		//窗口包含的控件数量 
	CONTROL_T controls[30];		//控件数组，元素为每个具体的控件 
	COLORREF bgcolor;		//窗口的背景颜色 
	int current;		//窗口当前聚焦的控件 
}WINDOW_T; 

//定义表格结构体 
typedef struct table_t{
	int x;	// 
	int y;
	int width;
	int height;
	int row;	//表格行数 
	int col;	//表格列数 
	char text[10][20];	//表的首行 
	char data[5][10][20];	//存储表格中的内容
	int count;	//实际数据所占的表格行数 
}TABLE_T;

//控件显示函数
void control_show(CONTROL_T); 

//窗口显示函数
void window_show(WINDOW_T);

//窗口驱动函数(集成时间显示)
WINDOW_T window_run_with_time(WINDOW_T,TIME_T *); 

//窗口驱动
WINDOW_T window_run(WINDOW_T); 

//背景图片重刷函数
void winbk_flush(); 

//绘制表格函数
void table_show(TABLE_T,int,int); 

//中文输入函数
void InputEdit(CONTROL_T *,const char *); 

#endif
