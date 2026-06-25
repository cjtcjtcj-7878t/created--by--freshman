#include"../View/myTiMe.h"
#include<time.h>
#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



void get_time_by_format(char *timestr,TIME_FORMAT_E format){
	
	//获取时间戳 
	time_t now=time(NULL);
	struct tm* local=localtime(&now);
	
	
	//获取不同格式时间 
	switch(format){
		case TIME_FORMAT_SIMPLE:
			
			sprintf(timestr,"当前时间 %02d:%02d:%02d",local->tm_hour,local->tm_min,local->tm_sec);
			break;
		
		case TIME_FORMAT_FULL:
			
			sprintf(timestr,"当前时间 %04d--%02d--%02d %02d:%02d:%02d",local->tm_year+1900,local->tm_mon+1,
			local->tm_mday,local->tm_hour,local->tm_min,local->tm_sec);
			break;
			
		case TIME_FORMAT_DATE:
			
			sprintf(timestr,"当前时间 %04d--%02d--%02d",local->tm_year+1900,local->tm_mon+1,
			local->tm_mday);
			break;
			
		case TIME_FORMAT_TIME:
			
			sprintf(timestr,"当前时间 %02d:%02d:%02d",local->tm_hour,local->tm_min,local->tm_sec);
			break;
			
		default:
			strcpy(timestr,"未知格式");
			break; 
	}
	
}

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//初始化结构体 
TIME_T time_control_init(int x,int y,int width,int height,
int num,TIME_FORMAT_E format)
{
	TIME_T p={x,y,width,height,"",num,format};
	get_time_by_format(p.text,p.format);
	
	return p;  
}
////////////////////////////////////////////////////////////////////////////// 

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

void time_show(TIME_T ctrl){
	
	//绘制背景
	setfillcolor(WHITE);
	setlinecolor(BLUE);
	settextcolor(YELLOW);
	fillrectangle(ctrl.x,ctrl.y,ctrl.x+ctrl.width,ctrl.y+ctrl.height);
	rectangle(ctrl.x,ctrl.y,ctrl.x+ctrl.width,ctrl.y+ctrl.height);
	
	//设置文字
	settextcolor(RED);
	settextstyle(30,10,_T("宋体"));
	
	//显示时间 
	int textwidth=strlen(ctrl.text)*10;
	int center=ctrl.x+(ctrl.width-textwidth)/2;
	
	outtextxy(center,ctrl.y+(ctrl.height-30)/2,ctrl.text); 
	
	FlushBatchDraw(); 
	
}

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void role_show(){
	
	
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
int time_update(TIME_T *tc) {    
	static unsigned long lastUpdateTime = 0;    
	unsigned long currentTime = GetTickCount();        
	// 检查是否到达更新时间间隔    
	if (currentTime - lastUpdateTime >= tc->updatenum) {        
			char newTime[30] = "\0";        
			get_time_by_format(newTime, tc->format);                
		// 只在时间改变时更新        
			if (strcmp(tc->text, newTime) != 0) {            
				strcpy(tc->text, newTime);            
				time_show(*tc);            
				lastUpdateTime = currentTime;            
				return 1;  // 需要刷新        
			}    
		}        
	return 0;  // 不需要刷新
}
