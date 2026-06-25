#include"control.h"
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<tchar.h>
#include<windows.h>



//显示时间函数 

/////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//控件显示函数 
void control_show(CONTROL_T ctrl){
	int i;
	char text[20]="\0";
	
	//绘制矩形框 
	if(ctrl.style==BUTTON||ctrl.style==EDIT||ctrl.style==EDIT_PWD||ctrl.style==SELECT
	||ctrl.style==SELECTED){
		if(ctrl.state==1){	//表示聚焦状态 
			setfillcolor(ctrl.bgcolor1);	//呈现聚焦时的颜色 
		}else{
			setfillcolor(ctrl.bgcolor2);	//呈现不聚焦的颜色	
		}
		fillrectangle(ctrl.x,ctrl.y,ctrl.x+ctrl.width,ctrl.y+ctrl.height);
		//填充矩形框 
	}
	
	//显示文字 
	settextcolor(ctrl.textcolor);
	if(ctrl.style==EDIT||ctrl.style==LABEL||ctrl.style==TIME){	//标签或明文输入框 
		outtextxy(ctrl.x+10,ctrl.y+5,ctrl.text);
	}else if(ctrl.style==BUTTON){		//按钮控件 
		settextstyle(40,10,_T("黑体"));
		int center=ctrl.x+(ctrl.width-strlen(ctrl.text)*10)/2;
		outtextxy(center,ctrl.y+10,ctrl.text);
		
	}else if(ctrl.style==EDIT_PWD){	//密码输入框 
		char buf[100]="";
		
		//重新绘制矩形框 
		setfillcolor(ctrl.state?ctrl.bgcolor1:ctrl.bgcolor2);
		fillrectangle(ctrl.x,ctrl.y,ctrl.x+ctrl.width,ctrl.y+ctrl.height);
		
		if(ctrl.pwd_show==0){
			//密文显示
			int len=strlen(ctrl.text);
			for(i=0;i<len;i++){
				buf[i]='*';
			} 
			buf[len]='\0';
			outtextxy(ctrl.x+10,ctrl.y+5,buf);
			
		}else {
			//明文显示 
			outtextxy(ctrl.x+10,ctrl.y+5,ctrl.text);
		}
			
			
	}else if(ctrl.style==SELECT||ctrl.style==SELECTED){	//选择控件 
		char buf[20]="\0";
		sscanf(ctrl.text,"%[^,]",buf);	//截取字符串text到逗号处 
		outtextxy(ctrl.x+5,ctrl.y,buf);
		outtextxy(ctrl.x+ctrl.width-15,ctrl.y,"v");
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////
//窗口显示函数
void window_show(WINDOW_T win){
	
	//绘制窗口背景
	setfillcolor(win.bgcolor);	//背景颜色 
	fillrectangle(win.x,win.y,win.x+win.width,win.y+win.height);	//定义窗口矩形大小 
	//在窗口背景上显示控件 
	int i;
	for(i=0;i<win.count;i++){
		
		
			control_show(win.controls[i]);
		
	}
	
} 

////////////////////////////////////////////////////////////////////////////////////////
//窗口驱动函数
WINDOW_T window_run_with_time(WINDOW_T win,TIME_T *ctrl){
	int i=0;
	int j;
	char ch1,ch2;
	unsigned long lastInputTime = 0;
	//寻找第一个可以聚焦的控件(除了LABEL其余都可聚焦) 
	while(win.controls[i].style==LABEL){
		i++;
		if(i==win.count){
			i=0;
		}
	}
	
	while(1){
		
	if(time_update(ctrl)){
			FlushBatchDraw();
		}
		
		if(kbhit()){
		
		lastInputTime=GetTickCount();
		 
		ch1=getch();
		if(ch1=='\r'){
			//'\r'代表回车键
			
			//EDIT输入框
			if(win.controls[i].style==EDIT&&win.controls[i].chineseEdit==1){
				InputEdit(&win.controls[i],"请输入相应内容");
				control_show(win.controls[i]);
				time_show(*ctrl);
				continue;
			}
			//BUTTON控件 
			if(win.controls[i].style==BUTTON){
				win.current=i;
				return win;
			}else if(win.controls[i].style==SELECT||win.controls[i].style==SELECTED){
				//定义选择窗口 
				static WINDOW_T selectwin={win.controls[i].x,win.controls[i].y+50,win.controls[i].width,
				win.controls[i].height,WHITE};
				
				
				if(win.controls[i].style==SELECT){
				
				//分割字符串 
					char *buf[10]={0};
					int k=0;
					char *token=strtok(win.controls[i].text,",");
					while(token!=NULL){
					//printf("子串:%s",token);
						buf[k++]=token;
						token=strtok(NULL,",");
					
				}
					selectwin.count=k-1;
					//构建下拉框组合 
					for(j=1;j<=k-1;j++){
						CONTROL_T tempctrl={win.controls[i].x,win.controls[i].y+j*50,
						win.controls[i].width,win.controls[i].height,"",LIGHTCYAN,CYAN,RED,BUTTON,0};
					
						strcpy(tempctrl.text,buf[j]);	//截取的字符串赋给组件的text 
					
						selectwin.controls[j-1]=tempctrl;	//赋值窗口的组件 
					
					if(j==1){
						selectwin.controls[j-1].state==1;	//第一个选择为聚焦状态 
					}
					
				}
				//改变下拉框控件组合类型为已初始化 
				win.controls[i].style==SELECTED;
			}
				
				//显示下拉框组合
				window_show(selectwin);
				time_show(*ctrl);
				
				//下拉框驱动
				selectwin=window_run_with_time(selectwin,ctrl);
				
				//用户在下拉框选择选型后将选项显示在原窗口矩形框中 
				strcpy(win.controls[i].text,selectwin.controls[selectwin.current].text);
				
				
				//背景刷新 
				winbk_flush();
				//重刷窗口 
				window_show(win); 
				time_show(*ctrl);
				 
				
		}
			
		}else if(ch1>='0'&&ch1<='9'||ch1>='a'&&ch1<='z'||ch1>='A'&&ch1<='Z'){
			if(win.controls[i].style==EDIT||win.controls[i].style==EDIT_PWD||win.controls[i].style==SELECT){
				//编辑框输出文字 
				win.controls[i].text[strlen(win.controls[i].text)]=ch1;
				control_show(win.controls[i]);
				time_show(*ctrl);
			}
		}else if(ch1==-32){
			ch2=getch();
			if(ch2==KEY_UP){
				//接收向上键 
				//将当前控件改为未聚焦状态 
				win.controls[i].state=0;
				control_show(win.controls[i]);
				
				
				//移动到下一个可聚焦的控件 
				do{
					i--;
					if(i==-1){
						i=win.count;
					}
				}while(win.controls[i].style==LABEL);
				
				//将移动到的控件改为聚焦状态
				win.controls[i].state=1;
				control_show(win.controls[i]); 
				time_show(*ctrl);
				
				
			}else if(ch2==KEY_DOWN){
				//接收向下键
				//将当前控件改为未聚焦状态
				win.controls[i].state=0;
				control_show(win.controls[i]);
				
				//移动
				do{
					i++;
					if(i==win.count){
						i=0;
					}
				}while(win.controls[i].style==LABEL);
				
				//将移动到的控件改为聚焦状态
				win.controls[i].state=1;
				control_show(win.controls[i]);
				time_show(*ctrl);
				 
			}else if(ch2==KEY_LEFT){
				win.current=-1;	//左键标识 
				return win;
			}else if(ch2==KEY_RIGHT){
				win.current=-2;	//右键标识 
				return win;
			}
		}else if(ch1=='\b'){
			//接收回删键
			if(win.controls[i].style==EDIT||win.controls[i].style==EDIT_PWD){
				if(strlen(win.controls[i].text)>0){
				
				win.controls[i].text[strlen(win.controls[i].text)-1]='\0';
				control_show(win.controls[i]);
				time_show(*ctrl);
				
			}
			}
			 
		}else if(ch1==0||ch1==224){
			//监听键盘F2键的输入 
			ch2=getch();
			
			if(ch2==60){
				//F2的ASCII值
				
				if(win.controls[i].pwd_show==0){
					//密文显示时按F2键转换明文显示 
					win.controls[i].pwd_show=1; 
					 
				}else{
					//明文显示时按F2转换密文显示 
					win.controls[i].pwd_show=0;
				} 
				
				control_show(win.controls[i]);
				time_show(*ctrl);
				FlushBatchDraw();
				
				continue;
			}
		}
		
	}else{
		Sleep(50);
	}

	
} 
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
WINDOW_T window_run(WINDOW_T win){
	TIME_T mytime={0,0,0,0,0,0,0,0};
	return window_run_with_time(win,&mytime);
}

//////////////////////////////////////////////////////////////////////////
//窗口背景刷新函数 
void winbk_flush(){
	
	IMAGE img;
	loadimage(&img,"image/image1.jpg",800,800);
	putimage(0,0,&img);
	
	setbkmode(TRANSPARENT);
	settextcolor(CYAN);
	
}

//////////////////////////////////////////////////////////////////////////
//表格绘画函数 
void table_show(TABLE_T table,int pagenow,int pagenum){
	
	int i,j;
	//1.画格子
	int w=table.width/table.col;	//单个表格的宽度
	int h=table.height/table.row;	//单个表格的高度
	
	setfillcolor(WHITE);	//将实心矩形填充为白色(有覆盖效果) 
	setlinecolor(BLUE); 	//表格线条的颜色 
	settextcolor(RED);		//表格内容文字的颜色 
	
	
	for(i=0;i<table.col;i++){
		for(j=0;j<table.row;j++){
			
			//先画白色实心矩形覆盖内容 
			fillrectangle(table.x+w*i,table.y+h*j,table.x+w*i+w,table.y+j*h+h);
			
			//画线条 
			rectangle(table.x+w*i,table.y+h*j,table.x+w*i+w,table.y+j*h+h);
		}
	}
	//2.显示首行内容 
	for(i=0;i<table.col;i++){
		outtextxy(table.x+i*w+5,table.y+5,table.text[i]);
	
		
	}
	
	//3.显示表格内容
	for(i=1;i<=table.row;i++){
		for(j=0;j<table.col;j++){
			outtextxy(table.x+j*w+5,table.y+h*i+5,table.data[i-1][j]);
			//printf("%s\n",table.data[i-1][j]);
		}
	} 
	
	//4.显示翻页
	
	char str[50]="0";
	sprintf(str,"<-上页   共%d页/当前为第%d页    下页->",pagenum,pagenow);
	outtextxy(table.x+(table.width-strlen(str)*10)/2,table.y+h*(i-1)+15 ,str); 
	
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//中文输入函数 

void InputEdit(CONTROL_T *p,const char *title)
{	

	TCHAR buf[100];
    InputBox(
        p->text,
        sizeof(p->text),
        title
    );
	
	
	
    p->state = 1;
}

//////////////////////////////////////////////////////////////////////////

