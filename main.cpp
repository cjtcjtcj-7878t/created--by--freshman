#include <iostream>
#include"View/control.h"
#include"App/Startwin.h"
#include"App/Loginwin.h"
#include"App/data.h"
#include"public/file.h" 
#include"App/Adminwin.h"
#include"App/Clerkwin.h"
#include"App/Yardmanwin.h"
#include"App/Cswin.h"
#include"App/Goods.h"
#include"View/myTiMe.h"
#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<tchar.h>
#include<Time.h>
#include<windows.h>


#define STARTWIN 0
#define LOGINWIN 1
#define ADMINWIN 2
#define ADMINWIN_SYSTEMMANAGE 3
#define ADMIN_ADDUSERWIN 4
#define CLERKWIN 5
#define ADMIN_RESEARCHUSERWIN 6
#define YARDMANWIN 7
#define CSWIN 8
#define ADMIN_PWDRESET 9
#define ADMINWIN_ORDERMANAGE 10
#define ADMIN_ADDORDER 11
#define ADMIN_RESEARCHORDER 12 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


//////////////////
		//全局变量 
Lnode *userlist=NULL;		//用户链表 
FILE *user_fp=NULL;			//用户文件 
Lnode *goodslist=NULL;		//货物链表(不同于订单链表)
FILE *goods_fp=NULL;		//货物文件 
Lnode *orderslist=NULL;			//订单链表(不同于货物链表)
FILE *orders_fp=NULL;			//订单文件 
char time_str[100]="";		//显示时间 
//////////////////
int main(int argc, char** argv) {
	initgraph(800,800,EX_SHOWCONSOLE);
	setbkmode(TRANSPARENT);
	IMAGE img;
	loadimage(&img,"image/image1.jpg",800,800);
	putimage(0,0,&img);
	//主窗口显示
	user_fp=file_open("data/users.txt");
	//硬盘用户文件 
	goods_fp=file_open("data/goods.txt");
	//硬盘货物文件 
	orders_fp=file_open("data/orders.txt");
	//硬盘订单文件 
	userlist=user_data_init_admin(user_fp);
	orderslist=order_data_init(orders_fp);
	//在用户链表初始化一个admin用于进入系统操作 
	
	goodslist=initlist();//创建一个货物链表
	file_read_list(goods_fp,sizeof(Goods_T),goodslist);  
//	WINDOW_T Startwin={200,200,400,300,3,{
//	{200,200,400,100,"1.登录",LIGHTCYAN,CYAN,RED,BUTTON,1},
//	{200,300,400,100,"2.注册",LIGHTCYAN,CYAN,RED,BUTTON,0},
//	{200,400,400,100,"3.退出",LIGHTCYAN,CYAN,RED,BUTTON,0}},
//	WHITE,0};
//	//登录窗口显示
//	WINDOW_T Loginwin={200,200,300,300,6,{
//	{200,200,100,100,"账户:",LABEL,0},
//	{200,300,100,100,"密码:",LABEL,0},
//	{300,200,200,100,"",LIGHTCYAN,CYAN,RED,EDIT,1},
//	{300,300,200,100,"",LIGHTCYAN,CYAN,RED,EDIT_PWD,0},
//	{200,400,100,100,"登录",LIGHTCYAN,CYAN,RED,BUTTON,0},
//	{300,400,100,100,"返回",LIGHTCYAN,CYAN,RED,BUTTON,0}},
//	WHITE,0}; 
//	
	
	//window_show(Startwin);
	//window_run(Startwin);
	
	//使用函数指针进行界面间的切换
	
	
	//时间线
	int win_id=0;
	int (*func[30])()={
	startwin,	//0,主选择界面 
	loginwin,	//1,登陆界面 
	adminwin,	//2,管理员选择界面 
	adminwin_systemmanage,	//3,在管理员选择界面选择"1.系统管理"功能后呈现的界面 
	admin_adduserwin,	//4,在"系统管理"界面选择"1.创建用户"功能后的创建界面
	clerkwin,	//5,仓储员选择界面 
	admin_researchuserwin,	//6,在“系统管理”页面选择"2.用户查询"功能后的查询页面 
	yardmanwin,	//7.调度员选择界面 
	cswin,			//8.客服选择界面 
	admin_pwdreset,		//9.在管理员系统管理界面选择"3.密码重置"功能后的重置界面
	adminwin_ordermanage,		//10.在管理员选择界面选择“2.订单管理”
	admin_addorder,			//11.在管理员订单管理界面选择"1.创建订单"
	admin_researchorder,	 	//12. 在管理员订单管理界面选择"3.查询订单"
	admin_ordercheck,			//13.在管理员订单管理界面选择"2.订单审核",只显示待审核订单 
 	clerk_goods_in,		//14.在仓储员选择界面选择"1.货物入库",只显示待入库订单 
	clerk_goods_out,	//15,在仓储员界面选择"2.货物出库",只显示待出库订单
	repertory_detail,	//16,在仓储员选择界面选择"3.库存管理" 
	cs_addorder,		//17,在客服选择界面选择"1.订单创建" 
	cs_researchorder,	//18,在客服选择界面选择"2.订单查询" 
	trans_control,		//19,在调度员选择界面选择"1.运输调度与跟踪"
	admin_statis,		//20,在管理员选择界面选择"5.统计分析"
	cs_consumerfeedback,	//21,在客服选择界面选择"4.客户反馈" 
	before_reset_pwd,				//22,在主选择界面选择"2.忘记密码"
	reset_pwd,				//23,在"2.忘记密码"界面获取权限后的重置密码界面 
	admin_orderchange,		//24,在订单管理界面选择"4.顶单修改" 
	admin_ordertrack,		//25,在订单管理界面选则"5.订单跟踪" 
	admin_pwdchange,		//26,在管理员选择界面选择"7.密码修改" 
	}; 
	while(1){
		//使用函数指针进行不同界面的切换 
		win_id=func[win_id]();
	};
	
//	while(1){
//		
//	};
	
	return 0;
}
