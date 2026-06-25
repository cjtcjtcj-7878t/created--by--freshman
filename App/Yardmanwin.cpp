#include"Yardmanwin.h"
#include"../View/control.h"
#include"../public/commonlist.h"
#include"../public/file.h"
#include"../App/data.h"
#include"../App/Goods.h"
#include"../View/myTiMe.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<tchar.h>
#include<string.h>
extern Lnode *goodslist;
extern Lnode *orderslist;
extern Lnode *userlist;
extern FILE *goods_fp;
extern FILE *orders_fp;
//调度员界面函数 
int yardmanwin(){
	
	//调度员窗口 
	TIME_T timectl=time_control_init(480,20,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T yardman={280,70,260,320,4,
	{{280,70,260,90,"1.运输调度和跟踪",LIGHTCYAN,CYAN,RED,BUTTON,1},
	{280,150,260,80,"2.车辆管理",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,230,260,80,"3.司机管理",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,310,260,80,"4.返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0}},WHITE,0};
	
	//刷新背景 
	winbk_flush();
	
	CONTROL_T Note={260,400,100,50,"上下键进行选择,回车键进行确定",LIGHTCYAN,CYAN,RED,LABEL,0};
	control_show(Note);
	
	window_show(yardman);
	time_show(timectl);
	yardman=window_run_with_time(yardman,&timectl);
	
	if(yardman.current==0){
		//选择"1.运输调度和跟踪"功能 
		return 19;
	}else if(yardman.current==1){
		//选择"2.车辆管理" 功能 
	}else if(yardman.current==2){
		//选择"3.司机管理"功能 
	}else if(yardman.current==3){
		//选择"4.返回上一级"功能 
		winbk_flush();
		return 1;
	}else if(yardman.current==-1){
		
		//左键防止程序崩溃
		return 7; 
	}else if(yardman.current==-2){
		
		//右键防止程序崩溃
		return 7; 
	}
	
	
}

///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
int trans_control(){
	//窗口显示
	TIME_T timectl=time_control_init(480,20,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T transwin={0,70,810,700,4,{
	{50,700,150,50,"订单编号:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{150,700,180,50,"",LIGHTCYAN,CYAN,RED,EDIT,1,1},
	{350,700,100,50,"查询",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{500,700,100,50,"返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0}},
	WHITE,0};
	
	//加载背景
		
	IMAGE img;
	loadimage(&img,"image/image1.jpg",800,800);
	putimage(0,0,&img);
	
	setbkmode(TRANSPARENT);
	settextcolor(CYAN);
	
	window_show(transwin);
	time_show(timectl);
	
	//设计表格结构体
	TABLE_T table={0,130,810,500,6,5,{"序号","订单编号","货物名称","发货地址","收获地址"}};
	int count=getlistnodecount(orderslist);
	static int pagenow=1;
	int pagecount=5;	//每页表格展示的数据行数 
	static int pagenum=count%pagecount==0?count/pagecount:count/pagecount+1;
	//总表格页数
	
	int start=(pagenow-1)*pagecount;
	int i,j;
	//临时链表存储查询结点 
	static Lnode *templist=initlist();
	static char buf1[30]="";		//订单编号
	char buf2[10]={0};		//序号
	
	Order_T *p=NULL;
	
	//搜索框未输入条件 
	if(strlen(buf1)==0){
		int row=0;
		count=getlistnodecount(orderslist);
		pagenum=count%pagecount==0?count/pagecount:count/pagecount+1;
		start=(pagenow-1)*pagecount;
		memset(table.data,0,sizeof(table.data));
		int k=0;
		//赋值表格 
		for(i=1;i<=pagecount;i++){
			
			if(start+i>count){
				break;
			}
			j=0;
			p=(Order_T *)findnode(orderslist,i+start);
			sprintf(buf2,"%d",++k);
			strcpy(table.data[row][j],buf2);
			strcpy(table.data[row][++j],p->order_id);
			strcpy(table.data[row][++j],p->goods_name);
			strcpy(table.data[row][++j],p->send_location);
			strcpy(table.data[row][++j],p->receive_location);
			//strcpy(table.data[row][++j],p->weight);
			row++;
			
		}
		table_show(table,pagenow,pagenum);
	}else if(strlen(buf1)!=0){
		
		//搜索框输入订单编号 
		int row=0;
		int count2=getlistnodecount(templist);
		int k=0;
		int pagenum2=count2%pagecount==0?count2/pagecount:count2/pagecount+1;
		start=(pagenow-1)*pagecount;
		memset(table.data,0,sizeof(table.data));
		
		//赋值表格 
		for(i=1;i<=count2;i++){
			if(start+i>count2){
				break;
			}
			p=(Order_T *)findnode(templist,i+start);
			j=0;
			sprintf(buf2,"%d",++k);
			strcpy(table.data[row][j],buf2);
			strcpy(table.data[row][++j],p->order_id);
			strcpy(table.data[row][++j],p->goods_name);
			strcpy(table.data[row][++j],p->send_location);
			strcpy(table.data[row][++j],p->receive_location);
			//strcpy(table.data[row][++j],p->weight);
			row++;
		}
		
		if(count2==0){
			pagenum2=1;
		}
		table_show(table,pagenow,pagenum2);
	}
	
	strcpy(buf1,transwin.controls[1].text);
	
	//窗口驱动 
	transwin=window_run_with_time(transwin,&timectl);
	if(transwin.current==2){
		strcpy(buf1,transwin.controls[1].text);
		int flag=0;
		if(strlen(buf1)==0){
			//未输入订单号 
			CONTROL_T fail={350,380,150,50,"请输入订单号!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			
			Sleep(1500);
			return 19;
		}
		for(i=1;i<=getlistnodecount(orderslist);i++){
			p=(Order_T *)findnode(orderslist,i);
		
			if(strcmp(buf1,p->order_id)==0){
				//找到相应订单 
				freelist(templist);
				templist=initlist();
				flag=1;
				Order_T *neworder=(Order_T *)malloc(sizeof(Order_T));
				if(!neworder){
					continue;
				}
				memcpy(neworder,p,sizeof(Order_T));
				insertAtTail(templist,neworder);
					 
				} 
		}
		
		//未找到目标订单 
		if(flag==0){
			CONTROL_T fail={350,380,150,50,"未找到该订单!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
			
			return 19;
		}
		
		return 19;
	}else if(transwin.current==3){
		//返回上一级 
		winbk_flush();
		return 7; 
		
	}else if(transwin.current==-1){
		//左键向上翻页
		if(pagenow>1){
			pagenow--;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是第一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 19; 
	}else if(transwin.current==-2){
			//右键向下翻页 
		if(pagenow<pagenum){
			pagenow++;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是最后一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 19;
	} 
	
	 
	 
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
