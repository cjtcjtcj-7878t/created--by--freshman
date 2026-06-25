#include"Adminwin.h"
#include"../View/control.h"
#include<graphics.h>
#include"../App/Loginwin.h"
#include"../App/data.h"
#include"../public/file.h"
#include"../public/commonlist.h"
#include"../public/file.h"
#include"../App/Goods.h"
#include"../View/myTiMe.h"
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<tchar.h>
#include<string.h>
///////////////////////////////////////
/*
该头文件用于管理员操作相关的函数 
*/ 
///////////////////////////////////////
extern Lnode *userlist;			//用户链表 
extern FILE *user_fp;			//用户文件 
extern Lnode *goodslist;		//货物链表 
extern FILE *goods_fp;			//货物文件 
extern Lnode *orderslist;		//订单链表 
extern FILE *orders_fp;			//订单文件

 
//extern int finished_count;		//已完成的订单数 
//extern int reject_count;		//驳回的顶单数
//extern int transing_count;		//运输中的订单数
//extern int wait_in_count;			//待入库订单数
//extern int wait_out_count;			//待出库订单数
//extern int wait_check_count;		//待审核订单数 
///////////////////////////////////////
int adminwin(){
	
	//绘制管理员界面窗口 
	TIME_T timectl=time_control_init(480,740,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T Adminwin={280,30,260,640,8,
	{{280,30,260,80,"1.系统管理",LIGHTCYAN,CYAN,RED,BUTTON,1},
	{280,110,260,80,"2.订单管理",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,190,260,80,"3.仓储管理",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,270,260,80,"4.运输管理",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,350,260,80,"5.统计分析",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,430,260,80,"6.客户服务",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,510,260,80,"7.密码修改",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,590,260,80,"8.返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0}},
	WHITE,0};
	//initgraph(800,800,EX_SHOWCONSOLE);
	IMAGE img;
	loadimage(&img,"image/image1.jpg",800,800);
	putimage(0,0,&img);
	
	setbkmode(TRANSPARENT);
	settextcolor(CYAN);
	
	CONTROL_T Note={250,690,100,50,"上下键进行选择,回车键进行确定",LIGHTCYAN,CYAN,RED,LABEL,
	0};
	control_show(Note);
	
	window_show(Adminwin);
	time_show(timectl);
	Adminwin=window_run_with_time(Adminwin,&timectl);//有BUTTON控件的窗口需要窗口驱动函数 
	
	if(Adminwin.current==7){
		//选择“返回上一级” 
		winbk_flush();
		return 1;
	
		
	}else if(Adminwin.current==6){
		//选择“密码修改” 
		return 26;
	}else if(Adminwin.current==5){
		//选择“客户服务” 
		
	}else if(Adminwin.current==4){
		//选择“统计分析” 
		return 20;
	}else if(Adminwin.current==3){
		//选择“运输管理” 
		
	}else if(Adminwin.current==2){
		//选择“仓储管理” 
		
	}else if(Adminwin.current==1){
		//选择“订单管理”
		return 10;   
	}else if(Adminwin.current==0){
		//选择“系统管理” 
		return 3;
	}else if(Adminwin.current==-1){
		
		//左键,防止程序崩溃
		return 2; 
	}else if(Adminwin.current==-2){
		
		//右键,防止程序崩溃
		 return 2;
	}
	
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

//在管理员界面选择"1.系统管理"
int adminwin_systemmanage(){
	//系统管理选择界面 
	TIME_T timectl=time_control_init(480,740,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T admin_system={280,30,260,640,8,{
	{280,30,260,80,"1.创建用户",LIGHTCYAN,CYAN,RED,BUTTON,1},
	{280,110,260,80,"2.用户查询",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,190,260,80,"3.密码重置",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,270,260,80,"4.角色管理",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,350,260,80,"5.仓库配置",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,430,260,80,"6.运输路线配置",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,510,260,80,"7.数据备份",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,590,260,80,"8.返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0}
	},WHITE,0};
	
	window_show(admin_system);
	time_show(timectl);
	admin_system=window_run_with_time(admin_system,&timectl);
	
	if(admin_system.current==0){
		return 4;
		//创建用户界面函数在函数指针的下标 
	}else if(admin_system.current==1){
		return 6;
		//用户查询界面函数在函数指针中的下标 
	}else if(admin_system.current==2){
		return 9;
	}else if(admin_system.current==3){
		
	}else if(admin_system.current==4){
		
	}else if(admin_system.current==5){
		
	}else if(admin_system.current==6){
		
	}else if(admin_system.current==7){
		winbk_flush();
		return 2;
	}else if(admin_system.current==-1){
		
		//左键，防止程序崩溃
		return 3;
	}else if(admin_system.current==-2){
		
		//右键,防止程序崩溃
		return 3; 
	}
	
} 
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
//在管理员/系统管理/创建用户时的创建界面 
int admin_adduserwin(){
	//创建用户界面 
	TIME_T timectl=time_control_init(480,20,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T adduser={280,100,250,250,8,{
	{280,100,100,50,"账户:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{280,160,100,50,"密码:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{350,100,150,50,"",LIGHTCYAN,CYAN,RED,EDIT,1,1},
	{350,160,150,50,"",LIGHTCYAN,CYAN,RED,EDIT_PWD,0,0,0},
	{280,220,100,50,"角色:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{350,220,150,50,"请选择数据,管理员,仓储员,调度员,客服",LIGHTCYAN,CYAN,RED,SELECT,0},
	{290,280,100,50,"创建",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{410,280,100,50,"返回",LIGHTCYAN,CYAN,RED,BUTTON,0}
	},WHITE,0};  
	
	//加载背景 
	winbk_flush();
	
	window_show(adduser);
	time_show(timectl);
	role_show();
	adduser=window_run_with_time(adduser,&timectl);
	
	
	if(adduser.current==6){
		//选择创建按钮 
		//创建链表结点 
		int i;
		USER_T *p=NULL;
	    p=(USER_T *)malloc(sizeof(USER_T));
		memset(p,0,sizeof(USER_T));
		
		
		if(strlen(adduser.controls[2].text)==0){
			//账户不能为空 
			
			if(strlen(adduser.controls[2].text)==0&&strlen(adduser.controls[3].text)==0){
			    CONTROL_T fail={320,380,240,80,"账户或密码不能为空!",LIGHTCYAN,CYAN,RED,BUTTON,0};
				control_show(fail);
				Sleep(1500);
				
				return 4;
			}
			CONTROL_T fail1={320,380,220,80,"账户不能为空!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail1);
			Sleep(1500);
		
			return 4;  
		}
		if(strlen(adduser.controls[3].text)==0){
			//密码不能为空 
			
			if(strlen(adduser.controls[2].text)==0&&strlen(adduser.controls[3].text)==0){
				CONTROL_T fail={320,380,240,80,"账户或密码不能为空!",LIGHTCYAN,CYAN,RED,BUTTON,0};
				control_show(fail);
				Sleep(1500);
				
				return 4;
			} 
			CONTROL_T fail2={320,380,220,80,"密码不能为空!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail2);
			Sleep(1500);
			
			return 4;
		}
		if(strcmp(adduser.controls[5].text,"请选择数据")==0||strchr(adduser.controls[5].text,',')!=NULL){
			//用户角色不能为空 
			CONTROL_T fail3={320,380,220,80,"请选择有效角色!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail3);
			Sleep(1500);
			
			return 4;
		}
		for(i=1;i<=getlistnodecount(userlist);i++){
			//遍历已有用户数据,核验待创建用户是否已存在,已存在则不允许创建 
			USER_T *T=NULL;
			T=(USER_T *)malloc(sizeof(USER_T));
			memset(T,0,sizeof(USER_T));
			T=(USER_T *)findnode(userlist,i);
			
			if(strcmp(adduser.controls[2].text,T->name)==0){
				CONTROL_T fail={320,380,220,80,"该用户已存在,无法创建!",LIGHTCYAN,CYAN,RED,BUTTON,0};
				control_show(fail);
				
				Sleep(1500);
				
				return 4;
				
			}
		}
		//ID自动生成 
		sprintf(p->ID,"%d",1000+getlistnodecount(userlist));	//角色ID自动生成 
		strcpy(p->name,adduser.controls[2].text);		
		strcpy(p->password,adduser.controls[3].text);	 
//		
//		for(i=1;i<getlistnodecount(userlist);i++){
//			//遍历已有用户数据,核验待创建用户是否已存在,已存在则不允许创建 
//			USER_T *T=NULL;
//			T=(USER_T *)malloc(sizeof(USER_T));
//			memset(T,0,sizeof(USER_T));
//			T=(USER_T *)findnode(userlist,i);
//			
//			if(strcmp(adduser.controls[2].text,T->name)==0){
//				CONTROL_T fail={340,330,150,50,"该用户已存在,无法创建!",LIGHTCYAN,CYAN,RED,BUTTON,0};
//				control_show(fail);
//				
//				Sleep(1500);
//				
//				return 4;
//				
//			}
//		}
		//根据注册的用户角色分配身份
		if(strcmp(adduser.controls[5].text,"管理员")==0){
			p->role=1;
		}else if(strcmp(adduser.controls[5].text,"仓储员")==0){
			p->role=2;
		}else if(strcmp(adduser.controls[5].text,"调度员")==0){
			p->role=3;
		}else if(strcmp(adduser.controls[5].text,"客服")==0){
			p->role=4;
		} 
						//1表示管理员角色,2表示仓储员,3表示调度员,4表示客服
						 
		p->state=1;			//1表示角色状态可用,0为不可用 
	
		insertAtTail(userlist,p);	//将新用户结点插入到用户链表尾部 
		
		file_add(user_fp,sizeof(USER_T),p);
		
		//弹窗提示
		CONTROL_T Successwin={340,330,100,50,"创建成功!",LIGHTCYAN,CYAN,RED,BUTTON,0}; 
		
		control_show(Successwin);
		
		Sleep(1500);
		
		return 3;
	}else if(adduser.current==7){
		//选择“返回”按钮 
		winbk_flush();
		return 3;
	}else if(adduser.current==-1){
		
		//左键，防止程序崩溃
		return 4;
	}else if(adduser.current==-2){
		
		//右键，防止程序崩溃
		return 4; 
	}
	
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
		//在管理员选择界面选择"2.订单管理"所呈现的界面 
int adminwin_ordermanage(){
	//订单管理界面窗口 
	TIME_T timectl=time_control_init(480,740,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T orderwin={280,30,260,480,6,
	{{280,30,260,80,"1.创建订单",LIGHTCYAN,CYAN,RED,BUTTON,1},
	{280,110,260,80,"2.订单审核",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,190,260,80,"3.订单查询",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,270,260,80,"4.订单修改",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,350,260,80,"5.订单跟踪",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,430,260,80,"6.返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0}},
	WHITE,0}; 
	
	//加载背景
	winbk_flush();
	
	//显示窗口
	window_show(orderwin);
	time_show(timectl);
	//窗口按钮驱动 
	orderwin=window_run_with_time(orderwin,&timectl); 
	
	if(orderwin.current==0){
		//创建订单 
		return 11;
	}else if(orderwin.current==1){
		//订单审核 
		return 13;
	}else if(orderwin.current==2){
		//订单查询 
		return 12;
	}else if(orderwin.current==3){
		//订单修改
		return 24; 
	}else if(orderwin.current==4){
		//订单跟踪
		return 25; 
	}else if(orderwin.current==5){
		//返回上一级 
		winbk_flush();
		return 2;
	}else if(orderwin.current==-1){
		
		//左键，防止程序崩溃
		return 10; 
		 
	}else if(orderwin.current==-2){
		
		//右键，防止程序崩溃 
		return 10;
	}
}
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
int admin_researchuserwin(){
	
	//查询窗口
	TIME_T timectl=time_control_init(480,20,300,50,1000,TIME_FORMAT_FULL); 
	WINDOW_T researchwin={180,190,470,400,4,
	{{190,200,100,50,"用户搜索:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{300,200,180,50,"",LIGHTCYAN,CYAN,RED,EDIT,1,1},
	{530,200,100,50,"查询",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{350,600,150,50,"返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0}},
	WHITE,0};
	
	
	//加载背景
	winbk_flush();
	 
	window_show(researchwin);
	time_show(timectl);
	//初始化表格结构体 
	TABLE_T table={185,260,460,270,6,4,{"ID","姓名","角色","状态"}};
	static int pagenow=1;	//进入表格时呈现的初始页面,1表示第一页，2表示第二页 
	int pagecount=5;	//每一页展现的数据行数,3表示每页展示3行数据（首行不算）  
	int count=getlistnodecount(userlist);		//用户链表中的结点个数(不包含头结点) 
	static int pagenum=count%pagecount==0?count/pagecount:count/pagecount+1;
	//页面总数,与用户个数和每页展现的数据行数有关
	
	//初始化一条静态链表保存查询数据
	static Lnode *templist=initlist();
	
	 
	char roles[5][20]={"0","管理员","仓储员","调度员","客服"};
	char state[2][10]={"不可用","可用"};
	static char buf[20]={0};
	int i,j;

	int start;	//每一页表格的起始序号
	USER_T *p=NULL; 
	//1.全部查询(未在搜索框输入条件) 
	
	if(strlen(buf)==0){
		//1.全部查询(未在搜索框输入条件) 
		
		//memset(table.data,0,sizeof(table.data));
		count=getlistnodecount(userlist);
		//表格总行数(每一页行数累加,不记首行) 
		pagenum=count%pagecount==0?count/pagecount:(count/pagecount)+1;
		//表格总页数 
		start=(pagenow-1)*pagecount;	//每一页表格的起始序号(0也算)
		
		memset(table.data,0,sizeof(table.data));
		for(i=1;i<=pagecount;i++){
			
			if(start+i>count){	//当用户数据不足一页表格 
				break;
			}
			
			p=(USER_T *)findnode(userlist,start+i);
			j=0;
			strcpy(table.data[i-1][j],p->ID);
			strcpy(table.data[i-1][++j],p->name);
			strcpy(table.data[i-1][++j],roles[p->role]);
			strcpy(table.data[i-1][++j],state[p->state]);
			
			
		}
		 
	}else{
		//2.条件查询(在搜索框输入相关条件进行查询) 
		int count2;	
		//memset(table.data,0,sizeof(table.data));
		count2=getlistnodecount(templist);
		//表格总行数(每一页行数累加,不记首行) 
		pagenum=count2%pagecount==0?count2/pagecount:(count2/pagecount)+1;
		//表格总页数 
		start=(pagenow-1)*pagecount;	//每一页表格的起始序号(0也算)
		
		memset(table.data,0,sizeof(table.data));
		for(i=1;i<=count2;i++){
			
			if(start+i>count2){	//当用户数据不足一页表格 
				break;
			}
			
			p=(USER_T *)findnode(templist,start+i);
			j=0;
			strcpy(table.data[i-1][j],p->ID);
			strcpy(table.data[i-1][++j],p->name);
			strcpy(table.data[i-1][++j],roles[p->role]);
			strcpy(table.data[i-1][++j],state[p->state]);
			
		
	}
}
	
	

	//测试表格内容是否正常显示
	 
//	for(i=0;i<5;i++){
//		j=0;
//		strcpy(table.data[i][j++],"1001");
//		strcpy(table.data[i][j++],"LiLi");
//		strcpy(table.data[i][j++],roles[1]);
//		strcpy(table.data[i][j++],state[1]);
//	}
	//显示表格
	
	if(getlistnodecount(templist)==0){
		pagenum=1;
	}
	
	
	table_show(table,pagenow,pagenum); 
	
	strcpy(buf,researchwin.controls[1].text);
	
	//窗口驱动 
	researchwin=window_run_with_time(researchwin,&timectl);
	
	if(researchwin.current==2){
		
		if(strlen(researchwin.controls[1].text)>0){
			strcpy(buf,researchwin.controls[1].text);
			
			//freelist
			freelist(templist);
			
			templist=initlist();
			
			for(i=1;i<=getlistnodecount(userlist);i++){
				p=(USER_T *)findnode(userlist,i);
				//精确查询与模糊查询 
				if(strstr(p->name,buf)!=NULL){
					insertAtTail(templist,p);
					//插入临时链表 
				}
				
			}
			
		}else{
			memset(buf,0,sizeof(buf));
		}
		return 6;
		
	}
	//翻页功能 
	else if(researchwin.current==-1){
		//左键向上翻页 
		if(pagenow>1){	//防止一直向上翻页导致当前页数溢出 
			pagenow--;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是第一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			
			Sleep(1500);
		}
		return 6;
	}else if(researchwin.current==-2){
		//右键向下翻页
		if(pagenow<pagenum){
			pagenow++;	//防止一直向下翻页导致当前页数溢出 
		}else{
			CONTROL_T fail={350,380,150,50,"已经是最后一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			
			
			Sleep(1500);
		}
		return 6; 
		 
	}else if(researchwin.current==3){
		winbk_flush();
		return 3;
	}

}

////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
int admin_pwdreset(){
	//在管理员选择界面选择"3.密码重置"
	
	//重置窗口
	TIME_T timectl=time_control_init(480,20,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T reset={280,100,280,320,3,{
	{320,200,200,50,"",LIGHTCYAN,CYAN,RED,EDIT,1,1},
	{370,280,100,50,"重置",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{358,350,120,50,"返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0}},
	WHITE,0
	};
	int flag=0;		//判断目标账户是否存在 
	//加载背景 
	winbk_flush();
	//显示窗口 
	window_show(reset);
	time_show(timectl);
	outtextxy(340,130,"请输入待重置的账户");
	//窗口按键驱动 
	reset=window_run_with_time(reset,&timectl);
	int i;
	USER_T *p=NULL;		//临时结点 
	if(reset.current==1){
		
		char buf[20]="0";
		strcpy(buf,reset.controls[0].text);
		if(strlen(reset.controls[0].text)==0){
			CONTROL_T fail1={340,240,170,50,"目标账户不能为空!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail1);
			Sleep(1500);
			
			return 9;
		}
		for(i=1;i<=getlistnodecount(userlist);i++){
			//遍历用户链表查找输入的账户是否存在 
		
			p=(USER_T *)findnode(userlist,i);		//遍历已有用户链表的结点 
			if(strcmp(p->name,buf)==0){
				flag=1;
				break;
			}
		}
			
				
		if(flag==1){ 
		
				char newpwd[20]="666";	//重置的密码 
				resetpwd_byname(userlist,reset.controls[0].text,newpwd);
				USER_T *T=NULL;
				
				T=(USER_T *)findnode(userlist,i);	//临时结点指针指向重置的结点 
				if(strcmp(T->password,newpwd)==0){
					//检验是否成功重置密码 
					FILE *fp=fopen("data/users.txt","wb");	//将新数据保存到文件中 
					list_write_file(fp,sizeof(USER_T),userlist);
					fclose(fp);
					CONTROL_T Success={340,240,150,50,"密码已重置为666",LIGHTCYAN,CYAN,RED,BUTTON,0};
					control_show(Success);
					Sleep(1500);
					
					
					if(T->role==1){
						winbk_flush(); 
						return 1;
					}
					
					return 9  ;
				}else{
					CONTROL_T fail3={340,240,100,50,"重置失败!",LIGHTCYAN,CYAN,RED,BUTTON,0};
					control_show(fail3);
					Sleep(1500);
					
					return 9;
				}  
		}else{
			CONTROL_T fail2={340,240,170,50,"目标账户不存在!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail2);		//未找到目标用户提示 
			Sleep(1500);
			
			return 9;
		}
		
	}else if(reset.current==2){
			//返回上一级 
			winbk_flush();
			return 3;
		}else if(reset.current==-1){
			
			//左键，防止程序崩溃
			return 9; 
		}else if(reset.current==-2){
			//右键，防止程序崩溃
			return 9; 
		}
	
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//统计分析功能 
int admin_statis(){
	//设计窗口
	TIME_T timectl=time_control_init(400,20,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T statiswin={20,50,750,700,4,
	{{50,90,100,50,"今日",LIGHTCYAN,CYAN,RED,BUTTON,1},
	{160,90,100,50,"本周",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{270,90,100,50,"本月",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{300,680,150,50,"返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0}},WHITE,0};
	
	//加载背景
	winbk_flush();
	window_show(statiswin);
	time_show(timectl);
	char buf1[100]="==============================订单统计结果=============================="; 
	outtextxy(30,160,buf1);
	
	time_t now=time(NULL);
	struct tm *local=localtime(&now);
	//今日时间
	char time1[50]="";
	sprintf(time1,"%d--%d--%d",local->tm_year+1900,local->tm_mon+1,local->tm_mday);
	char today1[50]="";
	sprintf(today1,"%d%02d%02d",local->tm_year+1900,local->tm_mon+1,local->tm_mday);
	                         //本周时间范围 
	                          
	char time2[50]="";
	struct tm today=*localtime(&now);
	int weekday=today.tm_wday;
	int days_from_monday=(weekday==0)?6:weekday-1;
	
	//起始时期范围 
	time_t monday_time=now-days_from_monday*86400;
	struct tm mon=*localtime(&monday_time);
	
	//终末时期范围 
	time_t sunday_time=monday_time+6*86400;
	struct tm sun=*localtime(&sunday_time); 
	
	sprintf(time2,"%d--%d--%d~~%d--%d--%d",mon.tm_year+1900,mon.tm_mon+1,mon.tm_mday,sun.tm_year+1900,sun.tm_mon+1,sun.tm_mday);
	char time2_start[50]="";		//本周时间范围的起点
	char time2_end[50]="";			//本周时间范围的终点 
	
	sprintf(time2_start,"%d%02d%02d",mon.tm_year+1900,mon.tm_mon+1,mon.tm_mday);
	//订单时间的统计格式 
	sprintf(time2_end,"%d%02d%02d",sun.tm_year+1900,sun.tm_mon+1,sun.tm_mday); 
	                         //本月时间范围 
	char time3[50]="";
	
	int days_in_month[]={31,28,31,30,31,30,31,31,30,31,30,31};
	int year=today.tm_year+1900;
	int month=today.tm_mon+1;
	
	int is_leap=(year%4==0&&year%100!=0)||(year%400==0);
	if(month==2&&is_leap){
		days_in_month[1]=29;
	}
	
	sprintf(time3,"%d--%d--%d~~%d--%d--%d",year,month,1,
	year,month,days_in_month[month-1]);
	
	char time3_start[50]="";		//本月时间范围起点
	char time3_end[50]="";			//本月时间范围终点 
	sprintf(time3_start,"%d%02d%02d",year,month,1);
	//订单时间的统计格式 
	sprintf(time3_end,"%d%02d%02d",year,month,days_in_month[month-1]);
	//////////////////////////////////////////////////////////
	char buf[30]=""; 
	char step[2]="|";
	char type[5][10]={"普通类","冷链","易碎","危险品"};
	//窗口驱动
	statiswin=window_run_with_time(statiswin,&timectl); 
	if(statiswin.current==0){
		//统计当天的订单信息 
//		char buf[30]=""; 
//		char step[2]="|";
//		char type[5][10]={"普通类","冷链","易碎","危险品"};
		
		//另起窗口显示订单信息 
		WINDOW_T detailwin={20,50,750,700,1,{{340,680,100,50,"返回",LIGHTCYAN,CYAN,RED,BUTTON,1}},
		WHITE,0};
		
		winbk_flush();
		window_show(detailwin);
		time_show(timectl);
		char buf1[100]="==============================订单统计结果=============================="; 
		//显示信息
		 
		outtextxy(30,160,buf1);
		outtextxy(330,100,time1);
		
		sprintf(buf,"总订单数: %d",countOrderByTime(today1,today1,-1));
		outtextxy(60,220,buf);
		outtextxy(200,220,step);
		
		sprintf(buf,"已完成订单数: %d",countOrderByTime(today1,today1,4));
		outtextxy(320,220,buf);
		outtextxy(490,220,step);
		
		sprintf(buf,"订单完成率: %.2f%%",getFinishRate(today1,today1,4));
		outtextxy(580,220,buf);
		outtextxy(760,220,step);
		
		sprintf(buf,"驳回订单数: %d",countOrderByTime(today1,today1,5));
		outtextxy(55,300,buf);
		outtextxy(200,300,step);
		
		sprintf(buf,"驳回率: %.2f%%",getFinishRate(today1,today1,5));
		outtextxy(315,300,buf);
		outtextxy(460,300,step);
		
		sprintf(buf,"运输中订单数: %d",countOrderByTime(today1,today1,3));
		outtextxy(575,300,buf);
		outtextxy(740,300,step); 
		
		
		outtextxy(70,390,"按货物类型统计");
		
		sprintf(buf,"普通货物: %d",countOrderByTypeAndTime(today1,today1,type[0]));
		outtextxy(50,480,buf);
		outtextxy(215,480,step);
		
		sprintf(buf,"易碎货物: %d",countOrderByTypeAndTime(today1,today1,type[2]));
		outtextxy(310,480,buf);
		outtextxy(475,480,step);
		
		sprintf(buf,"冷链货物: %d",countOrderByTypeAndTime(today1,today1,type[1]));
		outtextxy(50,600,buf);
		outtextxy(215,600,step);
		
		sprintf(buf,"危险品: %d",countOrderByTypeAndTime(today1,today1,type[3]));
		outtextxy(310,600,buf);
		outtextxy(475,600,step);
		
		//显示信息 
		
		//窗口驱动 
		detailwin=window_run_with_time(detailwin,&timectl);
		if(detailwin.current==0){
			//返回 
			winbk_flush();
			return 20;
		}
	}else if(statiswin.current==1){
		//统计本周订单数据
		 
		//另起窗口显示信息
		WINDOW_T detailwin={20,50,750,700,1,{{340,680,100,50,"返回",LIGHTCYAN,CYAN,RED,BUTTON,1}},
		WHITE,0};
		
		winbk_flush();
		window_show(detailwin);
		time_show(timectl);
		char buf1[100]="==============================订单统计结果=============================="; 
		//显示信息
		 
		outtextxy(30,160,buf1);
		outtextxy(280,100,time2);
		
		sprintf(buf,"总订单数: %d",countOrderByTime(time2_start,time2_end,-1));
		outtextxy(60,220,buf);
		outtextxy(200,220,step);
		
		sprintf(buf,"已完成订单数: %d",countOrderByTime(time2_start,time2_end,4));
		outtextxy(320,220,buf);
		outtextxy(490,220,step);
		
		sprintf(buf,"订单完成率: %.2f%%",getFinishRate(time2_start,time2_end,4));
		outtextxy(580,220,buf);
		outtextxy(760,220,step);
		
		sprintf(buf,"驳回订单数: %d",countOrderByTime(time2_start,time2_end,5));
		outtextxy(55,300,buf);
		outtextxy(200,300,step);
		
		sprintf(buf,"驳回率: %.2f%%",getFinishRate(time2_start,time2_end,5));
		outtextxy(315,300,buf);
		outtextxy(460,300,step);
		
		sprintf(buf,"运输中订单数: %d",countOrderByTime(time2_start,time2_end,3));
		outtextxy(575,300,buf);
		outtextxy(740,300,step); 
		
		
		outtextxy(70,390,"按货物类型统计");
		
		sprintf(buf,"普通货物: %d",countOrderByTypeAndTime(time2_start,time2_end,type[0]));
		outtextxy(50,480,buf);
		outtextxy(215,480,step);
		
		sprintf(buf,"易碎货物: %d",countOrderByTypeAndTime(time2_start,time2_end,type[2]));
		outtextxy(310,480,buf);
		outtextxy(475,480,step);
		
		sprintf(buf,"冷链货物: %d",countOrderByTypeAndTime(time2_start,time2_end,type[1]));
		outtextxy(50,600,buf);
		outtextxy(215,600,step);
		
		sprintf(buf,"危险品: %d",countOrderByTypeAndTime(time2_start,time2_end,type[3]));
		outtextxy(310,600,buf);
		outtextxy(475,600,step);
		
		//显示信息 
		
		//窗口驱动 
		detailwin=window_run_with_time(detailwin,&timectl);
		if(detailwin.current==0){
			//返回 
			winbk_flush();
			return 20;
		}
	}else if(statiswin.current==2){
		//本月时间范围订单数据
		
		//另起窗口显示信息
			WINDOW_T detailwin={20,50,750,700,1,{{340,680,100,50,"返回",LIGHTCYAN,CYAN,RED,BUTTON,1}},
		WHITE,0};
		
		winbk_flush();
		window_show(detailwin);
		time_show(timectl);
		char buf1[100]="==============================订单统计结果=============================="; 
		//显示信息
		 
		outtextxy(30,160,buf1);
		outtextxy(280,100,time3);
		
		sprintf(buf,"总订单数: %d",countOrderByTime(time3_start,time3_end,-1));
		outtextxy(60,220,buf);
		outtextxy(200,220,step);
		
		sprintf(buf,"已完成订单数: %d",countOrderByTime(time3_start,time3_end,4));
		outtextxy(320,220,buf);
		outtextxy(490,220,step);
		
		sprintf(buf,"订单完成率: %.2f%%",getFinishRate(time3_start,time3_end,4));
		outtextxy(580,220,buf);
		outtextxy(760,220,step);
		
		sprintf(buf,"驳回订单数: %d",countOrderByTime(time3_start,time3_end,5));
		outtextxy(55,300,buf);
		outtextxy(200,300,step);
		
		sprintf(buf,"驳回率: %.2f%%",getFinishRate(time3_start,time3_end,5));
		outtextxy(315,300,buf);
		outtextxy(460,300,step);
		
		sprintf(buf,"运输中订单数: %d",countOrderByTime(time3_start,time3_end,3));
		outtextxy(575,300,buf);
		outtextxy(740,300,step); 
		
		
		outtextxy(70,390,"按货物类型统计");
		
		sprintf(buf,"普通货物: %d",countOrderByTypeAndTime(time3_start,time3_end,type[0]));
		outtextxy(50,480,buf);
		outtextxy(215,480,step);
		
		sprintf(buf,"易碎货物: %d",countOrderByTypeAndTime(time3_start,time3_end,type[2]));
		outtextxy(310,480,buf);
		outtextxy(475,480,step);
		
		sprintf(buf,"冷链货物: %d",countOrderByTypeAndTime(time3_start,time3_end,type[1]));
		outtextxy(50,600,buf);
		outtextxy(215,600,step);
		
		sprintf(buf,"危险品: %d",countOrderByTypeAndTime(time3_start,time3_end,type[3]));
		outtextxy(310,600,buf);
		outtextxy(475,600,step);
		
		//显示信息 
		
		//窗口驱动 
		detailwin=window_run_with_time(detailwin,&timectl);
		if(detailwin.current==0){
			//返回 
			winbk_flush();
			return 20;
		} 
	}else if(statiswin.current==3){
		//返回上一级
		winbk_flush();
		return 2;
	}else if(statiswin.current==-1){
		
		//左键，防止程序崩溃
		return 20; 
	}else if(statiswin.current==-2){
		
		//右键，防止程序崩溃
		return 20; 
	}
}
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////

int admin_orderchange(){
	//设计显示窗口
	TIME_T timectl=time_control_init(460,20,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T orderwin={20,70,750,700,5,
	{{320,75,100,50,"管理员订单修改",LIGHTCYAN,CYAN,RED,LABEL,0},
	{500,700,100,50,"返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{150,700,180,50,"",LIGHTCYAN,CYAN,RED,EDIT,1,1,0},
	{50,700,150,50,"订单编号:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{350,700,100,50,"查看详情",LIGHTCYAN,CYAN,RED,BUTTON,0}},
	WHITE,0};  
	
	int i,j;
	
	//
	Order_T *order=NULL;
	Order_T *p=NULL;
	Lnode *checklist=initlist();
	
	//创建链表，存放待审核订单 
	for(i=1;i<=getlistnodecount(orderslist);i++){
		order=(Order_T *)findnode(orderslist,i);
		
		if(order->role==0){
			insertAtTail(checklist,order);
		}
	}
	
	//加载背景
	winbk_flush();
	window_show(orderwin); 
	time_show(timectl);
	
	//设计表格
	TABLE_T table={90,130,600,500,6,3,{"订单编号","客户姓名","订单状态"}}; 
	memset(table.data,0,sizeof(table.data));
	int pagecount=5;		//每页展示五条订单
	static int pagenow=1;
	int count=getlistnodecount(orderslist);		//总订单数 
	
	//表格总页面 
	int pagenum=getlistnodecount(checklist)%pagecount==0?getlistnodecount(checklist)/pagecount:
	(getlistnodecount(checklist)/pagecount)+1;	
	
	int start=(pagenow-1)*pagecount;
	int row=0;
	
	for(i=1;i<=pagecount;i++){
		p=(Order_T *)findnode(checklist,i+start);
		
		j=0;
		if(start+i>getlistnodecount(checklist)){
			break;
		}
		strcpy(table.data[row][j],p->order_id);
		strcpy(table.data[row][++j],p->client_name);
		strcpy(table.data[row][++j],p->state);
		row++;
	}
	
	if(getlistnodecount(checklist)==0){
		pagenum=1;
	}
	
	//显示表格 
	table_show(table,pagenow,pagenum);
	
	orderwin=window_run_with_time(orderwin,&timectl);
	char buf[50]="";		//存储输入的订单编号 
	if(orderwin.current==1){
		//返回上一级
		winbk_flush();
		return 10; 
	}else if(orderwin.current==4){
		//查看详情
		int flag=0;
		int found=0;
		Order_T *T=NULL;
		strcpy(buf,orderwin.controls[2].text);
		//未输入订单编号 
		if(strlen(buf)==0){
			CONTROL_T fail1={350,380,150,50,"请输入订单号!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail1);
			Sleep(1500);
			return 24;
		}
		
		//订单是否存在
		for(i=1;i<=getlistnodecount(orderslist);i++){
			T=(Order_T *)findnode(orderslist,i);
			
			if(strcmp(T->order_id,buf)==0){
				found=1;
			}
		}
		
		//订单不存在 
		if(found==0){
			CONTROL_T fail2={350,380,150,50,"订单不存在!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail2);
			
			Sleep(1500);
			return 24;
		} 
		//订单允许修改 
		for(i=1;i<=getlistnodecount(checklist);i++){
			T=(Order_T *)findnode(checklist,i);
			
			if(strcmp(T->order_id,buf)==0){
				flag=1;
				if(T->role!=0){
					CONTROL_T fail2={350,380,250,50,"该订单已通过审核不允许修改!",LIGHTCYAN,CYAN,RED,BUTTON,0};
					control_show(fail2);
					
					Sleep(1500);
					return 24;				
				}
				
				//另起窗口展示信息
				
				WINDOW_T printwin={20,70,750,700,3,
				{{320,75,100,50,"订单详细信息",LIGHTCYAN,CYAN,RED,LABEL,0},
				{200,700,150,50,"修改",LIGHTCYAN,CYAN,RED,BUTTON,1},
				{460,700,150,50,"返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0}},
				WHITE,0};
				 
				winbk_flush();
				window_show(printwin);
				time_show(timectl);
				char buf[50]={0};
				
				//信息显示 
				sprintf(buf,"订单编号:%s",T->order_id);
				outtextxy(240,115,buf);
				
				sprintf(buf,"客户姓名:%s",T->client_name);
				outtextxy(240,175,buf);
				
				sprintf(buf,"客户电话:%s",T->phonenum);
				outtextxy(240,235,buf);
				
				sprintf(buf,"货物名称:%s",T->goods_name);
				outtextxy(240,295,buf);
				
				sprintf(buf,"货物类型:%s",T->type);
				outtextxy(240,355,buf);
				
				sprintf(buf,"货物重量:%s",T->weight);
				outtextxy(240,415,buf);
				
				sprintf(buf,"货物数量:%s",T->goods_count);
				outtextxy(240,475,buf);
				
				sprintf(buf,"发货地址:%s",T->send_location);
				outtextxy(240,535,buf);
				
				sprintf(buf,"收获地址:%s",T->receive_location);
				outtextxy(240,595,buf);
				
				sprintf(buf,"订单状态:%s",T->state);
				outtextxy(240,655,buf);
				
				//信息显示 
				printwin=window_run_with_time(printwin,&timectl); 
				
				if(printwin.current==2){
					//返回上一级
					winbk_flush();
					return 24; 
				}else if(printwin.current==1){
					//进行修改
					//另起窗口
					WINDOW_T orderchange={150,5,500,720,25,{
					{280,5,100,50,"订单编号:",LIGHTCYAN,CYAN,RED,LABEL,0,0},
					{380,5,100,50,"",LIGHTCYAN,CYAN,RED,LABEL,0,0},
					{150,50,100,50,"客户姓名:",LIGHTCYAN,CYAN,RED,LABEL,0,0},
					{250,55,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,1,1},
					{150,110,100,50,"联系电话:",LIGHTCYAN,CYAN,RED,LABEL,0,0},
					{250,115,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
					{150,170,100,50,"客户地址:",LIGHTCYAN,CYAN,RED,LABEL,0,0},
					{250,175,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
					{150,230,100,50,"货物名称:",LIGHTCYAN,CYAN,RED,LABEL,0,0},
					{250,235,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
					{150,290,100,50,"货物类型:",LIGHTCYAN,CYAN,RED,LABEL,0,0},
					{250,290,390,50,"请选择数据,普通类,易碎,冷链类,危险品",LIGHTCYAN,CYAN,RED,SELECT,0,0},
					{150,350,100,50,"货物重量:",LIGHTCYAN,CYAN,RED,LABEL,0,0},
					{250,355,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
					{150,410,100,50,"货物数量:",LIGHTCYAN,CYAN,RED,LABEL,0,0},
					{250,415,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
					{150,470,100,50,"货物体积:",LIGHTCYAN,CYAN,RED,LABEL,0,0},
					{250,475,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
					{150,530,100,50,"发货地址:",LIGHTCYAN,CYAN,RED,LABEL,0,0},
					{250,535,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
					{150,590,100,50,"收获地址:",LIGHTCYAN,CYAN,RED,LABEL,0,0},
					{250,595,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
					{255,660,100,50,"保存",LIGHTCYAN,CYAN,RED,BUTTON,0,0},
					{445,660,100,50,"返回",LIGHTCYAN,CYAN,RED,BUTTON,0,0}},WHITE,0}; 
	 				
	 				
	 				//显示订单的信息
					strcpy(orderchange.controls[1].text,T->order_id);
					strcpy(orderchange.controls[3].text,T->client_name);
					strcpy(orderchange.controls[5].text,T->phonenum);
					strcpy(orderchange.controls[7].text,T->client_location);
					strcpy(orderchange.controls[9].text,T->goods_name);
					
					strcpy(orderchange.controls[11].text,T->type);
					strcpy(orderchange.controls[13].text,T->weight);
					strcpy(orderchange.controls[15].text,T->goods_count);
					strcpy(orderchange.controls[17].text,T->volumn);
					strcpy(orderchange.controls[19].text,T->send_location);
					strcpy(orderchange.controls[21].text,T->receive_location);
					
					 
	 				
	 				//
	 				winbk_flush();
	 				window_show(orderchange);
	 				time_show(timectl);
	 				orderchange=window_run_with_time(orderchange,&timectl);
	 				
	 				if(orderchange.current==23){
	 					//返回
						 winbk_flush();
						 return 24; 
					 }else if(orderchange.current==22){
					 	//保存修改
						 
						 strcpy(T->client_name,orderchange.controls[3].text);
						 strcpy(T->phonenum,orderchange.controls[5].text);
						 strcpy(T->client_location,orderchange.controls[7].text);
						 strcpy(T->goods_name,orderchange.controls[9].text);
						 
						 strcpy(T->type,orderchange.controls[11].text);
						 strcpy(T->weight,orderchange.controls[13].text);
						 strcpy(T->goods_count,orderchange.controls[15].text);
						 strcpy(T->volumn,orderchange.controls[17].text);
						 strcpy(T->send_location,orderchange.controls[19].text);
						 strcpy(T->receive_location,orderchange.controls[21].text);
						  
						  
						//保存到文件中
						FILE *fp=fopen("data/orders.txt","wb");
						
						int count=getlistnodecount(orderslist);
						Order_T *order=NULL;
						
						for(i=1;i<=count;i++){
							order=(Order_T *)findnode(orderslist,i);
							fwrite(order,sizeof(Order_T),1,fp);
							
							
						}
						
						fclose(fp);
						
						CONTROL_T success={350,380,150,50,"修改成功!",LIGHTCYAN,CYAN,RED,BUTTON,0};
						control_show(success);
						
						Sleep(1500);
						return 24;						 
						
					 }
				}
			}
		}
		
		if(flag==0){
			CONTROL_T fail={300,380,280,50,"该订单已通过审核不允许修改!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			
			Sleep(1500);
			return 24;			
		}
		
		
	}else if(orderwin.current==-1){
		//左键向上翻页
		if(pagenow>1){
			pagenow--;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是第一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 24; 
	}else if(orderwin.current==-2){
		//右键向下翻页 
		if(pagenow<pagenum){
			pagenow++;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是最后一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 24;
	} 
	
	
	
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////

int admin_ordertrack(){
	//设计窗口
		
	//查询窗口
	TIME_T timectl=time_control_init(460,20,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T ordertrack={20,70,750,600,6,
	{{25,90,100,50,"订单编号:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{125,90,180,50,"",LIGHTCYAN,CYAN,RED,EDIT,1,1},
	{305,90,100,50,"客户姓名:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{405,90,180,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
	{610,90,100,50,"查询",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{320,615,150,50,"返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0}},
	WHITE,0}; 
	
	//加载背景
	winbk_flush();
	window_show(ordertrack); 
	time_show(timectl);
	//设计表格结构体
	TABLE_T table={40,160,710,400,6,3,{"订单编号","客户姓名","订单状态"}};
	
	static int pagenow=1;		//进入查询页面时呈现的页数,1表示第一页
	int pagecount=5;		//每页表格所展现的数据行数(不包括首行),5表示5行
	int count=getlistnodecount(orderslist);		//数据总行数(等于订单链表的结点个数)
	static int pagenum=count%pagecount==0?count/pagecount:(count/pagecount)+1;
	//表格总页数(与总结点个数以及每页展示的结点个数有关) 
	
	static Lnode *temp=initlist();
	
	static char buf1[20]="";	//订单编号,初始长度赋值为0 
	static char buf2[20]="";	//客户姓名,初始长度赋值为0 
	int start;		//每一页表格的第一行的序号(从0开始算)
	int i,j;
	char state[6][10]={"待审核","待入库","待出库","运输中","已送达","已驳回"};
	//二位数组,储存中文字符使用,行表示最多可以有几个词语,列表示每个词语最大字节数
	//一中文汉字有两个字节 
	Order_T *p=NULL;  
	//strcpy(buf1,researchorderwin.controls[1].text); 		//输入订单编号
	//strcpy(buf2,researchorderwin.controls[3].text);			//输入客户姓名
	
	if(strlen(buf1)==0&&strlen(buf2)==0){
		//两个搜索框均未输入条件
		int row=0;
		count=getlistnodecount(orderslist);
		pagenum=count%pagecount==0?count/pagecount:count/pagecount+1;
		start=(pagenow-1)*pagecount;
		memset(table.data,0,sizeof(table.data));
		for(i=1;i<=pagecount;i++){
			if(start+i>count){
				break;
			}
			p=(Order_T *)findnode(orderslist,i+start);
			j=0;
			strcpy(table.data[row][j],p->order_id);
			strcpy(table.data[row][++j],p->client_name);
			strcpy(table.data[row][++j],state[p->role]);
			row++;
		} 
		
		table_show(table,pagenow,pagenum);
	}else if(strlen(buf1)!=0&&strlen(buf2)==0){
		//根据订单编号进行查询
		int row=0;
		int count2=getlistnodecount(temp);
		int pagenum2=count2%pagecount==0?count2/pagecount:count2/pagecount+1;
		//表格总页数(与结点总数以及每页展示的结点数有关) 
		start=(pagenow-1)*pagecount; 
		memset(table.data,0,sizeof(table.data));
		
		for(i=1;i<=count2;i++){
			if(start+i>count2){
				break;
			}
			p=(Order_T *)findnode(temp,i+start);
			j=0;
			strcpy(table.data[row][j],p->order_id);
			strcpy(table.data[row][++j],p->client_name);
			strcpy(table.data[row][++j],state[p->role]);
			row++;
		}
		
		if(count2==0){
			pagenum2=1;
		}
		table_show(table,pagenow,pagenum2);
	}else if(strlen(buf1)==0&&strlen(buf2)!=0){
		//根据客户姓名进行查询
		int row=0;
		int count3=getlistnodecount(temp);
		int pagenum3=count3%pagecount==0?count3/pagecount:count3/pagecount+1;
		//表格总页数(与结点总数以及每页展示的结点数有关) 
		start=(pagenow-1)*pagecount; 
		memset(table.data,0,sizeof(table.data));
		
		for(i=1;i<=count3;i++){
			if(start+i>count3){
				break;
			}
			p=(Order_T *)findnode(temp,i+start);
			j=0;
			strcpy(table.data[row][j],p->order_id);
			strcpy(table.data[row][++j],p->client_name);
			strcpy(table.data[row][++j],state[p->role]);
			row++;
		}
		
		if(count3==0){
			pagenum3=1;
		}
		table_show(table,pagenow,pagenum3);
	}
	
	
	strcpy(buf1,ordertrack.controls[1].text); 		//输入订单编号
	strcpy(buf2,ordertrack.controls[3].text);			//输入客户姓名
	
	ordertrack=window_run_with_time(ordertrack,&timectl);			//窗口控件驱动
	
	if(ordertrack.current==4){
		strcpy(buf1,ordertrack.controls[1].text); 		//输入订单编号
		strcpy(buf2,ordertrack.controls[3].text);			//输入客户姓名
		if(strlen(buf1)>0&&strlen(buf2)==0){
			//strcpy(buf1,researchorderwin.controls[1].text);//订单编号查询
			//strcpy(buf2,researchorderwin.controls[3].text);
			freelist(temp);
			temp=initlist(); 
			
			Order_T *T=NULL;
			
			int found=0; 
			for(i=1;i<=getlistnodecount(orderslist);i++){
				T=(Order_T *)findnode(orderslist,i);
				if(strcmp(buf1,T->order_id)==0){
					//创建订单副本
					found=1;
					Order_T *neworder=(Order_T *)malloc(sizeof(Order_T));
					if(!neworder){
						continue;
					} 
					memcpy(neworder,T,sizeof(Order_T));
					insertAtTail(temp,neworder);
				}
			}
			
			//未找到订单 
			if(found==0){
					CONTROL_T fail={350,380,150,50,"未找到该订单!",LIGHTCYAN,CYAN,RED,BUTTON,0};
					memset(buf1,0,sizeof(buf1));
					memset(buf2,0,sizeof(buf2)); 
					control_show(fail);
					
					Sleep(1500);
					return 25;
				}
			return 25;
		}else if(strlen(buf2)>0&&strlen(buf1)==0){
			//strcpy(buf2,researchorderwin.controls[3].text);		//客户姓名查询
			//strcpy(buf1,researchorderwin.controls[1].text);
			freelist(temp);
			temp=initlist();
			
			Order_T *T=NULL;
		
			int found=0;
			for(i=1;i<=getlistnodecount(orderslist);i++){
				T=(Order_T *)findnode(orderslist,i);
				if(strcmp(buf2,T->client_name)==0){
					//创建新副本
					found=1;
					Order_T *neworder=(Order_T *)malloc(sizeof(Order_T));
					if(!neworder){
						continue;
					}
					memcpy(neworder,T,sizeof(Order_T)); 
					insertAtTail(temp,neworder);
				}
			}
			
			//未找到订单 
			if(found==0){
					CONTROL_T fail={350,380,150,50,"未找到该订单!",LIGHTCYAN,CYAN,RED,BUTTON,0};
					memset(buf1,0,sizeof(buf1));
					memset(buf2,0,sizeof(buf2));
					
					control_show(fail);
					Sleep(1500);
					
					return 25;
				} 
			return 25;
				
		}else{
			memset(buf1,0,sizeof(buf1));
			memset(buf2,0,sizeof(buf2));
		}
		return 25;
		
	}else if(ordertrack.current==5){
		//返回上一级 
		winbk_flush();
		return 10;  		//返回订单管理界面 
	}else if(ordertrack.current==-1){
		//左键向上翻页
		if(pagenow>1){
			pagenow--;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是第一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 25; 
	}else if(ordertrack.current==-2){
		//右键向下翻页 
		if(pagenow<pagenum){
			pagenow++;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是最后一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 25;
	} 
}


///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
int admin_pwdchange(){
	//设计修改密码窗口
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
		return  2;
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
			
			return 26;
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
			return 26;			
		}
		
		
		
		
		//输入的密码不一致 
		if(strcmp(buf2,buf3)!=0){
			CONTROL_T fail3={320,490,180,50,"输入的密码不一致!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail3);
			
			Sleep(1500);
			return 26;
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
			
			return 26;
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
			return 2;
		}
		
		 
	}else if(resetwin.current==-1){
		//左键防止程序崩溃
		return 26; 
	}else if(resetwin.current==-2){
		//右键防止程序崩溃
		return 26; 
	} 
}
