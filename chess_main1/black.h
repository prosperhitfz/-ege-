#include<iostream>


using namespace std;
 

class  black 
{
	int  chessman_X;  //横向位置
	int  chessman_Y;  //纵向位置 
	int  black_chessman_count  ; //落子总数
	int  black_chessmanplayer ;
	
	public:
		
	
	black()
	{
		black_chessman_count=0;
		black_chessmanplayer=-1;
	}
	
	
	bool submit_chessman(int chessman_X , int chessman_Y )
	{
		if(chessman_X>15 || chessman_X<1 || chessman_Y>15 ||chessman_Y<1)
		{
			return false;
		}
		else
		{
			this->chessman_X = chessman_X;
			this->chessman_Y = chessman_Y;
			black_chessman_count++;
			return true;
		}
	} 
	
	int  getIdentity()
	{
		return  black_chessmanplayer; 
	}
	int  getChessman_X()
	{
		return chessman_X-1;  //这里设置减一是因为画图从0位置开始 
	}
	
	int getChessman_Y()
	{
		return chessman_Y-1;
	}
	
	int getChessmanCount()
	{
		return black_chessman_count  ;
	}
};
