#include <iostream>
#include <graphics.h>
#include <conio.h>
#include "black.h"
#include "white.h"
#include <process.h>
#include <windows.h>
#define singleGirdSize 40
#define girdLength  15
 

using namespace std;


class  chessboard
{
	//int allchessman[girdLength][girdLength] = {{0 ,0}};
	struct allchessman
	{
		int point_X;   //记录棋子X轴位置 
		int point_Y;  //记录棋子Y轴位置
		int message;  //识别棋子身份  (黑方? 白方 ? 空子? ) 
	}allchessman[girdLength][girdLength];
	
	
public :	bool win;  //玩家输赢的标记 
			black b;  //定义黑方对象 
			white w;  //定义白方对象 
			//这里b , w 是全局的  ,局部的话会对black_chessman_count这种属性的变化有影响 
	
	public:
		
		//在构造方法中初始化所有棋子
		chessboard()
		{
			win= false;
			int x=100 , y=100;  //棋盘左上端点100 ,100 
			for(int i=0 ; i<15 ; i++ , y+=singleGirdSize)
			{
				for(int u=0; u<15 ; u++ , x+=singleGirdSize)
				{
					allchessman[i][u].point_X = x;
					allchessman[i][u].point_Y = y;
					if(allchessman[i][u].point_X == 100  || allchessman[i][u].point_X == 660 || allchessman[i][u].point_Y == 100 || allchessman[i][u].point_Y == 660)
					{
						allchessman[i][u].message =2; //棋盘边界标识记为2 , 不能落子 
					}
					else
					{
						allchessman[i][u].message =0;  //初始化为空子 
					}
				}
				x=100;  //让X重新回到端点位置 
			}
		} 
		
		
		
	//添加棋子 
	bool   addchessman(int chessman_X , int  chessman_Y , int message)
	{
		if(message == -1)  //黑方落子 
		{
			if(allchessman[chessman_X][chessman_Y].message== 0)  //预落子位置无子
			{
				allchessman[chessman_X][chessman_Y].message = -1;  //落子 
				setfillcolor(RED);
				fillellipse(allchessman[chessman_X][chessman_Y].point_X , allchessman[chessman_X][chessman_Y].point_Y  ,  20 , 20); //界面上显示落子 .半径20 
				if(is_run()) delay_fps(10);
				return true;   //落子成功 
			} 
			else  return false;  //添加棋子失败  重复落子的处理 
		}
		else   
		{
		
			if (message == 1)
			{
				if(allchessman[chessman_X][chessman_Y].message == 0 )  
				{
					allchessman[chessman_X][chessman_Y].message  =1;
					setfillcolor(WHITE);
					fillellipse(allchessman[chessman_X][chessman_Y].point_X , allchessman[chessman_X][chessman_Y].point_Y  ,  20 , 20); //界面上显示落子 .半径20 
					if(is_run()) delay_fps(10);
					return true; //落子成功 
				}
				else  return false;
			}
			else
			{
				return false; //应对意外情况 --message身份出错时 
			}
		}
	} //addchessman
	
	
	
	
	void  drawchessboard()
	{
		setinitmode(INIT_WITHLOGO, CW_USEDEFAULT,  CW_USEDEFAULT);
		//画布大小暂定800 ,800
		initgraph(800 , 800);
	
		setfont(50 ,0 ,"宋体");
		outtextxy(250 , 0 , "简易五子棋");
		setfont(20 , 0 , "宋体");
		//画出棋盘 
		//预定棋盘左上端点是100 ,100 像素点
		int startpoint_X =100  , startpoint_Y =100 ;
		char str[10];
		for(int i=0; i<15 ; i++)
		{
			sprintf(str , "%d" , i+1);
			outtextxy(startpoint_X-20 , startpoint_Y-7, str);
			line(startpoint_X , startpoint_Y  , startpoint_X+( girdLength*singleGirdSize-singleGirdSize) , startpoint_Y);  //线段画出屏幕会出错:什么也画不出来 
			startpoint_Y+=singleGirdSize;
		} 
		
		startpoint_Y = 100;  //重置起始点Y
		
		for(i=0 ; i<15 ; i++)
		{
			sprintf(str , "%d" , i+1);
			outtextxy(startpoint_X-7, startpoint_Y-20 , str);
			line(startpoint_X , startpoint_Y  , startpoint_X , startpoint_Y+(girdLength*singleGirdSize-singleGirdSize) );
			startpoint_X+=singleGirdSize;
		} 
		
		
		/* 
		for(int i=0 ; i<15 ; i++)
		{
			for(int u=0 ; u<15 ; u++)
			{
				if(allchessman[i][u].message == 2) {}
				else
				{
					circle(allchessman[i][u].point_X , allchessman[i][u].point_Y , 20);
				}
			}
		}
		*/ 
			
	}//drawchessboard 
	
	
	
	
	void  playchess()
	{
		if(is_run()) delay_fps(10);
		int x ,y ; //接收落子的位置 
		int identity=1; // 标识黑方 白方身份   identity取余不为0 则是黑方
		
		do
		{
			cout<<"                           *************先输入竖列 再输入横列***************  "<<endl;
		 	black_entry(x ,y);
			if(is_run()) delay_fps(10);
		 	if(!win)
		 	{
		 		white_entry(x ,y);
		 	}
		 	system("cls");
		} while(!win);
		getch();
	}
	
	void black_entry(int &x , int &y)
	{
		//bool addchessman(int chessman_X , int chessman_Y , int message);
		cout<<"                           请黑方落子(您的棋子颜色是红色):"<<endl;
		cout<<"                           请输入横向位置:"<<endl;
		cout<<"                            ";
		cin>>x;
		cout<<"                           请输入纵向位置:"<<endl;
		cout<<"                            ";
		cin>>y; 	
	
		if( ! b.submit_chessman(x ,y) )
		{
			cout<<"                       输入位置超出棋盘大小或不合法,请重新输入"<<endl;
			black_entry(x ,y);
		}
		
		if( !addchessman(b.getChessman_X(), b.getChessman_Y() , b.getIdentity()) )
		{
			cout<<"                       落子失败! 该位置已有棋子或棋盘边界不能落子! 请重新输入~~~"<<endl; 
			black_entry( x ,y);
		}
		else
		{
			 if(bunko( b.getChessman_X(), b.getChessman_Y() , b.getIdentity()) )   
			 {
			 	setfont(50 , 0 ,"宋体");
			 	setfontbkcolor(GREEN);
			 	outtextxy(300 ,300 ,"黑方胜!");
			 	setfont(20 ,0 ,"宋体");
				outtextxy(300 ,750 ,"按任意键退出!"); 
			 	win = true;
			 }
		}
		cout<<"                           当前黑方落子总数:"<<b.getChessmanCount()<<endl;
		cout<<"                           当前白方落子总数:"<<w.getChessmanCount()<<endl;  
	}
	
	
	void white_entry(int &x , int &y)
	{
	//	bool addchessman(int chessman_X , int chessman_Y , int message);
		cout<<endl<<endl<<endl;
		cout<<"                          请白方落子(您的棋子颜色是白色):"<<endl;
		cout<<"                          请输入横向位置:"<<endl;
		cout<<"                            ";
		cin>>x;
		cout<<"                          请输入纵向位置:"<<endl;
		cout<<"                            ";
		cin>>y; 	
		
		if( ! w.submit_chessman(x ,y) )
		{
			cout<<"                      输入位置超出棋盘大小或不合法,请重新输入"<<endl;
			black_entry(x ,y);
		}
		
		if( !addchessman(w.getChessman_X() ,w.getChessman_Y() ,w.getIdentity()) )
		{
			cout<<"                     落子失败! 该位置已有棋子或棋盘边界不能落子! 请重新输入~~~"<<endl;
			white_entry(x ,y);
		}
		else
		{
			 if(bunko( w.getChessman_X(), w.getChessman_Y() , w.getIdentity()) )   
			 {
			 	setfont(50 , 0 ,"宋体");
			 	setfontbkcolor(LIGHTGRAY);
			 	outtextxy(300 ,300 ,"白方胜!");
			 	setfont(20 ,0 ,"宋体");
				outtextxy(300 ,720 ,"按任意键退出!"); 
			 	win = true;
			 }
		} 
	}
	
bool bunko(int x, int y , int message) //判胜 
{
	int xReturnZero =x;
	int yReturnZero =y; 
	int accumulative=0; //用来记录黑方或白方累计连在一起的 棋子个数 
	//先以该子位置为基点,向上(X轴不动 ,Y轴反方向) 逐一判断
	while(allchessman[--x][y].message == message)
	{
		accumulative++;
	//cout<<"累计的:"<<accumulative<<endl;
	} 
	/* 
	if(accumulative == 5) 
	{
	accumulative=0; //重置计数为0 
	return true;
	}
	else
	{
	return false;
	}
	*/ 
	x = xReturnZero;
	y = yReturnZero;
	//先以该子位置为基点 , 向下( X轴不动 , Y轴正方向) 逐一判断 
	while(allchessman[++x][y].message == message)
	{
		accumulative++;
		//cout<<"累计的:"<<accumulative<<endl;
	} 
	if(accumulative == 5) 
	{
		accumulative=0; //重置计数为0 
		return true;
	}
	else
	{
		//return false;
	}
	x = xReturnZero;
	y = yReturnZero;
	//先以该子位置为基点 , 向左(Y轴不动 , X轴反方向) 逐一判断
	while(allchessman[x][--y].message == message)
	{
		accumulative++;
		//cout<<"累计的:"<<accumulative<<endl;
	} 
	/*
	if(accumulative == 5) 
	{
	accumulative=0; //重置计数为0 
	return true;
	}
	else
	{
	return false;
	}
	*/
	x = xReturnZero;
	y = yReturnZero;
	//先以该子位置为基点, 向右(Y轴不动 , X轴正方向) 逐一判断
	while(allchessman[x][++y].message == message)
	{
		accumulative++;
		//cout<<"累计的:"<<accumulative<<endl;
	} 
	
	if(accumulative == 5) 
	{
		accumulative=0; //重置计数为0 
		return true;
	}
	else
	{
		//return false;
	}
	x = xReturnZero;
	y = yReturnZero;
	//右下方
	while(allchessman[++x][++y].message == message)
	{
		accumulative++;
		//cout<<"累计的:"<<accumulative<<endl;
	} 
	/*
	if(accumulative == 5) 
	{
	accumulative=0; //重置计数为0 
	return true;
	}
	else
	{
	return false;
    } */ 
	x = xReturnZero;
	y = yReturnZero;
	//左上方
	while(allchessman[--x][--y].message == message)
	{
		accumulative++;
		//cout<<"累计的:"<<accumulative<<endl;
	} 
	if(accumulative == 5) 
	{
		accumulative=0; //重置计数为0 
		return true;
	}
	else
	{
		//return false;
	} 
	x = xReturnZero;
	y = yReturnZero;
	//右上方
	while(allchessman[--x][++y].message == message)
	{
		accumulative++;
		//cout<<"累计的:"<<accumulative<<endl;
	} 
	/* 
	if(accumulative == 5) 
	{
	accumulative=0; //重置计数为0 
	return true;
	}
	else
	{
	return false;
    } */ 
	x = xReturnZero;
	y = yReturnZero;
	//左下方
	while(allchessman[++x][--y].message == message)
	{
		accumulative++;
		//cout<<"累计的:"<<accumulative<<endl;
	} 
	if(accumulative == 5) 
	{
		accumulative=0; //重置计数为0 
		return true;
	}
	else
	{
		return false;
	} 
}
//要在界面上显示黑方已下棋子个数 
	
	
};