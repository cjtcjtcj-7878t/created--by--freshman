#ifndef _COMMONLIST_H_
#define _COMMONLIST_H_
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h> 

typedef struct node{
	void *data;
	struct node *next;
}Lnode;//通用链表的定义形式 

Lnode *initlist();  //初始化链表，创建带有哨兵型头结点的链表 
Lnode *createnode(void *); //创建一个新的结点
void insertAtTail(Lnode *,void *);    //在链表尾结点插入一个结点
int insertAtposition(Lnode *head,void *,int);  //在指定位置插入一个结点 
int deletenode(Lnode *,int);    //删除指定位置的结点
void * findnode(Lnode *,int);   //查找指定数据的结点，返回结点数据，（不包括头结点） 
void freelist(Lnode *);   //释放链表内存（包括头结点） 
int getlistnodecount(Lnode *);  //获取链表结点个数,（不包括头结点） 
void printlist(Lnode *,void (*fun)(void *));  //打印结点内容 
void file_read_list(FILE *,int,Lnode *);//读文件数据存储到链表中 
void list_write_file(FILE *,int,Lnode *);//读链表数据到文件 
Lnode *list_data_update(Lnode *,int,char *);		//修改链表数据域数据(写死)  
int resetpwd_byname(Lnode *,const char*,const char *);		//重置密码(1-成功,-1-失败) 
int reset_order_state(Lnode *,const char *,const char *);	//修改订单状态(1-成功,-1-失败) 
#endif 
