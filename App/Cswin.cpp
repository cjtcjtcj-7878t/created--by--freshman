#include"Cswin.h"
#include"../View/control.h"
#include"../App/data.h"
#include"../App/Goods.h"
#include"../public/commonlist.h"
#include"../public/file.h"
#include<time.h>
#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern Lnode *goodslist;
extern Lnode *userslist;
extern Lnode *orderslist;
extern FILE *orders_fp;
extern FILE *goods_fp;
extern FILE *user_fp;
extern Lnode *transinglist;
int cswin(){
	//客服界面窗口 
	TIME_T timectl=time_control_init(480,20,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T Cswin={280,70,260,400,5,
	{{280,70,260,80,"1.订单创建",LIGHTCYAN,CYAN,RED,BUTTON,1},
	{280,150,260,80,"2.订单查询",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,230,260,80,"3.客户咨询",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,310,260,80,"4.客户反馈",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{280,390,260,80,"5.返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0}},
	WHITE,0};
	
	//加载背景
	winbk_flush();
	
	
	CONTROL_T Note={250,480,100,50,"上下键进行选择,回车键进行确定",LIGHTCYAN,CYAN,RED,LABEL,0};
	control_show(Note);
		
	//显示窗口 
	window_show(Cswin);
	time_show(timectl);
	//窗口按键驱动 
	Cswin=window_run_with_time(Cswin,&timectl);
	
	if(Cswin.current==0){
		//订单创建 
		return 17;
	}else if(Cswin.current==1){
		//订单查询 
		return 18;
	}else if(Cswin.current==2){
		
	}else if(Cswin.current==3){
		return 21;
	}else if(Cswin.current==4){
		winbk_flush();
		return 1;
	}else if(Cswin.current==-1){
		
		//左键防止程序崩溃
		return 8; 
	}else if(Cswin.current==-2){
		
		//右键防止程序崩溃
		return 8; 
	} 
}
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////

int cs_addorder(){
	//客服创建订单 
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
	{280,5,100,50,"订单编号:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{380,5,100,50,"",LIGHTCYAN,CYAN,RED,LABEL,0},
	{150,50,100,50,"客户姓名:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{250,55,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,1,1},
	{150,110,100,50,"联系电话:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{250,115,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
	{150,170,100,50,"客户地址:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{250,175,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
	{150,230,100,50,"货物名称:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{250,235,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
	{150,290,100,50,"货物类型:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{250,290,390,50,"请选择数据,普通类,易碎,冷链类,危险品",LIGHTCYAN,CYAN,RED,SELECT,0},
	{150,350,100,50,"货物重量:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{250,355,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
	{150,410,100,50,"货物数量:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{250,415,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
	{150,470,100,50,"货物体积:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{250,475,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
	{150,530,100,50,"发货地址:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{250,535,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
	{150,590,100,50,"收获地址:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{250,595,390,50,"",LIGHTCYAN,CYAN,RED,EDIT,0,1},
	{255,660,100,50,"提交",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{445,660,100,50,"返回",LIGHTCYAN,CYAN,RED,BUTTON,0}},WHITE,0}; 
	

	
	
	//订单编号的显示 
	Order_T *M=NULL;
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
		return 8;		//返回客服选择界面 
	}else if(addorder.current==22){		//创建订单 
		int k;
		int flag=1;
		Order_T *p=NULL;
		time_t now=time(NULL);
		struct tm *local=localtime(&now); 
		char time1[50]="";
		sprintf(time1,"%d%02d%02d",local->tm_year+1900,local->tm_mon+1,local->tm_mday);
		
		
		if(strlen(addorder.controls[3].text)==0||strlen(addorder.controls[5].text)==0||
		strlen(addorder.controls[7].text)==0||strlen(addorder.controls[9].text)==0||
		strlen(addorder.controls[11].text)==0||strlen(addorder.controls[13].text)==0||strlen(addorder.controls[14].text)==0
		||strlen(addorder.controls[15].text)==0||strlen(addorder.controls[17].text)==0||
		strlen(addorder.controls[21].text)==0){
			CONTROL_T fail7={350,380,150,50,"请完善相关数据!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail7);
			
			Sleep(1500);
			return 17;
		}
		Order_T *T=NULL;
		T=(Order_T *)malloc(sizeof(Order_T));		//临时订单结点T用于添加订单结点 
		memset(T,0,sizeof(Order_T));
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
				p->role=0;
				if(strcmp(addorder.controls[11].text,"冷链")==0){
					strcpy(T->type,"冷链");
				}else if(strcmp(addorder.controls[11].text,"易碎品")==0){
					strcpy(T->type,"易碎品");
				}else if(strcmp(addorder.controls[11].text,"普通类")==0){
					strcpy(T->type,"普通类");
				}else if(strcmp(addorder.controls[11].text,"危险品")==0){
					strcpy(T->type,"危险品");
				}
				
				outtextxy(380,10,order_no);
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
				p->role=0;
				if(strcmp(addorder.controls[11].text,"冷链")==0){
					strcpy(T->type,"冷链");
				}else if(strcmp(addorder.controls[11].text,"易碎品")==0){
					strcpy(T->type,"易碎品");
				}else if(strcmp(addorder.controls[11].text,"普通类")==0){
					strcpy(T->type,"普通类");
				}else if(strcmp(addorder.controls[11].text,"危险品")==0){
					strcpy(T->type,"危险品");
				}
				outtextxy(380,10,order_no);
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
		return 10;		//返回客服选择界面 
	}else if(addorder.current==-1){
		
		//左键防止程序崩溃
		return 17; 
	}else if(addorder.current==-2){
		
		//右键防止程序崩溃
		return 17; 
	} 
}

//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
int cs_researchorder(){
	//客服查询订单 
	
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
			T=(Order_T *)malloc(sizeof(Order_T));
			memset(T,0,sizeof(Order_T));
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
					return 18;
				}
			return 18;
		}else if(strlen(buf2)>0&&strlen(buf1)==0){
			//strcpy(buf2,researchorderwin.controls[3].text);		//客户姓名查询
			//strcpy(buf1,researchorderwin.controls[1].text);
			freelist(temp);
			temp=initlist();
			
			Order_T *T=NULL;
			T=(Order_T *)malloc(sizeof(Order_T *));
			memset(T,0,sizeof(Order_T));
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
					
					return 18;
				} 
			return 18;
				
		}else{
			memset(buf1,0,sizeof(buf1));
			memset(buf2,0,sizeof(buf2));
		}
		return 18;
		
	} else if(researchorderwin.current==5){
		//返回上一级 
		winbk_flush();
		return 8 ;  		// 
	}else if(researchorderwin.current==-1){
		//左键向上翻页
		if(pagenow>1){
			pagenow--;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是第一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 18; 
	}else if(researchorderwin.current==-2){
		//右键向下翻页 
		if(pagenow<pagenum){
			pagenow++;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是最后一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 18;
	} 
}

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
//客户反馈 
int cs_consumerfeedback(){
	//设计窗口
	TIME_T timectl=time_control_init(480,20,300,50,1000,TIME_FORMAT_FULL);
	WINDOW_T feedbackwin={20,70,750,700,5,
	{{50,700,150,50,"订单编号:",LIGHTCYAN,CYAN,RED,LABEL,0},
	{150,700,180,50,"",LIGHTCYAN,CYAN,RED,EDIT,1,1},
	{350,700,100,50,"查看详情",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{500,700,100,50,"返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0},
	{320,75,100,50,"客服完成订单",LIGHTCYAN,CYAN,RED,LABEL,0}},WHITE,0}; 
	
	//加载背景
	winbk_flush();
	window_show(feedbackwin);
	time_show(timectl);
	//单独创建运输中的链表 
	Lnode *transinglist=initlist();
	Order_T *p=NULL;
	char buf2[50]="";
	time_t now=time(NULL);
	struct tm *local=localtime(&now); 
	sprintf(buf2,"%04d%02d%02d",local->tm_year+1900,local->tm_mon+1,local->tm_mday);
	//设计表格
	TABLE_T table={90,130,600,500,6,3,"订单编号","客户姓名","订单状态"};
	memset(table.data,0,sizeof(table.data)); 
	int i,j;
	int count=getlistnodecount(orderslist);
	
	//将运输中订单单独收集
	for(i=1;i<=count;i++){
		p=(Order_T *)findnode(orderslist,i);
		if(strcmp(p->state,"运输中")==0){
			insertAtTail(transinglist,p);
		}
	} 
	static int pagenow=1;		//首页 
	int pagecount=5;		//每页展示的订单数 
	static int pagenum=getlistnodecount(transinglist)%pagecount==0?
	getlistnodecount(transinglist)/pagecount:getlistnodecount(transinglist)/pagecount+1;	//表格总页数 
	int finished_count=0;		//已送达订单数 
	int start=(pagenow-1)*pagecount; 
	

	char buf[50]="";	//订单编号 
	
	//赋值表格数据 
	for(i=1;i<=getlistnodecount(transinglist);i++){
		p=(Order_T *)findnode(transinglist,i+start);
		
			//只显示运输中订单
			int row=0;
			if(i+start>getlistnodecount(transinglist)){
				break;
			} 
			j=0;
			strcpy(table.data[row][j],p->order_id);
			strcpy(table.data[row][++j],p->client_name);
			strcpy(table.data[row][++j],p->state);
			row++;
		
	}
	//显示表格 
	
	if(getlistnodecount(transinglist)==0){
		pagenum=1;
	}
	
	table_show(table,pagenow,pagenum);
	
	//窗口驱动 
	feedbackwin=window_run_with_time(feedbackwin,&timectl);
	if(feedbackwin.current==3){
		//返回上一级
		winbk_flush();
		return 8; 
	}else if(feedbackwin.current==2){
		//完成订单 
		int flag=0;
		strcpy(buf,feedbackwin.controls[1].text);
		if(strlen(buf)==0){
			CONTROL_T fail={350,380,150,50,"请输入订单号!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
			
			return 21; 
		}
			for(i=1;i<=getlistnodecount(transinglist);i++){
				p=(Order_T *)findnode(transinglist,i);
				
				if(strcmp(p->order_id,buf)==0){
					//找到目标订单
					//另起窗口显示详细信息
					flag=1;
					if(p->role!=3){
						CONTROL_T fail={350,380,150,50,"该订单未进行运输!",LIGHTCYAN,CYAN,RED,BUTTON,0};
						control_show(fail);
						Sleep(1500);
						return  21;
					}
					WINDOW_T detailwin={20,70,750,700,3,
					{{320,75,100,50,"订单详细信息",LIGHTCYAN,CYAN,RED,LABEL,0},
					{200,700,100,50,"完成",LIGHTCYAN,CYAN,RED,BUTTON,1},
					{460,700,150,50,"返回上一级",LIGHTCYAN,CYAN,RED,BUTTON,0}},WHITE,0};
					
					//加载窗口 
					winbk_flush();
					window_show(detailwin);
					time_show(timectl);
					char buf2[50]="";
					
					//显示订单信息 
					sprintf(buf2,"订单编号:%s",p->order_id);
					outtextxy(240,115,buf2);
					
					sprintf(buf2,"客户姓名:%s",p->client_name);
					outtextxy(240,175,buf2);
					
					sprintf(buf2,"客户电话:%s",p->phonenum);
					outtextxy(240,235,buf2);
					
					sprintf(buf2,"货物名称:%s",p->goods_name);
					outtextxy(240,295,buf2);
				
					sprintf(buf2,"货物类型:%s",p->type);
					outtextxy(240,355,buf2);
				
					sprintf(buf2,"货物重量:%s",p->weight);
					outtextxy(240,415,buf2);
				
					sprintf(buf2,"货物数量:%s",p->goods_count);
					outtextxy(240,475,buf2);
				
					sprintf(buf2,"发货地址:%s",p->send_location);
					outtextxy(240,535,buf2);
				
					sprintf(buf2,"收获地址:%s",p->receive_location);
					outtextxy(240,595,buf2);
				
					sprintf(buf2,"订单状态:%s",p->state); 
					outtextxy(240,655,buf2);
					
					//显示订单信息 
					detailwin=window_run_with_time(detailwin,&timectl);
					if(detailwin.current==2){
						//返回上一级
						winbk_flush();
						return 21; 
					}else if(detailwin.current==1){
						//完成订单
						char state[10]="已送达";
						Order_T *T=NULL;
						T=(Order_T *)findnode(transinglist,i);
						
						//修改订单状态 
						reset_order_state(transinglist,T->order_id,state);
						
						if(strcmp(T->state,"已送达")==0&&T->role==4){
							finished_count++;
							strcpy(T->finished_time,buf2);
							CONTROL_T success={350,380,150,50,"订单已送达!",LIGHTCYAN,CYAN,RED,BUTTON,0};
							control_show(success);
							
							Sleep(1500);
							return 21;
						}else{
							CONTROL_T fail={350,380,150,50,"出现错误!",LIGHTCYAN,CYAN,RED,BUTTON,0};
							control_show(fail);
							
							Sleep(1500);
							return 21;
						} 
					}
				 
				}
			}
			//未找到订单 
		if(flag==0){
			
			int found=0;
			for(i=1;i<=getlistnodecount(orderslist);i++){
				p=(Order_T *)findnode(orderslist,i);
				if(strcmp(p->order_id,buf)==0){
					found=1;
				}
			}
			
			//输入的订单不存在 
			if(found==0){
				CONTROL_T fail1={350,380,200,50,"该订单不存在!",LIGHTCYAN,CYAN,RED,BUTTON,0};
				control_show(fail1);
				Sleep(1500);
				return 21;
			}else{
			
			
			//输入的订单存在但未运输或已送达 
			CONTROL_T fail={350,380,250,50,"该订单未进行运输或已送达!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
			
			return 21;
			
		}
		}
		
	}else if(feedbackwin.current==-1){
		//左键向上翻页 
		if(pagenow>1){
			pagenow--;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是第一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 21; 
	}else if(feedbackwin.current==-2){
		//右键向下翻页 
		if(pagenow<pagenum){
			pagenow++;
		}else{
			CONTROL_T fail={350,380,150,50,"已经是最后一页!",LIGHTCYAN,CYAN,RED,BUTTON,0};
			control_show(fail);
			Sleep(1500);
		}
		return 21;
	}
} 
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
