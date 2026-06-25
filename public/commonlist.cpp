#include"commonlist.h"
#include"../App/data.h"
#include"../App/Goods.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
/*
链表的基础操作以及链表和文件间的相互读写 
*/
extern FILE *orders_fp;
extern Lnode *orderslist;
Lnode *initlist(){
	Lnode *head=(Lnode *)malloc(sizeof(Lnode));
	if(!head){
		printf("内存分配失败!\n");
		exit(1);
	}
	head->next=NULL;
	head->data=NULL;//哨兵型头结点（不存储有效数据的结点） 
	return head;

}  
//初始化链表，创建带有头结点的链表 


Lnode *createnode(void *data){
	Lnode *newnode=(Lnode *)malloc(sizeof(Lnode));
	if(!newnode){
		printf("内存分配失败!\n");
		exit(1);
	}
	newnode->data=data;
	newnode->next=NULL;
	return newnode; 
}
//创建一个新的结点


void insertAtTail(Lnode *head,void *data){
	Lnode *p=head;
	Lnode *newnode=createnode(data);
	while(p->next!=NULL){ //检查下一个结点是否是尾结点 
		p=p->next;
	}
	p->next=newnode;//链接新的尾结点 
}
//在链表尾结点插入一个结点


int insertAtposition(Lnode *head,void *data,int position){
	Lnode *p=head;
	Lnode *newnode;
	int i=0;
	if(position<0||position>getlistnodecount(head)){
		printf("插入位置不合法!\n");
		return -1; //失败返回-1 
	}
	while(p->next!=NULL&&i<position){
		p=p->next;
		i++;
	}
	if(i==position){
		newnode=(Lnode *)malloc(sizeof(Lnode));
		newnode->next=p->next;//插入操作，p指针停留在插入位置的前一个结点，此操作意味着将
		//新结点的后继链接到后一个结点 
		p->next=newnode;
		newnode->data=data;
	} 
	return 1;  //成功返回1 
} 
//在指定位置插入一个结点 


int deletenode(Lnode *head,int position){
	Lnode *p=head;
	Lnode *q=head->next;
	int i=0;
	if(position<0){
		printf("删除位置不合法!\n");
		return -1;
	}
	while(i<position&&p->next!=NULL){
		p=p->next;
		q=q->next;
		i++;
	}
	if(i==position&&q!=NULL){
		p->next=q->next;
		free(q->data);
		free(q);
		return 1;	
	}
}  
//删除指定位置的结点


void *findnode(Lnode *head,int position){
	Lnode *p=head->next;
	int i=0;
	while(p!=NULL){
		i++;
		if(i==position){
			return p->data;
		}
		p=p->next;
	}
	return NULL;
}
//查找指定位置的结点，返回结点位置

 
void freelist(Lnode *head){
	Lnode *tem;
	while(head!=NULL){
		tem=head;
		head=head->next;
		if(tem->data!=NULL){
			free(tem->data);//释放数据内存 
		}
		free(tem);//释放结点内存 
	}
	
}
//释放链表内存（包括头结点） 


int getlistnodecount(Lnode *head){
	Lnode *p=head->next;//计算链表结点个数,因为不算哨兵型头结点个数,所以从头结点的next
						//开始算 
	int count=0;
	while(p!=NULL){
		p=p->next;
		count++;
	}
	return count;
}
//获取链表结点个数（不包括头结点）

void printlist(Lnode *head,void (*fun)(void *)){
	Lnode *p=head->next;
	while(p!=NULL){
		fun(p->data);
		printf("\n");
		p=p->next;
	}
}

//函数名:file_read_list
//功能:将文件的数据写入链表
//参数:fp--文件指针
//		size--单个数据大小
//		head--链表头结点
//返回值:无   
void file_read_list(FILE *fp,int size,Lnode *head){
	void *data;
	rewind(fp);
	data=malloc(size);
	if(!data){
		printf("数据内存分配失败!\n");
		exit(1);
	}
	memset(data,0,size);
	while(fread(data,size,1,fp)>0){
		insertAtTail((Lnode *)head,data);
		data=malloc(size);
		memset(data,0,size);
	}
	free(data);
}
///////////////////////////////////////////////////

void list_write_file(FILE *fp,int size,Lnode *head){
	Lnode *p=head->next;
	rewind(fp);
	while(p!=NULL){
		fwrite(p->data,size,1,fp);
		p=p->next;
		//fwrite(p->data,size,1,fp);
		fflush(fp);
	}
}
////////////////////////////////////////////////////

Lnode *list_data_update(Lnode *head,int position,char newdata[]){
	int i;
	Lnode *T=NULL;	//临时结点 
	T=(Lnode *)malloc(sizeof(Lnode));		//开辟内存
	memset(T,0,sizeof(Lnode));		//数据初始化为0 
	T=(Lnode *)findnode(head,i);		//找到目标结点
	
	Lnode *newnode=createnode(T->data);
			//开辟新结点(密码与原旧结点不同,其余数据相同)
	USER_T *p=NULL;
	p=(USER_T *)malloc(sizeof(USER_T));
	memset(p,0,sizeof(USER_T));
	p=(USER_T *)findnode(head,i);
	
	strcpy(p->password,newdata);	//修改密码
	deletenode(head,i);		//删除旧结点
	free(T);
	
	insertAtposition(head,newnode->data,i);		 //插入新结点 
	

	
	
	if(strcmp(p->password,newdata)==0){
		return head;	//修改成功 
	}
		//修改失败 
}
////////////////////////////////////////////////////

////////////////////////////////////////////////////
//重置用户密码 
int resetpwd_byname(Lnode *head,const char *username,const char *newpwd){
	if(head==NULL||username==NULL||newpwd==NULL){
		return -1;		//重置失败 
	}
	Lnode *p=head->next;
	while(p!=NULL){
		USER_T *user=(USER_T *)(p->data);
		if(user!=NULL&&strcmp(user->name,username)==0){
			//找到目标账户 
			strncpy(user->password,newpwd,sizeof(user->password)-1);
			user->password[sizeof(user->password)-1]='\0';
			return 1;		//重置成功 
		}
		p=p->next;
	}
	return -1;
}

///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
int reset_order_state(Lnode *head,const char *order_id,const char *new_state){
	
	if(head==NULL||order_id==NULL||new_state==NULL){
		//修改失败 
		return -1;
	}
	Lnode *p=head->next;
	Order_T *T=NULL;
	int flag=0;
	
	while(p!=NULL){
		T=(Order_T *)(p->data);
		if(T!=NULL&&strcmp(T->order_id,order_id)==0){
			//寻找目标订单 
			flag=1;
			break;
		}
		p=p->next;
	}
	if(flag==0){
		//未找到目标订单 
		return -1;
	}
	
	//修改订单状态
	if(flag==1){
	
	strncpy(T->state,new_state,sizeof(T->state)-1);
	T->state[sizeof(T->state)-1]='\0';
	
	
	//修改订单状态标志 
	if(strcmp(T->state,"待审核")==0){
		T->role=0;
	}else if(strcmp(T->state,"待入库")==0){
		T->role=1;
	}else if(strcmp(T->state,"待出库")==0){
		T->role=2;
	}else if(strcmp(T->state,"运输中")==0){
		T->role=3;
	}else if(strcmp(T->state,"已送达")==0){
		T->role=4;
	}else if(strcmp(T->state,"已驳回")==0){
		T->role=5;
	}
}
	if(orders_fp!=NULL){
		rewind(orders_fp);
		list_write_file(orders_fp,sizeof(Order_T),head);
		fflush(orders_fp);
	
	}
	return 1;
} 
