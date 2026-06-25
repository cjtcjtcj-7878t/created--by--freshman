#include"Loginwin.h"
#include"../View/control.h"
#include"../public/commonlist.h"
#include"../View/myTiMe.h"
#include"data.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#include<tchar.h>
extern Lnode *userlist;
int loginwin(){
	//登录窗口显示
	TIME_T timectl=time_control_init(480,20,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T Loginwin={200,140,400,350,7,{
	{210,200,100,50,"账户:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{210,270,100,50,"密码:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{280,200,300,50,"",LIGHTCYAN,CYAN,RED,EDIT,1,1},
	{280,270,300,50,"",LIGHTCYAN,CYAN,RED,EDIT_PWD,0,0,0},
	{260,390,100,100,"登录",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{450,390,100,100,"返回",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,140,400,100,"智慧物流管理系统登录界面",LIGHTCYAN,CYAN,RED,LABEL,0},
	},
	WHITE,0}; 
	
	window_show(Loginwin);	//显示窗口 
	time_show(timectl);
	
	Loginwin=window_run_with_time(Loginwin,&timectl);	//有BUTTON控件的窗口需要窗口驱动函数 
	
	if(Loginwin.current==4){
		//在输入账户密码后点击登录操作 
		char name[20]="0";
		char pwd[20]="0";
		
		//将输入的账户保存 
		strcpy(name,Loginwin.controls[2].text);	
		
		//将输入的密码保存 
		strcpy(pwd,Loginwin.controls[3].text);
		
		//strcmp函数值为-1表示两者相同 
		if(strcmp(name,"0")==-1||strcmp(pwd,"0")==-1){
			if(strcmp(name,"0")==-1&&strcmp(pwd,"0")!=-1){
				//只输入了密码
				CONTROL_T namefail={340,330,150,50,"请输入账户!",CYAN,LIGHTCYAN,RED,BUTTON,0};
				control_show(namefail);
				
				Sleep(1500);
				return 1; 
				
			}else if(strcmp(name,"0")!=-1&&strcmp(pwd,"0")==-1){
				//只输入了账户
				CONTROL_T  pwdfail={340,330,150,50,"请输入密码!",CYAN,LIGHTCYAN,RED,BUTTON,0};
				control_show(pwdfail);
				
				Sleep(1500);
				return 1;
				
			}else if(strcmp(name,"0")==-1&&strcmp(pwd,"0")==-1){
				//账户与密码均未输入
				CONTROL_T fail={320,330,200,50,"请输入账户与密码!",CYAN,LIGHTCYAN,RED,BUTTON,0};
				control_show(fail);
				
				Sleep(1500);
				return 1; 
			}
			
		}
		
		//将输入的账号密码与文件中的用户账号密码进行比对 
		int i;
		int flag=0;
		for(i=1;i<=getlistnodecount(userlist);i++){
			USER_T *p=(USER_T *)findnode(userlist,i);
			//printf("%s %s",p->name,p->password);
			if(strcmp(name,p->name)==0&&strcmp(pwd,p->password)==0){
				flag=1;
				CONTROL_T Successwin={340,330,100,50,"登录成功!",CYAN,LIGHTCYAN,RED,BUTTON,0};
				control_show(Successwin);//登录成功弹窗提示 
				
				Sleep(1500);
				
				if(p->role==1){
					//管理员主界面 
					return 2;
				}else if(p->role==2){
					//仓储员主界面 
					return 5;
				}else if(p->role==3){
					//调度员主界面
					return 7; 
				}else if(p->role==4){
					//客服主界面
					return 8; 
				}
			}
		}
		if(getlistnodecount(userlist)==1){
			USER_T *p=NULL;
			p=(USER_T *)findnode(userlist,1);
			if(strcmp(name,p->name)==0&&strcmp(pwd,p->password)==0){
				flag=1;
				CONTROL_T Successwin={340,330,100,50,"登录成功!",CYAN,LIGHTCYAN,RED,BUTTON,0};
				control_show(Successwin);//登录成功弹窗提示 
				
				Sleep(1500);
				return 2;
				
			
			}
		}
 	if(flag==0){
			//登陆失败 
			CONTROL_T Failure={340,330,150,50,"账号或密码错误!",CYAN,LIGHTCYAN,RED,BUTTON,0};
			control_show(Failure);//登陆失败弹窗提示 
			
			Sleep(1500);
			return 1;//重回登录界面(返回登录函数在函数指针的下标) 
		}
	}else if(Loginwin.current==5){
		//点击返回操作则返回主选择界面 
		winbk_flush();
		return 0;
	}else if(Loginwin.current==-1){
		//左键防止程序崩溃
		return 1; 
	}else if(Loginwin.current==-2){
		//右键防止程序崩溃
		return 1; 
	}
}

