#include"Clerkwin.h"
#include"../View/control.h"
#include"../public/commonlist.h"
#include"../App/data.h"
#include"../App/Goods.h"
#include"../public/file.h"
#include<graphics.h>
#include"Loginwin.h"
#include<time.h>
extern Lnode *orderslist;
extern FILE *orders_fp;
extern Lnode *goodslist;
extern FILE *goods_fp;
////////////////////////////////////////////

int wait_in_count=0;		//待入库订单数量 
int wait_out_count=0;			//待出库订单数 
int transing_count=0;		//运输中订单数量 
////////////////////////////////////////////
int clerkwin(){
	
	//仓储员界面窗口 
	TIME_T timectl=time_control_init(480,10,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T Clerkwin={280,60,260,320,4,
	{{280,60,260,80,"1.货物入库",LIGHTCYAN,CYAN,RED,BUTTON,1,0},
	{280,140,260,80,"2.货物出库",LIGHTCYAN,CYAN,RED,BUTTON,0,0},
	{280,220,260,80,"3.库存管理",LIGHTCYAN,CYAN,RED,BUTTON,0,0},
	{280,300,260,80,"4.返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0,0}},
	WHITE,0};
	
	
//加载背景 
//	IMAGE img;
//	loadimage(&img,"image/image1.jpg",800,800);
//	putimage(0,0,&img);
//		/
//	setbkmode(TRANSPARENT);
//	settextcolor(CYAN);
	winbk_flush();
	
	
	CONTROL_T Note={250,400,100,50,"上下键进行选择,回车键进行确定",LIGHTCYAN,CYAN,RED,LABEL,
	0};
	control_show(Note);
	
	//显示窗口 
	window_show(Clerkwin);
	time_show(timectl);
	//窗口按键驱动 
	Clerkwin=window_run_with_time(Clerkwin,&timectl);
	
	
	if(Clerkwin.current==0){
		//选择"1.货物入库”功能 
		return 14;
	}else if(Clerkwin.current==1){
		//选择“2.货物出库”功能
		return 15; 
	}else if(Clerkwin.current==2){
		//选择“3.库存管理”功能 
		return 16;
	}else if(Clerkwin.current==3){
		//选择“4.返回上一级” 
		winbk_flush();
		return 1;
	}else if(Clerkwin.current==-1){
		
		//左键防止程序崩溃
		return 5; 
	}else if(Clerkwin.current==-2){
		
		//右键防止程序崩溃
		return 5; 
	}
	
	
}

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//货物入库 
int clerk_goods_in(){
	//显示订单窗口
	TIME_T timectl=time_control_init(480,10,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T Goodswin={20,70,750,700,5,
	{{320,75,100,50,"仓储员货物入库",LIGHTCYAN,CYAN,RED,LABEL,0,0},
	{500,700,100,50,"返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0,0},
	{150,700,180,50,"",LIGHTCYAN,CYAN,RED,EDIT,1,1},
	{350,700,100,50,"查看详情",LIGHTCYAN,CYAN,RED,BUTTON,0,0},
	{50,700,150,50,"订单编号:",LIGHTCYAN,CYAN,RED,LABEL,0,0}},WHITE,0};
	
	//加载背景
	winbk_flush(); 
	window_show(Goodswin); 
	time_show(timectl);
	//创建链表存储待入库订单 
	Lnode *inlist=initlist();
	
	//表格结构体
	TABLE_T table={20,130,750,500,6,6,{"序号","货物名称","货物类型","库存数量","存储货位","预计入库时间"}};
	//显示待入库订单的相关信息 
	int pagecount=5;		//每页展示5条订单信息
	//int wait_in_count=0;		//待入库订单数量 
	//int wait_out_count=0;			//待出库订单数 
	int count=getlistnodecount(orderslist);	//总订单数
	Order_T *order=NULL; 
	int i,j;
	for(i=1;i<=count;i++){
		order=(Order_T *)findnode(orderslist,i);
		if(strcmp(order->state,"待入库")==0){
			insertAtTail(inlist,order);
		}
	}
	static int pagenow=1;
	//表格总页数 
	static int pagenum=getlistnodecount(inlist)%pagecount==0?
	getlistnodecount(inlist)/pagecount:(getlistnodecount(inlist)/pagecount)+1;	
	//总表格页数
	
	
	int start=(pagenow-1)*pagecount;
	
	int k=0;		//用作货物序号 
	int d=0;		//用作货物存放位置 
	memset(table.data,0,sizeof(table.data));
	
	time_t now=time(NULL);
	struct tm *local=localtime(&now); 
	int row=0;
	char buf1[5]={0};		//货物序号 
	char buf2[10]={0};		//货物存放位置 
	char buf3[30]={0};		//货物入库时间 
	
	//sprintf(buf2,"%s%d","A",k++);
	sprintf(buf3,"%d-%d-%d",local->tm_year+1900,local->tm_mon+1,local->tm_mday);
	Order_T *T=NULL;
	//表格显示待入库订单
	for(i=1;i<=pagecount;i++){
		T=(Order_T *)findnode(inlist,i+start);
	
			j=0;
			if(i+start>getlistnodecount(inlist)){
				break;
			}
			
			sprintf(buf1,"%d",++k);			//货物序号 
			sprintf(buf2,"%s%d","A",++d);
			strcpy(table.data[row][j],buf1);
			strcpy(table.data[row][++j],T->goods_name);
			strcpy(table.data[row][++j],T->type);
			strcpy(table.data[row][++j],T->goods_count);
			strcpy(table.data[row][++j],buf2);
			strcpy(table.data[row][++j],buf3);
			row++;
		}
		  	 
	
	if(getlistnodecount(inlist)==0){
		pagenum=1;
	}
	
	
	table_show(table,pagenow,pagenum);
	//显示表格 
	Goodswin=window_run_with_time(Goodswin,&timectl);
	//窗口驱动 
	if(Goodswin.current==1){
		//返回上一级 
		winbk_flush();
		return 5;
	}else if(Goodswin.current==3){
		//查看详细信息 
		char buf[20]={0};
		int flag=0;
		strcpy(buf,Goodswin.controls[2].text);
		Order_T *p=NULL;
		
		if(strlen(Goodswin.controls[2].text)==0){
			//检验输入 
			CONTROL_T fail={350,380,150,50,"请输入订单号!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			
			Sleep(1500);
			return 14;
		}
		for(i=1;i<=getlistnodecount(inlist);i++){
			p=(Order_T *)findnode(inlist,i);
			//遍历订单结点
		
			if(strcmp(p->order_id,Goodswin.controls[2].text)==0){
				//根据订单编号进行查询 
				//另起窗口 
				//详细信息窗口
				flag=1;
				if(p->role!=1){
					CONTROL_T fail={350,380,150,50,"该订单已入库或未审核!",LIGHTCYAN,CYAN,RED,BUTTON,0};
					control_show(fail);
					Sleep(1500);
					return 14 ;
				}
				WINDOW_T printwin={20,70,750,700,3,
				{{320,75,100,50,"订单详细信息",LIGHTCYAN,CYAN,RED,LABEL,0},
				{200,700,100,50,"入库",LIGHTCYAN,CYAN,RED,BUTTON,1},
				{460,700,150,50,"返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0}},
				WHITE,0};
				 
				winbk_flush();
				window_show(printwin);
				time_show(timectl);
				char buf[50]={0};
				
				//信息显示 
				sprintf(buf,"订单编号:%s",p->order_id);
				outtextxy(240,115,buf);
				
				sprintf(buf,"客户姓名:%s",p->client_name);
				outtextxy(240,175,buf);
				
				sprintf(buf,"客户电话:%s",p->phonenum);
				outtextxy(240,235,buf);
				
				sprintf(buf,"货物名称:%s",p->goods_name);
				outtextxy(240,295,buf);
				
				sprintf(buf,"货物类型:%s",p->type);
				outtextxy(240,355,buf);
				
				sprintf(buf,"货物重量:%s",p->weight);
				outtextxy(240,415,buf);
				
				sprintf(buf,"货物数量:%s",p->goods_count);
				outtextxy(240,475,buf);
				
				sprintf(buf,"发货地址:%s",p->send_location);
				outtextxy(240,535,buf);
				
				sprintf(buf,"收获地址:%s",p->receive_location);
				outtextxy(240,595,buf);
				
				sprintf(buf,"订单状态:%s",p->state);
				outtextxy(240,655,buf);
				
				//信息显示 
				printwin=window_run_with_time(printwin,&timectl);
				if(printwin.current==2){
					//选择返回上一级 
					winbk_flush();
					return 14;
				}else if(printwin.current==1){
					//选择入库功能 
					char buf[10]="待出库";
					
				
					
					//修改订单状态
					reset_order_state(orderslist,p->order_id,buf);
					
					//根据入库订单结点填充货物结点数据 
					Goods_T *M=(Goods_T *)malloc(sizeof(Goods_T));
					
					
					if(!M){
						return 14;
					}  
					memset(M,0,sizeof(Goods_T));
					char buf0[20]="";
					 
					strcpy(M->ID,buf1); 	//货物序号 
					strcpy(M->name,p->goods_name);		//货物名称 
					strcpy(M->count,p->goods_count);	//货物数量 
					strcpy(M->type,p->type);		//货物类型 
					strcpy(M->in_time,buf3);		//货物入库时间
					strcpy(M->location,buf2); 			//货物存放位置
					
					insertAtTail(goodslist,M); 	//插入货物链表 
					//file_add(goods_fp,sizeof(Goods_T),M);		//写入货物文件
					list_write_file(goods_fp,sizeof(Goods_T),goodslist);
					printf("%d\n",getlistnodecount(goodslist));
					
					//改变库存 
					if(strcmp(p->state,"待出库")==0&&p->role==2){
						//判断入库情况 
						wait_out_count++;
						CONTROL_T success={350,380,150,50,"入库成功!",LIGHTCYAN,CYAN,RED,BUTTON,0};
						control_show(success);
						
						Sleep(1500);
						return 14;
						
					}else{
						CONTROL_T fail={350,380,150,50,"入库失败!",LIGHTCYAN,CYAN,RED,BUTTON,0};
						control_show(fail);
						
						Sleep(1500);
						return 14;
					} 
				}
			}
		}
		
		if(flag==0){
			
			int found=0;
			for(i=1;i<=getlistnodecount(orderslist);i++){
				p=(Order_T *)findnode(orderslist,i);
				if(strcmp(p->order_id,buf)==0){
					found=1;
					break;
				}
			}
			
			//输入的订单不存在 
			if(found==0){
				CONTROL_T fail1={350,380,200,50,"未找到该订单!",LIGHTCYAN,CYAN,RED,BUTTON,0};
				control_show(fail1);
				Sleep(1500);
				return 14;
			}else{
			
			
			//输入的订单存在但不需要入库 
			CONTROL_T fail={350,380,240,50,"该订单已入库或未审核!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
			return 14;
		}
		}
	}else if(Goodswin.current==-1){
		//左键向上翻页
		if(pagenow>1){
			pagenow--;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是第一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 14; 
	}else if(Goodswin.current==-2){
		//右键向下翻页 
		if(pagenow<pagenum){
			pagenow++;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是最后一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 14;
	}
		
	
}
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//货物出库 
int clerk_goods_out(){
	//显示窗口
	TIME_T timectl=time_control_init(480,10,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T goodswin={20,70,750,700,5,{
	{320,75,100,50,"仓储员货物出库",LIGHTCYAN,CYAN,RED,LABEL,0},
	{500,700,100,50,"返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{150,700,180,50,"",LIGHTCYAN,CYAN,RED,EDIT,1,1},
	{350,700,100,50,"查看详情",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{50,700,150,50,"订单编号:",LIGHTCYAN,CYAN,RED,LABEL,0}},WHITE,0}; 
	
	//加载背景 
	winbk_flush();
	window_show(goodswin);
	time_show(timectl);
	//设计表格
	int i,j;
	Order_T *order=NULL;
	
	//创建链表存储待出库订单 
	Lnode *outlist=initlist();
	
	
	TABLE_T table={20,130,750,500,6,6,{"序号","货物名称","货物类型","库存数量","存储货位","预计出库时间"}};
	int count=getlistnodecount(orderslist);		//总订单数 
	
	for(i=1;i<=count;i++){
		order=(Order_T *)findnode(orderslist,i);
		if(strcmp(order->state,"待出库")==0){
			insertAtTail(outlist,order);
		}
	}
	int pagecount=5;		//每页展示的订单数 
	static int pagenow=1;
	static int pagenum=getlistnodecount(outlist)%pagecount==0?
	getlistnodecount(outlist)/pagecount:getlistnodecount(outlist)/pagecount+1;
	//表格页面总数 
	int start=(pagenow-1)*pagecount;
	
	int row=0;
	int k=0;		//用作货物序号 
	int d=0;		//用作货物存放位置 
	
	memset(table.data,0,sizeof(table.data));
	Order_T *p=NULL;
	//int transing_count=0;		//运输中订单数量 
	//获取时间 
	time_t now=time(NULL);
	struct tm *local=localtime(&now);
	char buf1[20]={0};	//货物序号 
	char buf2[20]={0};	//货物存储货位 
	char buf3[20]={0};	//货物出库时间
	
	//sprintf(buf2,"%s%d","A",k++);
	sprintf(buf3,"%d-%d-%d",local->tm_year+1900,local->tm_mon+1,local->tm_mday);
	//表格显示待出库订单
	for(i=1;i<=getlistnodecount(outlist);i++){
		
		p=(Order_T *)findnode(outlist,i+start);
		
			
			j=0;
			if(i+start>getlistnodecount(outlist)){
				break;
			}
			sprintf(buf1,"%d",++k);	//货物序号 
			sprintf(buf2,"%s%d","A",++d); 
			strcpy(table.data[row][j],buf1);	//货物序号 
			strcpy(table.data[row][++j],p->goods_name);		//货物名称 
			strcpy(table.data[row][++j],p->type);		//货物类型 
			strcpy(table.data[row][++j],p->goods_count);	//货物数量 
			strcpy(table.data[row][++j],buf2);			//货物存储货位 
			strcpy(table.data[row][++j],buf3);		//预计货物出库时间 
			row++;
		
	} 
	//显示表格 
	
	if(getlistnodecount(outlist)==0){
		pagenum=1;
	}
	table_show(table,pagenow,pagenum);
	//窗口驱动 
	goodswin=window_run_with_time(goodswin,&timectl);
	
	if(goodswin.current==1){
		//返回上一级 
		winbk_flush();
		return 5;
	}else if(goodswin.current==3){
		//查看详情 
		Order_T *T=NULL;
		int flag=0;
		char buf[20]="";
		strcpy(buf,goodswin.controls[2].text);
		if(strlen(goodswin.controls[2].text)==0){
			//检验订单号输入情况 
			CONTROL_T fail={350,380,150,50,"请输入订单号!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			
			Sleep(1500);
			return 15;
		}
		for(i=1;i<=getlistnodecount(outlist);i++){
			T=(Order_T *)findnode(outlist,i);
		
			if(strcmp(T->order_id,goodswin.controls[2].text)==0){
				//另起窗口显示详细信息
				//详细信息窗口
				flag=1;
				if(T->role!=2){
					CONTROL_T fail={350,380,150,50,"该订单已出库或未入库!",LIGHTCYAN,CYAN,RED,BUTTON,0};
					control_show(fail);
					
					Sleep(1500);
					return 15;			
				}
				WINDOW_T printwin={20,70,750,700,3,
				{{320,75,100,50,"订单详细信息",LIGHTCYAN,CYAN,RED,LABEL,0},
				{200,700,100,50,"出库",LIGHTCYAN,CYAN,RED,BUTTON,1},
				{460,700,150,50,"返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0}},
				WHITE,0};
				 
				winbk_flush();
				window_show(printwin);
				time_show(timectl);
				char buf[50]={0};
				
				//信息显示 
				sprintf(buf,"订单编号:%s",p->order_id);
				outtextxy(240,115,buf);
				
				sprintf(buf,"客户姓名:%s",p->client_name);
				outtextxy(240,175,buf);
				
				sprintf(buf,"客户电话:%s",p->phonenum);
				outtextxy(240,235,buf);
				
				sprintf(buf,"货物名称:%s",p->goods_name);
				outtextxy(240,295,buf);
				
				sprintf(buf,"货物类型:%s",p->type);
				outtextxy(240,355,buf);
				
				sprintf(buf,"货物重量:%s",p->weight);
				outtextxy(240,415,buf);
				
				sprintf(buf,"货物数量:%s",p->goods_count);
				outtextxy(240,475,buf);
				
				sprintf(buf,"发货地址:%s",p->send_location);
				outtextxy(240,535,buf);
				
				sprintf(buf,"收获地址:%s",p->receive_location);
				outtextxy(240,595,buf);
				
				sprintf(buf,"订单状态:%s",p->state);
				outtextxy(240,655,buf);
				
				//信息显示 
				
				//窗口驱动 
				printwin=window_run_with_time(printwin,&timectl);
				
				if(printwin.current==2){
					//返回上一级 
					winbk_flush();
					return 15;
				}else if(printwin.current==1){
					//选择出库功能 
					char buf[10]="运输中";
					
					
					//改变订单状态
					reset_order_state(orderslist,T->order_id,buf);
					
					
					//改变库存
					 
					if(strcmp(T->state,"运输中")==0&&T->role==3){
						//检验出库情况 
						transing_count++;
						CONTROL_T success={350,380,150,50,"出库成功!",LIGHTCYAN,CYAN,RED,BUTTON,0};
						control_show(success);
						Sleep(1500);
						
						return 15;
					}else{
						CONTROL_T fail={350,380,150,50,"出库失败!",LIGHTCYAN,CYAN,RED,BUTTON,0};
						control_show(fail);
						
						Sleep(1500);
						return 15;
					}
				}
				
			}
		}
		
		if(flag==0){
			
			int found=0;
			for(i=1;i<=getlistnodecount(orderslist);i++){
				T=(Order_T *)findnode(orderslist,i);
				if(strcmp(T->order_id,buf)==0){
					found=1;
					break;
					
				}
			}
			
			//输入的订单不存在 
			if(found==0){
				CONTROL_T fail1={350,380,200,50,"该订单不存在!",LIGHTCYAN,CYAN,RED,BUTTON,0};
				control_show(fail1);
				
				Sleep(1500);
				return 15;
			}else{
			
			
			//输入的订单存在但不需要出库 
			CONTROL_T fail={350,380,220,50,"该订单已出库或未入库!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
			
			return 15;
			
		}
		}
	}else if(goodswin.current==-1){
		//左键向上翻页
		if(pagenow>1){
			pagenow--;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是第一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 15; 
	}else if(goodswin.current==-2){
		//右键向下翻页 
		if(pagenow<pagenum){
			pagenow++;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是最后一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 15;
	}
}

int repertory_detail(){
	//库存窗口
	//查询窗口
	TIME_T timectl=time_control_init(480,10,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T researchgoodswin={20,70,750,700,6,
	{{25,90,100,50,"货物名称:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{125,90,180,50,"",LIGHTCYAN,CYAN,RED,EDIT,1,1},
	{305,90,100,50,"货物序号:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{405,90,180,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
	{610,90,100,50,"查询",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{320,715,150,50,"返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0}},
	WHITE,0}; 
	
	//加载背景
	winbk_flush();
	window_show(researchgoodswin); 
	time_show(timectl);
	
	//设计表格结构体 
	TABLE_T table={20,150,750,500,6,6,{"序号","货物名称","货物类型","货物数量","存储货位","入库时间"}};
	int pagecount=5;		//每页表格展示的货物数据(5行)
	int count=getlistnodecount(goodslist);
	int pagenum=count%pagecount==0?count/pagecount:count/pagecount+1;
	static int pagenow=1;
	int start=(pagenow-1)*pagecount;
	int i,j;

	int row=0;
	//临时货物链表 
	static Lnode * temp=initlist();
	time_t now=time(NULL);
	struct tm *local=localtime(&now); 

	
	static char buf1[20]="";	//根据货物名称查询 
	static char buf2[20]="";	//根据货物序号查询 
	

	memset(table.data,0,sizeof(table.data));
	Order_T *p=NULL;
	Goods_T *T=NULL;
	
	//搜索框未输入内容 
	if(strlen(buf1)==0&&strlen(buf2)==0){
		start=(pagenow-1)*pagecount;
		pagenum=count%pagecount==0?count/pagecount:count/pagecount+1;
		memset(table.data,0,sizeof(table.data));
		int row=0;
		int k=0;
		char buf[50]="";
		//显示表格内容 
		for(i=1;i<=pagecount;i++){
			
			if(start+i>getlistnodecount(goodslist)){
				break;
			}
			T=(Goods_T *)findnode(goodslist,i+start);
			p=(Order_T *)findnode(orderslist,i+start);
			j=0;
			if(strcmp(p->goods_name,T->name)==0&&p->role==2){
			//判断货物是否已出库 
			sprintf(buf,"%d",++k);
			strcpy(table.data[row][j],buf);
			strcpy(table.data[row][++j],T->name);
			strcpy(table.data[row][++j],T->type);
			strcpy(table.data[row][++j],T->count);
			strcpy(table.data[row][++j],T->location);
			strcpy(table.data[row][++j],T->in_time);
			row++;
		}
		} 
		
		if(count==0){
			pagenum=1;
		}
		
		table_show(table,pagenow,pagenum);
	}else if(strlen(buf1)!=0&&strlen(buf2)==0){
		//根据货物名称查询
		int count2=getlistnodecount(temp);
		int pagenum2=count2%pagecount==0?count2/pagecount:count2/pagecount+1;
		start=(pagenow-1)*pagecount;
		memset(table.data,0,sizeof(table.data));
		int row=0;
		int k=0;
		char buf[50]="";
		//显示表格内容 
		for(i=1;i<=pagecount;i++){
			if(start+i>count2){
				break;
			}
			j=0;
			T=(Goods_T *)findnode(temp,start+i);
			p=(Order_T *)findnode(orderslist,start+i);
		
				
			sprintf(buf,"%d",++k);
			strcpy(table.data[row][j],buf);
			strcpy(table.data[row][++j],T->name);
			strcpy(table.data[row][++j],T->type);
			strcpy(table.data[row][++j],T->count);
			strcpy(table.data[row][++j],T->location);
			strcpy(table.data[row][++j],T->in_time);
			row++;
		}
		
		if(count2==0){
			pagenum2=1;
		}
		table_show(table,pagenow,pagenum2); 
		
			 
		}
		

	else if(strlen(buf1)==0&&strlen(buf2)!=0){
		//根据货物序号查询
		int row=0;
		int k=0;
		char buf[50]="";
		int count3=getlistnodecount(temp);
		int pagenum3=count3%pagecount==0?count3/pagecount:count3/pagecount+1;
		start=(pagenow-1)*pagecount;
		memset(table.data,0,sizeof(table.data));
		
		//显示表格内容 
		for(i=1;i<=count3;i++){
			if(start+i>count3){
				break;
			}
			T=(Goods_T *)findnode(temp,i+start);
			p=(Order_T *)findnode(orderslist,i+start);
			j=0;
			
			
			if(strcmp(buf2,T->ID)==0&&p->role==2){
			
			sprintf(buf,"%d",++k);
			strcpy(table.data[row][j],buf);
			strcpy(table.data[row][++j],T->name);
			strcpy(table.data[row][++j],T->type);
			strcpy(table.data[row][++j],T->count);
			strcpy(table.data[row][++j],T->location);
			strcpy(table.data[row][++j],T->in_time);
			row++;
		}
		}
		
		if(count3==0){
			pagenum3=1;
		}
		table_show(table,pagenow,pagenum3); 
	}
	//窗口驱动 
	researchgoodswin=window_run_with_time(researchgoodswin,&timectl);
	if(researchgoodswin.current==5){
		//返回上一级 
		winbk_flush();
		return 5;
	}else if(researchgoodswin.current==4){
		//查询功能 
		strcpy(buf1,researchgoodswin.controls[1].text);
		//输入货物名称查询 
		strcpy(buf2,researchgoodswin.controls[3].text);
		//输入货物序号查询 
		
		
		if(strlen(buf1)>0&&strlen(buf2)==0){
			//根据货物名称查询 
			freelist(temp);
			temp=initlist();
			int flag=0;
			//memset(T,0,sizeof(Goods_T));
			
			for(i=1;i<=getlistnodecount(goodslist);i++){
				T=(Goods_T *)findnode(goodslist,i);
				
				if(strcmp(T->name,buf1)==0){
					//创建副本
					Goods_T *newgoods=(Goods_T *)malloc(sizeof(Goods_T));
					if(!newgoods){
						continue;
					}
					flag=1;
					//复制数据 
					memcpy(newgoods,T,sizeof(Goods_T));
					//插入链表 
					insertAtTail(temp,newgoods); 
				}
			}
			
			if(flag==0){
					CONTROL_T fail={350,380,150,50,"未找到该订单!",LIGHTCYAN,CYAN,RED,BUTTON,0};
					memset(buf1,0,sizeof(buf1));
					memset(buf2,0,sizeof(buf2));
					control_show(fail);
					
					Sleep(1500);
					return 16;
				}
			return 16;
		}else if(strlen(buf1)==0&&strlen(buf2)>0){
			//根据货物序号查询 
			freelist(temp);
			temp=initlist();
			int flag=0;
			//memset(T,0,sizeof(Goods_T));
			
			
			for(i=1;i<=getlistnodecount(goodslist);i++){
				T=(Goods_T *)findnode(goodslist,i);
				if(strcmp(buf2,T->ID)==0){
					Goods_T *newgoods=(Goods_T *)malloc(sizeof(Goods_T));
					
					if(!newgoods){
						continue;
					}
					//复制数据 
					flag=1;
					memcpy(newgoods,T,sizeof(Goods_T));
					//插入链表
					insertAtTail(temp,newgoods); 
				}
			}
			
			if(flag==0){
					CONTROL_T fail={350,380,150,50,"未找到该订单!",LIGHTCYAN,CYAN,RED,BUTTON,0};
					memset(buf1,0,sizeof(buf1));
					memset(buf2,0,sizeof(buf2));
					control_show(fail);
					
					Sleep(1500);
					return 16;
				}
			return 16;
		}else{
			memset(buf1,0,sizeof(buf1));
			memset(buf2,0,sizeof(buf2));
		}
		return 16;
	}else if(researchgoodswin.current==-1){
		//左键向上翻页
		if(pagenow>1){
			pagenow--;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是第一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			
			Sleep(1500);
			return 16;
		} 
	}else if(researchgoodswin.current==-2){
		//右键向下翻页 
		if(pagenow<pagenum){
			pagenow++;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是最后一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			
			
			Sleep(1500);
		}
		return 16;
	}
	
	 
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////	

