#ifndef _CLREKWIN_H_
#define _CLERKWIN_H_

/*
该头文件包含仓储员操作相关函数 
*/

int clerkwin();	//仓储员界面函数
int clerk_goods_in();		//在仓储员界面选择"1.货物入库",只显示待入库订单
int clerk_goods_out();			//在仓储员界面选择"2.货物出库",只显示待出库订单
int repertory_detail();			//库存管理界面 
#endif
