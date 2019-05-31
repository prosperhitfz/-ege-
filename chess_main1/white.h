#include<iostream>


using namespace std;
 
class  white
{
	int  chessman_X;  //����λ��
	int  chessman_Y;  //����λ�� 
	int  white_chessman_count; //��������
	int  white_chessmanplayer;
	
	public:
	
	white()
	{
		white_chessman_count=0;
		white_chessmanplayer=1;
	}
	
	bool submit_chessman(int chessman_X , int chessman_Y )
	{
		if(chessman_X>15 || chessman_X<1  || chessman_Y>15 || chessman_Y<1)
		{
			return false;
		}
		else
	    {
	    	this->chessman_X = chessman_X;
			this->chessman_Y = chessman_Y;
			white_chessman_count++;
			return true;
		}
	} 
	
	int  getIdentity()
	{
		return  white_chessmanplayer; 
	}
	
	int  getChessman_X()
	{
		return chessman_X-1;
	}
	
	int getChessman_Y()
	{
		return chessman_Y-1;
	}
	
	int getChessmanCount()
	{
		return white_chessman_count  ;
	}
};
