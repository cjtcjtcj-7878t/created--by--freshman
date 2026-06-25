#include"Startwin.h"
#include"../View/myTiMe.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"../View/control.h"
#include"../App/data.h"
#include"../public/commonlist.h"
#include"../public/file.h"
#include<tchar.h>
#include<string.h>

extern Lnode *userlist;

int startwin(){
	//主窗口显示
	
	TIME_T timectl=time_control_init(480,20,300,50,1000,TIME_FORMAT_FULL);
	
	WINDOW_T Startwin={200,120,400,300,4,{
	{200,200,400,100,"1.登录",LIGHTCYAN,CYAN,RED,BUTTON,1},
	{200,300,400,100,"2.忘记密码",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{200,400,400,100,"3.退出",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,130,400,100,"智慧物流管理系统主界面",LIGHTCYAN,CYAN,RED,LABEL,0}
		},
	WHITE,0};
	
	
	//显示窗口 
	window_show(Startwin);
	
	time_show(timectl);
	
	FlushBatchDraw();
	//窗口按键驱动 
	Startwin=window_run_with_time(Startwin,&timectl);	//有BUTTON控件的窗口需要窗口驱动函数 
	
	if(Startwin.current==0){
		winbk_flush();
		return 1;
		//客户选择“登录功能”，则返回0(登录界面函数在函数指针中的下标) 
	}else if(Startwin.current==1){
		//客户选择“忘记密码功能”，
		return  22;
	}else if(Startwin.current==2){
		//客户选择“退出功能”
		exit(1); 
	}else if(Startwin.current==-1){
		//左键防止程序崩溃 
		
		return 0; 
	}else if(Startwin.current==-2){
		//右键防止程序崩溃 
	
		return 0;
	} 
}

//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
int before_reset_pwd(){
	
	//输入窗口显示
	TIME_T timectl=time_control_init(480,20,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T win={150,200,500,400,7,
	{{210,210,250,50,"请输入任一管理员的账户与密码以获取权限",LIGHTCYAN,CYAN,RED,LABEL,0},
	{180,280,100,50,"账户:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{270,280,300,50,"",LIGHTCYAN,CYAN,RED,EDIT,1,1},
	{180,350,100,50,"密码:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{270,350,300,50,"",LIGHTCYAN,CYAN,RED,EDIT_PWD,0,1,0},
	{260,500,100,50,"继续",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{450,500,100,50,"返回",LIGHTCYAN,CYAN,RED,BUTTON,0}},WHITE,0};
	
	//加载窗口 
	winbk_flush();
	window_show(win);
	time_show(timectl);
	
	
	win=window_run_with_time(win,&timectl);
	
	char buf1[30]="";		//存储输入的账户 
	char buf2[30]="";		//存储输入的密码 
	int i,j;
	int flag=0;
	USER_T *user=NULL;
	//管理员角色链表 
	Lnode *adminlist=initlist();
	
	for(i=1;i<=getlistnodecount(userlist);i++){
		user=(USER_T *)findnode(userlist,i);
		
		if(user->role==1){
			insertAtTail(adminlist,user);
		}
		
	}
	
	
	if(win.current==5){
		//继续按钮 
		strcpy(buf1,win.controls[2].text);
		strcpy(buf2,win.controls[4].text);
		USER_T *p=NULL;
		USER_T *target=NULL;
		
	
		
		//未输入账户 
		if(strlen(buf1)==0&&strlen(buf2)!=0){
			CONTROL_T fail1={320,420,150,50,"请输入账户!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail1);
			
			Sleep(1500);
			return 22;
		}
		
		//未输入密码 
		if(strlen(buf1)!=0&&strlen(buf2)==0){
			CONTROL_T fail2={320,420,150,50,"请输入密码!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail2);
			
			Sleep(1500);
			return 22;
		}
		
		//账户与密码均未输入 
		if(strlen(buf1)==0&&strlen(buf2)==0){
			CONTROL_T fail3={300,420,200,50,"请输入账户与密码!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail3);
			
			Sleep(1500);
			return 22;
		}
		
		//寻找账户名是否存在 
		for(i=1;i<=getlistnodecount(userlist);i++){
			p=(USER_T *)findnode(userlist,i);
			
			if(strcmp(p->name,buf1)==0){
				target=p;
				break;
			}
		}
		
		//输入的账号不存在
		if(target==NULL){
			CONTROL_T fail4={320,420,150,50,"账户不存在!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail4);
			
			Sleep(1500);
			return 22;
		}
		
		
		//输入的账户非管理员身份 
		if(target->role!=1){
			CONTROL_T fail5={300,420,240,50,"输入的账户非管理员账户!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail5);
			
			Sleep(1500);
			return 22;		
		}
		
		//输入的密码错误
		
		if(strcmp(target->password,buf2)!=0){
			CONTROL_T fail6={320,420,150,50,"密码错误!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail6);
			
			Sleep(1500);
			return 22;
		} 
		
		
		

		
		CONTROL_T Success={320,420,150,50,"已获取权限!",LIGHTCYAN,CYAN,RED,BUTTON,0};
		control_show(Success);
		
		Sleep(1500);
		return 23;
	
	}else if(win.current==6){
		//返回上一级
		winbk_flush();
		return 0;
	}else if(win.current==-1){
		
		//左键防止程序崩溃
		return 22; 
	}else if(win.current==-2){
		
		//右键防止程序崩溃
		return 22; 
	}
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

//密码重置界面 
int reset_pwd(){
	
	//设计重置密码窗口
	TIME_T timectl=time_control_init(480,20,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T resetwin={150,200,500,500,9,
	{{300,210,150,50,"请输入账户与新密码",LIGHTCYAN,CYAN,RED,LABEL,0},
	{180,280,100,50,"账户:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{270,280,300,50,"",LIGHTCYAN,CYAN,RED,EDIT,1,1},
	{180,350,100,50,"新密码:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{270,350,300,50,"",LIGHTCYAN,CYAN,RED,EDIT_PWD,0,1,0},
	{150,430,100,50,"确认新密码:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{270,430,300,50,"",LIGHTCYAN,CYAN,RED,EDIT_PWD,0,1,0},
	{240,600,100,50,"修改",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{440,600,100,50,"返回",LIGHTCYAN,CYAN,RED,BUTTON,0}},
	WHITE,0}; 
	
	//加载窗口
	winbk_flush();
	
	window_show(resetwin);
	
	time_show(timectl);
	
	resetwin=window_run_with_time(resetwin,&timectl);
	
	int i,j;
	char buf1[50]="";		//存储输入的账户 
	char buf2[50]="";		//存储输入的密码 
	char buf3[50]="";		//存储输入的二次密码 
	
	if(resetwin.current==8){
		//返回
		winbk_flush();
		return  22;
	}else if(resetwin.current==7){
		
		//点击修改 
		strcpy(buf1,resetwin.controls[2].text);
		//用户输入账户 
		strcpy(buf2,resetwin.controls[4].text);
		//用户输入新密码 
		strcpy(buf3,resetwin.controls[6].text);
		//用户输入二次密码
		USER_T *p=NULL;
		USER_T *target=NULL; 
		int flag=1;
		if(strlen(buf1)==0||strlen(buf2)==0||strlen(buf3)==0){
			CONTROL_T fail={320,490,180,50,"请完善所有信息!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
			
			return 23;
		}
		
		//寻找目标账户 
		for(i=1;i<=getlistnodecount(userlist);i++){
			p=(USER_T *)findnode(userlist,i);
			
			if(strcmp(p->name,buf1)==0){
				target=p;
				break;
			}
		}
		
		//输入的账户不存在 
		if(!target){
			CONTROL_T fail1={320,490,180,50,"输入的账户不存在!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail1);
			
			Sleep(1500);
			return 23;			
		}
		
		//不允许修改管理员密码
		if(target->role==1){
			CONTROL_T fail2={320,490,200,50,"不允许修改管理员密码!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail2);
			
			Sleep(1500);
			return 23;
		} 
		
		
		//输入的密码不一致 
		if(strcmp(buf2,buf3)!=0){
			CONTROL_T fail3={320,490,180,50,"输入的密码不一致!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail3);
			
			Sleep(1500);
			return 23;
		}
		
		
		//检验输入的密码是否已存在
		for(i=1;i<=getlistnodecount(userlist);i++){
			p=(USER_T *)findnode(userlist,i);
			
			if(strcmp(p->password,buf2)==0){
				flag=0;
				break;
			}
		} 
		
		
		if(flag==0){
			CONTROL_T fail4={280,500,260,50,"密码已存在,请输入其他密码",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail4);
			Sleep(1500);
			
			return 23;
		}
		
		//重置密码 
		resetpwd_byname(userlist,buf1,buf2);
		
		//检验是否成功 
		if(strcmp(target->password,buf2)==0){
			FILE *fp=fopen("data/users.txt","wb");
			list_write_file(fp,sizeof(USER_T),userlist);
			fclose(fp);
			
			CONTROL_T Success={320,490,180,50,"密码已修改!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(Success);
			
			Sleep(1500);
			winbk_flush();
			return 0;
		}
		
		 
	}else if(resetwin.current==-1){
		
		//左键防止程序崩溃
		return 23;
	}else if(resetwin.current==-2){
		
		//右键防止程序崩溃
		return 23; 
	} 
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
