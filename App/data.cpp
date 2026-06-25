#include"data.h"
#include"../App/Goods.h" 
#include<time.h> 
#include"../public/commonlist.h"
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"../public/file.h" 
#include<tchar.h>

extern Lnode *userlist;
extern Lnode *orderslist;
extern Lnode *goodslist;
//初始化用户账号密码(初始化一个admin) 
Lnode *user_data_init_admin(FILE *user_fp){
	//1.创建用户链表
	userlist=initlist();
	
	//判断文件大小
	if(file_getsize("data/users.txt")==0){
	//如果为0，则初始化一个用户结点写入链表和硬盘文件
	USER_T *p=NULL;
	p=(USER_T *)malloc(sizeof(USER_T));
	memset(p,0,sizeof(USER_T));
	
	sprintf(p->ID,"%d",1000+getlistnodecount(userlist));	//角色ID自动生成 
	strcpy(p->name,"admin");		//初始化admin 
	strcpy(p->password,"123456");	//初始化密码 
	p->role=1;				//1表示管理员角色,2表示客服,3表示仓储员,4表示调度员 
	p->state=1;			//1表示角色状态可用,0为不可用 
	
	insertAtTail(userlist,p);	//将新结点插入到链表尾部 
	
	list_write_file(user_fp,sizeof(USER_T),userlist);	//链表数据写入硬盘文件 
	}else{
		//如果不为0，则添加文件数据到链表中 
		file_read_list(user_fp,sizeof(USER_T),userlist);
	} 
	return userlist;

}

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
Lnode *order_data_init(FILE *order){
	//初始化订单数据 
	orderslist=initlist();
	int i=1;
	char order_no[30]="0";
	char buf[15]="0";
	time_t now=time(NULL);
	struct tm *local=localtime(&now); 
	sprintf(buf,"%d%02d%02d",local->tm_year+1900,local->tm_mon+1,local->tm_mday);
	sprintf(order_no,"WL%s%06d",buf,i);
	if(file_getsize("data/orders.txt")==0){
		//如果订单链表为0，则初始化一个订单 
		Order_T *p=NULL;
		p=(Order_T *)malloc(sizeof(Order_T));	//临时结点创建订单 
		memset(p,0,sizeof(Order_T));
		
		strcpy(p->order_id,order_no);
		strcpy(p->client_name,"Alice");
		strcpy(p->phonenum,"123456");
		strcpy(p->client_location,"American");		//赋值 
		strcpy(p->send_location,"China");
		strcpy(p->receive_location,"American");
		strcpy(p->goods_name,"华为Mate 70");
		strcpy(p->volumn,"0.01");
		strcpy(p->weight,"0.203");
		strcpy(p->type,"普通类");
		strcpy(p->goods_count,"10");
		strcpy(p->state,"待审核");
		p->role=0;
		strcpy(p->create_time,buf); 
		insertAtTail(orderslist,p);		//结点插入到链表尾部
		list_write_file(order,sizeof(Order_T),orderslist);	//写入硬盘文件
		 
	}else{
		//如果订单文件不为0，则写入订单链表 
		file_read_list(order,sizeof(Order_T),orderslist);
	}
	return orderslist;
}

////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
