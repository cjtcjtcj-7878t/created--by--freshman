#include"Goods.h"
#include"../View/control.h"
#include"../public/commonlist.h"
#include"../public/file.h"
#include"../View/myTiMe.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<tchar.h>

#define MAX_CLIENTNAME_LEN 20
#define MAX_PHONE_LEN 11
#define MAX_LOCATION_LEN 30
#define MAX_GOODNAME_LEN 30
#define MAX_WEIGHT_LEN 8
#define MAX_VOLUMN_LEN 10
#define MAX_GOODSCOUNT_LEN 8
#define MAX_SEND_LEN 50
#define MAX_RECEIVE_LEN 50
#define MAX_REJECT_LEN 50 
extern Lnode *goodslist;
extern Lnode *orderslist;
extern FILE *orders_fp;
extern FILE *goods_fp;
/////////////////////////////////////////////////////////////////////

int wait_check_count=0;			//待审核的订单数
int reject_count=0; 			//驳回的订单数
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//管理员的创建订单界面 
int admin_addorder(){
	//创建订单窗口
	TIME_T timectl=time_control_init(480,740,300,50,1000,TIME_FORMAT_FULL);
	int flag=1;
	int i=getlistnodecount(orderslist)+1;
	char order_no[30]="0";
	char buf[15]="0";
	time_t now=time(NULL);
	struct tm *local=localtime(&now); 
	sprintf(buf,"%04d%02d%02d",local->tm_year+1900,local->tm_mon+1,local->tm_mday);
	sprintf(order_no,"WL%s%06d",buf,i);
	//printf("%s",order_no);
	printf("%s",order_no);
	WINDOW_T addorder={150,5,500,720,25,{
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
	{255,660,100,50,"提交",LIGHTCYAN,CYAN,RED,BUTTON,0,0},
	{445,660,100,50,"返回",LIGHTCYAN,CYAN,RED,BUTTON,0,0}},WHITE,0}; 
	
	//strcpy(addorder.controls[1].text,order_no);

	
	
	//订单编号的显示 
	Order_T *M=NULL;
	char key;
	//M=(Order_T *)malloc(sizeof(Order_T));
	//memset(M,0,sizeof(Order_T));
	int j;
	for(j=1;j<=getlistnodecount(orderslist);j++){
		M=(Order_T *)findnode(orderslist,j); 
		if(strcmp(M->order_id,order_no)==0){
			//有相同的订单编号+1显示 
			flag=0;
			break;
	}
}
	if(getlistnodecount(orderslist)==0){	//无订单时的显示 
		strcpy(addorder.controls[1].text,order_no);
	}
	if(flag==0){
		//有相同的订单编号
		sprintf(order_no,"WL%s%06d",buf,getlistnodecount(orderslist)+2);
		strcpy(addorder.controls[1].text,order_no);
	}else if(flag==1){
		strcpy(addorder.controls[1].text,order_no);
	}
	
		//加载背景
	winbk_flush();
	//显示窗口
	window_show(addorder); 
	time_show(timectl);
	
	//窗口按钮驱动
	addorder=window_run_with_time(addorder,&timectl);
	
	

	if(addorder.current==23){ 
		winbk_flush();
		return 10;		//返回订单管理界面 
	}else if(addorder.current==22){		//创建订单 
		int k;
		
		
		
		int flag=1;
		char time1[50]=""; 
		Order_T *p=NULL;
		//p=(Order_T *)malloc(sizeof(Order_T));		//临时订单结点p用于遍历订单编号 
		//memset(p,0,sizeof(Order_T));
		time_t now=time(NULL);
	    struct tm *local=localtime(&now); 
	    sprintf(time1,"%d%02d%02d",local->tm_year+1900,local->tm_mon+1,local->tm_mday);
		Order_T *T=NULL;
		
		
		T=(Order_T *)malloc(sizeof(Order_T));		//临时订单结点T用于添加订单结点 
		memset(T,0,sizeof(Order_T));
		
		if(strlen(addorder.controls[3].text)==0||strlen(addorder.controls[5].text)==0||
		strlen(addorder.controls[7].text)==0||strlen(addorder.controls[9].text)==0||
		strlen(addorder.controls[11].text)==0||strlen(addorder.controls[13].text)==0||strlen(addorder.controls[14].text)==0
		||strlen(addorder.controls[15].text)==0||strlen(addorder.controls[17].text)==0||
		strlen(addorder.controls[21].text)==0){
			CONTROL_T fail7={350,380,150,50,"请完善相关数据!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail7);
			
			Sleep(1500);
			return 11;
		}
		for(k=1;k<=getlistnodecount(orderslist);k++){
		
			p=(Order_T *)findnode(orderslist,k);
			if(strcmp(order_no,p->order_id)==0){
			   		flag=0;	
					break;	//遍历已有订单的订单编号,确保每个
			 }else{				//订单的订单编号不重复	
			 	flag=1;
			 }
		}	
		if(flag==0){
				
				int flag2=1;		
				//有相同的订单编号						
				sprintf(order_no,"WL%s%06d",buf,i+1);	//若有相同的订单编号则+1 
				strcpy(T->order_id,order_no);
				strcpy(T->client_name,addorder.controls[3].text);
				strcpy(T->phonenum,addorder.controls[5].text);
				strcpy(T->client_location,addorder.controls[7].text);
				strcpy(T->goods_name,addorder.controls[9].text);
				strcpy(T->goods_count,addorder.controls[15].text);
				strcpy(T->volumn,addorder.controls[17].text);
				strcpy(T->weight,addorder.controls[13].text);
				strcpy(T->send_location,addorder.controls[19].text);
				strcpy(T->receive_location,addorder.controls[21].text);
				strcpy(T->state,"待审核");
				strcpy(T->create_time,time1);
				T->role=0;
				if(strcmp(addorder.controls[11].text,"冷链")==0){
					strcpy(T->type,"冷链");
				}else if(strcmp(addorder.controls[11].text,"易碎品")==0){
					strcpy(T->type,"易碎品");
				}else if(strcmp(addorder.controls[11].text,"普通类")==0){
					strcpy(T->type,"普通类");
				}else if(strcmp(addorder.controls[11].text,"危险品")==0){
					strcpy(T->type,"危险品");
				}
				
				
				//插入链表并写入文件 
				insertAtTail(orderslist,T);
				file_add(orders_fp,sizeof(Order_T),T);
				
		}else{
				//无相同的订单编号 
				strcpy(T->order_id,order_no);
				strcpy(T->client_name,addorder.controls[3].text);
				strcpy(T->phonenum,addorder.controls[5].text);
				strcpy(T->client_location,addorder.controls[7].text);
				strcpy(T->goods_name,addorder.controls[9].text);
				strcpy(T->send_location,addorder.controls[19].text);
				strcpy(T->receive_location,addorder.controls[21].text);
				strcpy(T->goods_count,addorder.controls[15].text);
				strcpy(T->volumn,addorder.controls[17].text);
				strcpy(T->weight,addorder.controls[13].text);
				strcpy(T->state,"待审核");
				strcpy(T->create_time,time1);
				T->role=0;
				if(strcmp(addorder.controls[11].text,"冷链")==0){
					strcpy(T->type,"冷链");
				}else if(strcmp(addorder.controls[11].text,"易碎品")==0){
					strcpy(T->type,"易碎品");
				}else if(strcmp(addorder.controls[11].text,"普通类")==0){
					strcpy(T->type,"普通类");
				}else if(strcmp(addorder.controls[11].text,"危险品")==0){
					strcpy(T->type,"危险品");
				}
				//outtextxy(380,10,order_no);
				//插入链表并写入文件 
				insertAtTail(orderslist,T);
				file_add(orders_fp,sizeof(Order_T),T);
			}
		//弹窗提示
		CONTROL_T success={380,360,150,50,"订单创建成功!",LIGHTCYAN,CYAN,RED,BUTTON,0};
		control_show(success);
		
		//insertAtTail(orderslist,T);
		//file_add(orders_fp,sizeof(Order_T),T);
		Sleep(1500);	 
		return 10;		//返回订单管理界面 
	}else if(addorder.current==-1){
		
		//左键防止程序崩溃
		return 11; 
	}else if(addorder.current==-2){
		
		//右键防止程序崩溃
		return 11; 
	} 
}
////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//管理员查询订单界面 
int admin_researchorder()
{
	
	//查询窗口
	TIME_T timectl=time_control_init(480,20,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T researchorderwin={20,70,750,600,6,
	{{25,90,100,50,"订单编号:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{125,90,180,50,"",LIGHTCYAN,CYAN,RED,EDIT,1,1},
	{305,90,100,50,"客户姓名:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{405,90,180,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
	{610,90,100,50,"查询",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{320,615,150,50,"返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0}},
	WHITE,0}; 
	
	//加载背景
	winbk_flush();
	window_show(researchorderwin); 
	time_show(timectl);
	//设计表格结构体
	TABLE_T table={40,160,710,400,6,4,{"订单编号","客户姓名","联系电话","订单状态"}};
	
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
			strcpy(table.data[row][++j],p->phonenum);
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
			strcpy(table.data[row][++j],p->phonenum);
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
			strcpy(table.data[row][++j],p->phonenum);
			strcpy(table.data[row][++j],state[p->role]);
			row++;
		}
		
		if(count3==0){
			pagenum3=1;
		}
		table_show(table,pagenow,pagenum3);
	}
	
	
	strcpy(buf1,researchorderwin.controls[1].text); 		//输入订单编号
	strcpy(buf2,researchorderwin.controls[3].text);			//输入客户姓名
	
	researchorderwin=window_run_with_time(researchorderwin,&timectl);			//窗口控件驱动
	
	if(researchorderwin.current==4){
		strcpy(buf1,researchorderwin.controls[1].text); 		//输入订单编号
		strcpy(buf2,researchorderwin.controls[3].text);			//输入客户姓名
		if(strlen(buf1)>0&&strlen(buf2)==0){
			//strcpy(buf1,researchorderwin.controls[1].text);//订单编号查询
			//strcpy(buf2,researchorderwin.controls[3].text);
			freelist(temp);
			temp=initlist(); 
			
			Order_T *T=NULL;
			
			int found=0; 
			for(i=1;i<=getlistnodecount(orderslist);i++){
				T=(Order_T *)findnode(orderslist,i);
				if(strstr(T->order_id,buf1)!=NULL){
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
					return 12;
				}
			return 12;
		}else if(strlen(buf2)>0&&strlen(buf1)==0){
			//strcpy(buf2,researchorderwin.controls[3].text);		//客户姓名查询
			//strcpy(buf1,researchorderwin.controls[1].text);
			freelist(temp);
			temp=initlist();
			
			Order_T *T=NULL;
		
			int found=0;
			for(i=1;i<=getlistnodecount(orderslist);i++){
				T=(Order_T *)findnode(orderslist,i);
				if(strstr(T->client_name,buf2)!=NULL){
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
					
					return 12;
				} 
			return 12;
				
		}else{
			memset(buf1,0,sizeof(buf1));
			memset(buf2,0,sizeof(buf2));
		}
		return 12;
		
	}else if(researchorderwin.current==5){
		//返回上一级 
		winbk_flush();
		return 10;  		//返回订单管理界面 
	}else if(researchorderwin.current==-1){
		//左键向上翻页
		if(pagenow>1){
			pagenow--;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是第一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 12; 
	}else if(researchorderwin.current==-2){
		//右键向下翻页 
		if(pagenow<pagenum){
			pagenow++;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是最后一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 12;
	} 
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

int admin_ordercheck(){
	//只显示待审核订单 
	//订单审核窗口
	TIME_T timectl=time_control_init(480,20,300,50,1000,TIME_FORMAT_FULL);
	int i,j,currentindex=0;
	int row=0;
	WINDOW_T checkwin={20,70,750,700,5,
	{{320,75,100,50,"管理员订单审核",LIGHTCYAN,CYAN,RED,LABEL,0},
	{500,700,100,50,"返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{150,700,180,50,"",LIGHTCYAN,CYAN,RED,EDIT,1,1},
	{350,700,100,50,"查看详情",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{50,700,150,50,"订单编号:",LIGHTCYAN,CYAN,RED,LABEL,0}},
	WHITE,0};
	
	//创建链表存储待审核订单 
	Lnode *checklist=initlist();
	
	//加载背景 
	winbk_flush();
	window_show(checkwin);
	time_show(timectl);
	//表格结构体 
	TABLE_T table={90,130,600,500,6,3,{"订单编号","客户姓名","订单状态"}};
	//显示待审核订单的相关信息 
	int pagecount=5;		//一页展示的数据行数(不算首行)
	int count=getlistnodecount(orderslist);	//总订单数 
	//int wait_check_count=0;			//待审核的订单数
	//int reject_count=0; 			//驳回的订单数 
	static int pagenow=1;
	
	
	memset(table.data,0,sizeof(table.data));
	Order_T *T=NULL;
	
	for(i=1;i<=count;i++)
{
    T=(Order_T *)findnode(
        orderslist,
        i
    );

    if(strcmp(
        T->state,
        "待审核"
       )==0)
    {
        insertAtTail(
            checklist,
            T
        );
    }
}	
	//表格总页数 
	static int pagenum=getlistnodecount(checklist)%pagecount==0?
	getlistnodecount(checklist)/pagecount:(getlistnodecount(checklist)/pagecount)+1;
	int start=(pagenow-1)*pagecount;
	
	for(i=1;i<=pagecount;i++){
		T=(Order_T *)findnode(checklist,i+start);
	
			j=0;
			if(i+start>getlistnodecount(checklist)){
				break;
			}
			strcpy(table.data[row][j],T->order_id);
			strcpy(table.data[row][++j],T->client_name);
			strcpy(table.data[row][++j],T->state);
			row++;
		}
	
	//待审核订单数量为0 
	if(getlistnodecount(checklist)==0){
		pagenum=1;
	}
	
	table_show(table,pagenow,pagenum);
	//窗口驱动 
	checkwin=window_run_with_time(checkwin,&timectl);
	if(checkwin.current==1){
		//返回上一级 
		winbk_flush();
		return 10;
	}else if(checkwin.current==3){
		//查看订单详情 
		int flag=0;
		char buf[20]={0};
		strcpy(buf,checkwin.controls[2].text);
		Order_T *p=NULL;
		if(strlen(checkwin.controls[2].text)==0){
			//未输入订单号 
			CONTROL_T fail={350,380,150,50,"请输入订单号!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			
			Sleep(1500);
			return 13;
		}
//		for(j=1;j<=getlistnodecount(orderslist);j++){
//			p=(Order_T *)findnode(orderslist,j);
//			if(strcmp(p->order_id,checkwin.controls[2].text)==0&&p->role!=0){
//				CONTROL_T fail={350,380,150,50,"该订单已审核!",LIGHTCYAN,CYAN,RED,BUTTON,0};
//				control_show(fail);
//				Sleep(1500);
//				return 13;
//			}
//		}
		for(i=1;i<=getlistnodecount(checklist);i++){
			p=(Order_T *)findnode(checklist,i);
			//遍历订单结点 
			
			if(strcmp(p->order_id,checkwin.controls[2].text)==0){
				//根据订单编号进行查询 
				//另起窗口 
				//详细信息窗口
				flag=1;
				if(p->role!=0){
					CONTROL_T fail={350,380,150,50,"该订单已审核!",LIGHTCYAN,CYAN,RED,BUTTON,0};
					control_show(fail);
					Sleep(1500);
					
					return 13;
				}
				WINDOW_T printwin={20,70,750,700,4,
				{{320,75,100,50,"订单详细信息",LIGHTCYAN,CYAN,RED,LABEL,0},
				{200,700,100,50,"通过",LIGHTCYAN,CYAN,RED,BUTTON,1},
				{330,700,100,50,"驳回",LIGHTCYAN,CYAN,RED,BUTTON,0},
				{460,700,150,50,"返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0}},
				WHITE,0};
				 
				winbk_flush();
				window_show(printwin);
				time_show(timectl);
				char buf[50]={0};
				
				//char type[4][10]="";
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
				if(printwin.current==3){
					//返回上一级 
					winbk_flush();
					return 13;
				}else if(printwin.current==2){
					//驳回订单 
					//驳回窗口
					WINDOW_T rejectwin={180,70,500,300,4,
					{
					{350,80,100,50,"填写驳回原因",LIGHTCYAN,CYAN,RED,LABEL,0},
					{330,140,200,120,"",LIGHTCYAN,CYAN,RED,EDIT,1,1},
					{310,315,100,50,"驳回",LIGHTCYAN,CYAN,RED,BUTTON,0},
					{470,315,100,50,"取消",LIGHTCYAN,CYAN,RED,BUTTON,0}
					},WHITE,0}; 
					
					winbk_flush();
					window_show(rejectwin);
					time_show(timectl);
					rejectwin=window_run_with_time(rejectwin,&timectl);
					
					if(rejectwin.current==2){
						
						if(strlen(rejectwin.controls[1].text)==0){
							CONTROL_T fail={350,380,200,50,"驳回原因不能为空!",LIGHTCYAN,CYAN,RED,BUTTON,0};
							control_show(fail);
							
							Sleep(1500);
							return 13;
						}
						char buf[10]="已驳回";
						//找到目标结点 
						Order_T *p=NULL;

						p=(Order_T *)findnode(orderslist,i);
						//驳回 
						reset_order_state(orderslist,p->state,buf);
						if(strcmp(p->state,"已驳回")==0&&p->role==5){
							reject_count++;
							CONTROL_T success={350,380,150,50,"已驳回!",LIGHTCYAN,CYAN,RED,BUTTON,0};
							control_show(success);
							
							Sleep(1500);
							return 13;
						}
					}else if(rejectwin.current==3){
						//取消驳回
						winbk_flush();
						return 13; 
					}
					
					
				}else if(printwin.current==1){
					//审核订单 
					
					char buf[10]="待入库";
					Order_T *T=NULL;
				
					T=(Order_T *)findnode(checklist,i);
					//修改订单状态 
					reset_order_state(checklist,T->order_id,buf);
					 
					if(strcmp(T->state,"待入库")==0&&T->role==1){
						//判断审核情况 
						CONTROL_T success={350,380,150,50,"审核成功!",LIGHTCYAN,CYAN,RED,BUTTON,0};
						control_show(success);
						
						Sleep(1500);
						return 13;
					}else{
						CONTROL_T fail={350,380,150,50,"审核失败!",LIGHTCYAN,CYAN,RED,BUTTON,0};
						control_show(fail);
						
						Sleep(1500);
						return 13;
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
		if(found==0){
			//输入的订单号不存在 
			CONTROL_T fail1={350,380,150,50,"该订单不存在!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail1);
			Sleep(1500);
			return 13;
		}else{
		
		
		//输入的订单存在但不需要审核 
		CONTROL_T fail={350,380,200,50,"订单已审核或被驳回!",LIGHTCYAN,CYAN,RED,BUTTON,0};
		control_show(fail);
		
		Sleep(1500);
		return 13;
	}
}
		
	}else if(checkwin.current==-1){
		//左键向上翻页
		if(pagenow>1){
			pagenow--;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是第一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 13; 
	}else if(checkwin.current==-2){
			//右键向下翻页 
		if(pagenow<pagenum){
			pagenow++;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是最后一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 13;
	}
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////


//根据初始时间及完成时间和订单状态统计订单数量
int countOrderByTime(char begin[],char end[],int role)
    //-1表示统计所有状态订单
	//0表示统计待审核状态订单
	//1表示统计待入库状态订单
	//2表示统计待出库状态订单
	//3表示统计运输中状态订单
	//4表示统计已送达状态订单
	//5表示统计已驳回状态订单 
{
    int count=0;

    int total=
    getlistnodecount(
        orderslist
    );

    for(int i=1;i<=total;i++)
    {
        Order_T *T=
        (Order_T *)findnode(
            orderslist,
            i
        );

        //时间筛选
        if(strcmp(
            T->create_time,
            begin
           )<0)
        {
            continue;
        }

        if(strcmp(
            T->create_time,
            end
           )>0)
        {
            continue;
        }

        //状态筛选
        if(role!=-1)
        {
            if(T->role!=role)
            {
                continue;
            }
        }

        count++;
    }

    return count;
}

///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
double getFinishRate(
    char begin[],
    char end[],
    int role
)
{
    int total=
    countOrderByTime(
        begin,
        end,		//统计所有状态订单数 
        -1
    );

    int finish=
    countOrderByTime(		//统计已完成的订单数 
        begin,
        end,
        role
    );

    if(total==0)
    {
        return 0;
    }

    return
    finish*100.0/total;
} 

///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////

int countOrderByTypeAndTime(
    char begin[],
    char end[],
    char type[]
)
{
    int count=0;

    int total=
    getlistnodecount(orderslist);

    for(int i=1;i<=total;i++)
    {
        Order_T *T=
        (Order_T *)findnode(
            orderslist,
            i
        );

        if(strcmp(T->create_time,begin)<0)
        {
            continue;
        }

        if(strcmp(T->create_time,end)>0)
        {
            continue;
        }

        if(strcmp(T->type,type)!=0)
        {
            continue;
        }

        count++;
    }

    return count;
}
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

	


