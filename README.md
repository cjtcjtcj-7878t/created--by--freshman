# ILMS/created--by--freshman
a freshman's project learning 


# ILMS---created-by-freshman
计算机领域学子学习编写的工程——ILMS


  该编码程序的搭建环境如下：
    个人计算机,Window11家庭版。
    5.11版本DEV C++，
    该工程主要使用DEV C++的第三方库——EasyX库，要确保代码的正常运行需要在DEV C++安装第三方EasyX库
    
    EasyX库是针对c++使用的,但作者编写程序时尚未学习c++,所以源文件后缀名是.cpp,源文件的语言依然是c语言
    
    EasyX官方文档网址:https://docs.easyx.cn/zh-cn/intro

  目前ILMS的功能并没有全部开发，所以聚焦部分BUTTON按钮时按下回车键程序会崩溃而强制退出
  
    各个界面间的切换通过函数指针实现，每个具有相应功能的函数都有自己的数组下标（例如startwin为0，loginwin为1），所以函数类型都为int型，根据函数指针的下标给每个函数特定的返回值
    便于函数指针进行界面的切换。
    例如在main.cpp文件中，因为程序首先呈现的界面是startwin界面，所以startwin函数的数组下标应为0，使函数指针指向该startwin函数实现调用，同时初始化一个信标win_id=0,使用该信标作为函数指针的下标，
    让其接收函数返回值。
    因为其随着函数返回值动态变化，所以函数指针指向的函数也发生变化，不同的函数被调用就实现了界面切换

  程序首次启动时
  main.cpp文件中的file_open函数会自动在main文件目录下创建data文件夹，该文件夹
  包含三个txt文件
  
  users.txt   
  goods.txt    
  orders.txt    
  
  user_data_init_admin函数会在users.txt文件中初始化一个管理员角色admin-->123456,便于进行程序操作

  
  order_data_init函数会在orders.txt文件中初始化一个订单数据（订单结构体、用户结构体、货物结构体定义在Goods.h）