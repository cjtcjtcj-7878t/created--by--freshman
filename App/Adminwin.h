#ifndef _ADMINWIN_H_
#define _ADMINWIN_H_

extern int finished_count;		//已完成的订单数 
extern int reject_count;		//驳回的顶单数
extern int transing_count;		//运输中的订单数
extern int wait_in_count;			//待入库订单数
extern int wait_out_count;			//待出库订单数
extern int wait_check_count;		//待审核订单数 


int adminwin();//管理员界面函数 
int adminwin_systemmanage();	//管理员界面选择"1.系统管理" 
int adminwin_ordermanage();		//管理员界面选择"2.订单管理" 
int admin_adduserwin();	//"创建用户"界面函数,在管理员系统管理界面选择"1.创建用户" 
int admin_researchuserwin();		//"用户查询"界面函数,在管理员系统管理界面选择"2.用户查询"功能 
int admin_pwdreset();		//"密码重置"界面函数,在管理员系统管理界面选择"3.密码重置"
int admin_statis();		//管理员选择界面选择"5.统计分析" 
int admin_orderchange();		//管理员订单修改,只允许修改待审核订单
int admin_ordertrack();			//管理员订单跟踪，主要看订单状态
int admin_pwdchange();			//管理员选择界面选择"7.密码修改" 
#endif
