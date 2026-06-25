#ifndef _GOODS_H_
#define _GOODS_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

//货物类型枚举
typedef enum{
	GOODS_TYPE_NORMAL,	//普通类 
	GOODS_TYPE_FRAGILE,		//易碎品 
	GOODS_TYPE_COLD_CHAIN,	//冷链类 
	GOOD_TYPE_HAZARDOUS,	//危险品 
}GoodstypeEnum; 

//货物结构体
typedef struct{ 
	char ID[10];		//货物序号 
	char name[20];		//货物名称 
	char type[20];		//货物类型  
	char count[20];		//货物数量 
	char location[20];		//货物位置 
	char in_time[20];		//入库时间 
	
}Goods_T; 

//订单结构体
typedef struct{
	char order_id[30];		//订单编号(每个订单的订单号都独一无二)
	char client_name[20];	//客户姓名
	char phonenum[20];		//客户联系电话
	char client_location[30];		//客户地址
	char goods_name[20];		//货物名称
	char type[10];			//货物类型,易碎品，危险品，普通类，冷链 
	char weight[20];				//货物重量(kg为单位)
	char volumn[20];				//货物大小(立方米为单位)
	char goods_count[20];			//货物数量
	char send_location[30];		//货物发货地址
	char receive_location[30];		//货物收货地址 
	char state[10];			//订单状态(待审核,待入库,待出库,运输中,已送达) 
	char reject_reason[50];		//订单驳回理由(可有可无) 
	char create_time[50];		//订单创建时间 
	char finished_time[50];		//订单完成时间 
	int role;			//作为订单状态的标志(0-待审核,1-待入库,2-待出库,3-运输中,4-已送达)
											//5-已驳回 
}Order_T; 


//定义仓储结构体 
typedef struct{
	
}REPERTORY_T;


int admin_addorder();		//管理员的订单管理界面选择"1.创建订单" 
int admin_researchorder();		//管理员的订单管理界面选择"3.查询订单"
int admin_ordercheck();			//管理员的订单管理界面选择"2.订单审核",只显示待审核订单 
int countOrderByTime(char *,char *,int);	//统计订单数量 
double getFinishRate(char *,char *,int);		//计算某一时间范围某种状态订单完成率 
int countOrderByTypeAndTime(char *,char *,char *);	//统计某一时间范围内某种类型订单数量
int Checkorderinput();		//检验订单数据输入情况 
#endif 
