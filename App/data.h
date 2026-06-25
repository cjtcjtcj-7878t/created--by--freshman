#ifndef _DATA_H_
#define _DATA_H_
#include<stdio.h>
#include"../public/commonlist.h"
//extern FILE *user_fp;
//extern Lnode *userlist;

//用户结构体 
typedef struct user_t
{
	char ID[6];//用户ID
	char name[10];//用户姓名
	char password[10];//用户密码
	int role;//1--管理员，2--快递员 ，3--调度员，4--客服 
	int state; //1--可用，0--不可用 
}USER_T;
//

//extern int g_capacity;
//extern USER_T *g_users;
//extern USER_T now_user;
//extern USER_T *g_Puser;
//extern int g_count;
//extern FILE *user_fp;




//初始化用户数据到硬盘文件中
Lnode *user_data_init_admin(FILE *user_fp);	//在硬盘中初始化用户数据 
Lnode *order_data_init(FILE *orders_fp);	//在硬盘中初始化订单数据 
#endif 
